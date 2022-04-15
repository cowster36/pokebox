#ifndef ANIMATION
#define ANIMATION

#include <SFML/Graphics.hpp>

#include "box.hpp"

class Animation {
private:
    Box * box1;
    Box * box2;

    sf::Vector2f desiredOff1;
    sf::Vector2f desiredOff2;
    sf::Vector2f vel;
public:
    Animation(Box *, sf::Vector2f, Box *, sf::Vector2f, sf::Vector2f);

    bool update();
    float getDirection();
    Box * getBox2();
};

#endif