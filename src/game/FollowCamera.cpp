#include "FollowCamera.h"
#include "Entity.h"
#include "Level.h"

#include "../core/LogManager.h"
using namespace jvgs::core;

using namespace std;

#include "../video/VideoManager.h"
using namespace jvgs::video;

using namespace jvgs::math;

#include "../tinyxml/tinyxml.h"

namespace jvgs
{
    namespace game
    {
        void FollowCamera::loadData(TiXmlElement *element)
        {
            element->QueryFloatAttribute("maxDistance", &maxDistance);
            target = element->Attribute("target");
            Entity *entity = level->getEntityById(target);
            if(entity)
                position = entity->getPosition();
        }

        FollowCamera::FollowCamera(const std::string &target, float maxDistance,
                Level *level)
        {
            this->level = level;
            this->target = target;
            this->maxDistance = maxDistance;
        }

        FollowCamera::FollowCamera(TiXmlElement *element, Level *level)
        {
            this->level = level;
            load(element);
        }

        FollowCamera::~FollowCamera()
        {
        }

        void FollowCamera::update(float ms)
        {
            Entity *entity = level->getEntityById(target);
            if(entity) {
                Vector2D entityToCamera = position - entity->getPosition();
                if(entityToCamera.getLength() > maxDistance) {
                    entityToCamera.setLength(maxDistance);
                    position = entity->getPosition() + entityToCamera;
                }
            }
        }

        void FollowCamera::transform() const
        {
            VideoManager *videoManager = VideoManager::getInstance();
            videoManager->translate(-position + videoManager->getSize() * 0.5f);
        }
    }
}