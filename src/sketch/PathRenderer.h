#ifndef JVGS_SKETCH_PATHRENDERER_H
#define JVGS_SKETCH_PATHRENDERER_H

#include "PrimitiveRenderer.h"
#include "../math/Vector2D.h"
#include <map>

namespace jvgs
{
    namespace sketch
    {
        class Path;
        class PathSegmentRenderer;

        class PathRenderer: public PrimitiveRenderer
        {
            private:
                Path *path;
                bool firstSegment;
                math::Vector2D startingPoint;
                math::Vector2D currentPoint;
                std::map<char, PathSegmentRenderer*> segmentRenderers;

            public:
                PathRenderer(Path *path);
                virtual ~PathRenderer();

                virtual bool isFirstSegment() const;
                virtual void setFirstSegment(bool firstSegment);

                virtual const math::Vector2D &getStartingPoint() const;
                virtual void setStartingPoint(const math::Vector2D &point);

                virtual const math::Vector2D &getCurrentPoint() const;
                virtual void setCurrentPoint(const math::Vector2D &point);

                virtual void fill(video::Renderer *renderer);
                virtual void stroke(video::Renderer *renderer);
                virtual void vectors(video::Renderer *renderer);
        };
    }
}

#endif
