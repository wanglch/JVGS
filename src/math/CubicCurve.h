#ifndef JVGS_MATH_CUBICCURVE_H
#define JVGS_MATH_CUBICCURVE_H

#include "Curve.h"

namespace jvgs
{
    namespace math
    {
        class CubicCurve: public Curve
        {
            private:
                /** Defining points of the curve.
                 */
                Vector2D start, control1, control2, end;

            public:
                /** Constructor.
                 *  @param start Curve start.
                 *  @param control1 First control point.
                 *  @param control2 Second control point.
                 *  @param end End of the curve.
                 */
                CubicCurve(const Vector2D &start, const Vector2D &control1,
                        const Vector2D &control2, const Vector2D &end);

                /** Destructor.
                 */
                virtual ~CubicCurve();

                /* Override
                 */
                virtual Vector2D getPoint(float t) const;

                /* Override
                 */
                virtual float getLengthGuess() const;
        };
    }
}

#endif
