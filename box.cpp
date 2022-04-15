#include <SFML/Graphics.hpp>
#include "box.hpp"
#include <iostream>
#include <math.h>

Box::Box() {

};

Box::Box(sf::Texture * backgroundTex, sf::Texture * leftMenuTex, sf::Texture * containerTex, sf::Font * font, std::string name) {
    background.setTexture(* backgroundTex);
    container.setTexture(* containerTex);
    leftMenu.setTexture(* leftMenuTex);
    container.setPosition(88, 0);
    leftMenu.setPosition(0, 0);

    for(int i = 0; i < 20; i++) {
        entries.push_back(BoxEntry());
        entries.back().setIndex(i);
    }

    pokeName.setFont(* font);
    pokeName.setFillColor(sf::Color::White);
    pokeName.setOutlineColor(sf::Color(100, 100, 100));
    pokeName.setOutlineThickness(0.5f);
    pokeName.setCharacterSize(15);

    boxName.setFont(* font);
    boxName.setFillColor(sf::Color(100, 100, 100));
    boxName.setOutlineColor(sf::Color::White);
    boxName.setOutlineThickness(0.5f);
    boxName.setCharacterSize(15);
    boxName.setString(name);

    miscText.setFont(* font);
    miscText.setFillColor(sf::Color::White);
    miscText.setOutlineColor(sf::Color(100, 100, 100));
    miscText.setOutlineThickness(0.5f);
    miscText.setPosition(sf::Vector2f(8, 163));
    miscText.setCharacterSize(15);
};

void Box::renderContainer(sf::RenderWindow & window) {
    if(offset != sf::Vector2f(0,0)) {
        container.setPosition(container.getPosition() + offset);
    }

    window.draw(container);
    
    if(offset != sf::Vector2f(0,0)) {
        container.setPosition(container.getPosition() - offset);
    }

    for(int i = 0; i < entries.size(); i++) {
        int col = entries[i].getIndex() % 5;
        int row = floor(entries[i].getIndex()/5);

        sf::Vector2f renderPos = sf::Vector2f(col * 30 + 92, row * 30 + 30) + offset;
        entries[i].render(window, renderPos);
    }

    boxName.setPosition(sf::Vector2f(158, 10) + offset);
    window.draw(boxName);

    internalTimer += 1;
};

void Box::renderLeftMenu(sf::RenderWindow & window) {
    window.draw(leftMenu);
};

void Box::renderBackground(sf::RenderWindow & window) {
    for(int i = 0 ; i < window.getSize().x; i += 20) {
        for(int j = 0 ; j < window.getSize().y; j += 20) {
            background.setPosition(i, j);
            window.draw(background);
        }
    }
};

void Box::addEntry(Pokemon * pokemon) {
    for(int i = 0 ; i < entries.size(); i++) {
        if(entries[i].getPokemon() == NULL) {
            entries[i].setPokemon(pokemon);
            return;
        }
    }
};

BoxEntry * Box::getEntry(int index) {
    for(int i = 0 ; i < entries.size(); i++) {
        if(entries[i].getIndex() == index) {
            return &(entries[i]);
        }
    }
};

void Box::movePokemon(BoxEntry * p1, BoxEntry * p2) {
    Pokemon * temp = p1->getPokemon();
    p1->setPokemon(p2->getPokemon());
    p2->setPokemon(temp);
};

void Box::renderPokemonInfo(sf::RenderWindow & window, Pokemon * pokemon) {
    pokemon->renderHD(window, sf::Vector2f(4, 43));

    pokeName.setString(pokemon->name);
    
    pokeName.setPosition(sf::Vector2f(4, 125));
    window.draw(pokeName);

    pokeName.setPosition(sf::Vector2f(3, 2));
    window.draw(pokeName);

    miscText.setString(pokemon->ability);
    window.draw(miscText);
};