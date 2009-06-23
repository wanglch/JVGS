#include "PathRenderer.h"
#include "Path.h"
#include "PathSegment.h"
#include "PathSegmentRenderer.h"
#include "CPathSegmentRenderer.h"
#include "HPathSegmentRenderer.h"
#include "LPathSegmentRenderer.h"
#include "MPathSegmentRenderer.h"
#include "QPathSegmentRenderer.h"
#include "SPathSegmentRenderer.h"
#include "TPathSegmentRenderer.h"
#include "VPathSegmentRenderer.h"
#include "ZPathSegmentRenderer.h"

#include "../core/LogManager.h"
using namespace jvgs::core;

using namespace jvgs::video;
using namespace jvgs::math;
using namespace std;

namespace jvgs
{
    namespace sketch
    {
        PathRenderer::PathRenderer(Path *path): PrimitiveRenderer(path)
        {
            this->path = path;

            segmentRenderers['c'] = new CPathSegmentRenderer(this);
            segmentRenderers['h'] = new HPathSegmentRenderer(this);
            segmentRenderers['l'] = new LPathSegmentRenderer(this);
            segmentRenderers['m'] = new MPathSegmentRenderer(this);
            segmentRenderers['q'] = new QPathSegmentRenderer(this);
            segmentRenderers['s'] = new SPathSegmentRenderer(this);
            segmentRenderers['t'] = new TPathSegmentRenderer(this);
            segmentRenderers['v'] = new VPathSegmentRenderer(this);
            segmentRenderers['z'] = new ZPathSegmentRenderer(this);
        }

        PathRenderer::~PathRenderer()
        {
            for(map<char, PathSegmentRenderer*>::iterator iterator =
                    segmentRenderers.begin();
                    iterator != segmentRenderers.end(); iterator++) {
                delete iterator->second;
            }
        }

        const Vector2D &PathRenderer::getStartingPoint() const
        {
            return startingPoint;
        }

        void PathRenderer::setStartingPoint(const Vector2D &startingPoint)
        {
            this->startingPoint = startingPoint;
        }

        const Vector2D &PathRenderer::getCurrentPoint() const
        {
            return currentPoint;
        }

        void PathRenderer::setCurrentPoint(const Vector2D &currentPoint)
        {
            this->currentPoint = currentPoint;
        }

        const Vector2D &PathRenderer::getLastControlPoint() const
        {
            return lastControlPoint;
        }

        void PathRenderer::setLastControlPoint(const Vector2D &lastControlPoint)
        {
            this->lastControlPoint = lastControlPoint;
        }

        void PathRenderer::fill(Renderer *renderer)
        {
            startingPoint = Vector2D(0.0f, 0.0f);
            currentPoint = Vector2D(0.0f, 0.0f);
            lastControlPoint = Vector2D(0.0f, 0.0f);

            vectors(renderer, true);
        }

        void PathRenderer::stroke(Renderer *renderer)
        {
            startingPoint = Vector2D(0.0f, 0.0f);
            currentPoint = Vector2D(0.0f, 0.0f);
            lastControlPoint = Vector2D(0.0f, 0.0f);

            vectors(renderer, false);
        }

        void PathRenderer::vectors(Renderer *renderer, bool fill)
        {
            for(int i = 0; i < path->getNumberOfSegments(); i++) {

                PathSegment *segment = path->getSegment(i);

                map<char, PathSegmentRenderer*>::iterator iterator =
                        segmentRenderers.find(segment->getLowerCaseCommand());

                if(iterator != segmentRenderers.end()) {
                    PathSegmentRenderer *segmentRenderer = iterator->second;
                    segmentRenderer->vectors(renderer, segment, fill);
                    LogManager::getInstance()->message(
                            "%c rendering.",
                            segment->getCommand());
                } else {
                    LogManager::getInstance()->warning(
                            "%c command for paths is not (yet) implemented.",
                            segment->getLowerCaseCommand());
                }
            }

            /* Stop the renderer if left unclosed. */
            if(renderer->isBusy()) {
                LogManager::getInstance()->message("Closed renderer.");
                renderer->end();
            }
        }
    }
}
