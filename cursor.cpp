#include <SFML/Graphics.hpp>

#include "cursor.hpp"
#include "pokemon.hpp"

Cursor::Cursor() {

};

Cursor::Cursor(sf::Texture * t1, sf::Texture * t2, sf::Texture * t3, sf::Texture * t4) {
    textures.push_back(t1);
    textures.push_back(t2);
    textures.push_back(t3);
    textures.push_back(t4);

    currentTexture = t1;

    sprite.setPosition(offset);
    sprite.setOrigin(sf::Vector2f(0, 20));
    sprite.setTexture(* t1);
};

void Cursor::moveLeft() {
    if(position.x < 1) return;
    position += sf::Vector2f(-1, 0);
    sprite.setPosition(position * 30.f + offset);
};

void Cursor::moveRight() {
    if(position.x > 3) return;
    position += sf::Vector2f(1, 0);
    sprite.setPosition(position * 30.f + offset);
};

void Cursor::moveUp() {
    if(position.y == -1) return;
    
    if(position.y == 0) {
        position = sf::Vector2f(-1, -1);
        sprite.setPosition(170, 20);
        boxSelector = true;
    } else {
        position += sf::Vector2f(0, -1);
        sprite.setPosition(position * 30.f + offset);
    }
};

void Cursor::moveDown() {
    if(position.y == -1) {
        position = sf::Vector2f(0, 0);
        sprite.setPosition(position * 30.f + offset);
        boxSelector = false;
        return;
    }

    if(position.y > 2) return;
    position += sf::Vector2f(0, 1);
    sprite.setPosition(position * 30.f + offset);
};

void Cursor::render(sf::RenderWindow & window, int frameCount) {
    if(grabbedPokemon != NULL) {
        currentTexture = textures[2];
        sprite.setTexture(* currentTexture);

        grabbedPokemon->renderIcon(window, sf::Vector2f(sprite.getPosition().x - 10,
                                                        sprite.getPosition().y - 15));
    } else if(currentTexture == textures[2]) {
        currentTexture = textures[0];
        sprite.setTexture(* currentTexture);
    } else if(frameCount % 20 == 0) {
        if(currentTexture == textures[0]) {
            currentTexture = textures[1];
        } else if(currentTexture == textures[1]) {
            currentTexture = textures[0];
        }

        sprite.setTexture(* currentTexture);
    }

    window.draw(sprite);
};

sf::Vector2f Cursor::getPosition() {
    return this->position;
};

BoxEntry * Cursor::getCurrentEntry(Box * currentBox) {
    int currentIndex = position.x + position.y * 5;
    BoxEntry * currentEntry = currentBox->getEntry(currentIndex);
    return currentEntry;
};
