#include "Vec2.h"
#include <SFML/Graphics.hpp>


class CTransform {

public:

    Vec2 position = { 0.0, 0.0};
    Vec2 velocity = { 0.0, 0.0};
    float angle = 0;

    CTransform (const Vec2& posIn, const Vec2& velIn, float a)
    : position(posIn), velocity(velIn), angle(a) {

    }

};

class CShape {

public:

    sf::CircleShape shape;

    CShape (float rad, int points, const sf::Color& fill, const sf::Color& outline, float thickness) 
    : shape(rad, points) {

        shape.setFillColor(fill);
        shape.setOutlineColor(outline);
        shape.setOutlineThickness(thickness);
        shape.setOrigin(rad, rad);
    }

};


class CCollision {

public:

    float radius = 0;
    CCollision (float r)
    : radius(r) {

    }

};

class CLifespan {

public:

    int remaining = 0;
    int total = 0;
    
    CLifespan (int total)
    : remaining(total), total(total) {

    }

};

class CInput {

public:

    bool up = false;
    bool left = false;
    bool right = false;
    bool down = false;
    bool shoot = false;

    CInput () {}

};



class CScore {

public:

    int score = 0;

    CScore (int s) 
    : score(s) {

    }

};




