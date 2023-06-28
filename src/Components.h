#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CShape {
public:
    sf::CircleShape circle;
    CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness)
    : circle(radius, points) {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);

    }
};

class CTransform {
public:
    Vec2 position = {0.0, 0.0};
    Vec2 velocity = {0.0, 0.0};
    float angle = 0;
    CTransform(const Vec2& p, const Vec2& v, float a)
    : position(p), velocity(v), angle(a) {}
};

class CCollision {
public:
    float radius = 0;
    CCollision(float r)
    : radius(r) {}
};

class CInput {
public:
    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;

    CInput() {}

};

class CScore {
public:
    int score = 0;
    CScore(int s)
    : score(s) {}
};

class CLifespan {
public:
    int remaining = 0;
    int total = 0;
    CLifespan(int totalArg)
    : remaining(totalArg), total(totalArg) {}
};
