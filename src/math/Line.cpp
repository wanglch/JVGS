#include "Line.h"

namespace jvgs
{
    namespace math
    {
        Line::Line(Vector2D point, Vector2D vector)
        {
            this->point = point;
            this->vector = vector.normalized();
        }

        Line::~Line()
        {
        }

        Vector2D Line::getNormal() const
        {
            return Vector2D(-vector.getX(), vector.getY());
        }
    }
}