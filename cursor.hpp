#ifndef CURSOR
#define CURSOR

#include <SFML/Graphics.hpp>
#include "box.hpp"

class Cursor {
private:
    std::vector<sf::Texture *> textures;
    sf::Vector2f position = sf::Vector2f(0, 0);
    sf::Sprite sprite;
    sf::Vector2f offset = sf::Vector2f(100, 35);
    sf::Texture * currentTexture;


public:
    Cursor();
    Cursor(sf::Texture *, sf::Texture *, sf::Texture *, sf::Texture *);
    bool boxSelector = false;
    BoxEntry * grabbedEntry = NULL;
    Pokemon * grabbedPokemon = NULL;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void render(sf::RenderWindow &, int);
    sf::Vector2f getPosition();
    BoxEntry * getCurrentEntry(Box *);
};

#endif