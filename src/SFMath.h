#ifndef SFMATH_H
#define SFMATH_H

/**
 * A Point representation somewhat in the style of the IBM/Sony Vectormath library.
 */
class Point2 {
public:
    inline Point2(const float x, const float y) : x(x), y(y) {}
    inline Point2(const Point2& p) : x(p.x), y(p.y) {}
    inline const float getX() const { return x; }
    inline const float getY() const { return y; }
private:
    float x, y;
};

typedef Point2 Vector2;

#endif
