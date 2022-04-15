#ifndef BOX
#define BOX

#include <SFML/Graphics.hpp>
#include "pokemon.hpp"

class BoxEntry {
private:
    int index;
    Pokemon * pokemon = NULL;

public:
    BoxEntry(Pokemon * pokemon) {
        this->pokemon = pokemon;
    };

    BoxEntry() {
    };

    void render(sf::RenderWindow & window, sf::Vector2f pos) {
        if(pokemon != NULL) {
            pokemon->renderIcon(window, pos);
        }
    };

    void setIndex(int index) {
        this->index = index;
    };

    int getIndex() {
        return this->index;
    };

    Pokemon * getPokemon() {
        return this->pokemon;
    };

    void setPokemon(Pokemon * p) {
        this->pokemon = p;
    };
};

class Box {
private:
    sf::Sprite background;
    sf::Sprite container;
    sf::Sprite leftMenu;
    sf::Text pokeName;
    sf::Text boxName;
    sf::Text miscText;
    int internalTimer = 0;
    
public:
    std::vector<BoxEntry> entries;
    Box(sf::Texture *, sf::Texture *, sf::Texture *, sf::Font *, std::string);
    Box();
    static const int boxLimit = 20;
    sf::Vector2f offset = sf::Vector2f(0, 0);

    void renderContainer(sf::RenderWindow &);
    void renderLeftMenu(sf::RenderWindow &);
    void renderBackground(sf::RenderWindow &);
    void addEntry(Pokemon * pokemon);
    BoxEntry * getEntry(int);
    void movePokemon(BoxEntry *, BoxEntry *);
    void renderPokemonInfo(sf::RenderWindow &, Pokemon *);
};

#endif