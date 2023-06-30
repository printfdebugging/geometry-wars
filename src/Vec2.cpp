#include "Vec2.h"
#include <cmath>


Vec2::Vec2 (float xin, float yin) 
: x(xin), y(yin) {

}

bool Vec2::operator == (const Vec2& rhs) const {

    return (x == rhs.x && y == rhs.y);

}

bool Vec2::operator != (const Vec2& rhs) const {

    return !(x == rhs.x && y == rhs.y);

}

Vec2 Vec2::operator + (const Vec2& rhs) const {

    return Vec2(x + rhs.x, y + rhs.y);

}

Vec2 Vec2::operator - (const Vec2& rhs) const {

    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float val) const {

    return Vec2(x * val, y * val);
}

Vec2 Vec2::operator / (const float val) const {

    return Vec2(x / val, y / val);
}

void Vec2::operator += (const Vec2& rhs) {

    x = x + rhs.x;
    y = y + rhs.y;

}

void Vec2::operator -= (const Vec2& rhs) {

    x = x - rhs.x;
    y = y - rhs.y;

}

void Vec2::operator *= (const float val) {

    x = x * val;
    y = y * val;

}

void Vec2::operator /= (const float val) {

    x = x / val;
    y = y / val;

}



float Vec2::length(const Vec2& rhs) const {

    float lensq = (rhs.x - x)*(rhs.x - x) + (rhs.y - y)*(rhs.y - y);
    return std::sqrt(lensq);

}


void Vec2::normalise() {


}


