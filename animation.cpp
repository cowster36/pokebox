#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "animation.hpp"

Animation::Animation(Box * box1, sf::Vector2f desiredOff1, Box * box2, sf::Vector2f desiredOff2, sf::Vector2f vel) {
    this->box1 = box1;
    this->box2 = box2;

    this->desiredOff1 = desiredOff1;
    this->desiredOff2 = desiredOff2;
    this->vel = vel;
};

bool Animation::update() {
    sf::Vector2f dist1 = desiredOff1 - box1->offset;
    sf::Vector2f dist2 = desiredOff2 - box2->offset;

    if(abs(dist1.x) < fmax(vel.x, 1) || abs(dist2.x) < fmax(vel.x, 1)) {
        box1->offset = desiredOff1;
        box2->offset = desiredOff2;
        return true;
    }

    box1->offset += vel;
    box2->offset += vel;

    return false;
};

float Animation::getDirection() {
    if(vel.x > 0) return 1;
    return -1;
};

Box * Animation::getBox2() {
    return box2;
};