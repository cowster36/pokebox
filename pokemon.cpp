#include <SFML/Graphics.hpp>
#include "pokemon.hpp"
#include <iostream>

Pokemon::Pokemon() {

};

Pokemon::Pokemon(std::string name, std::string ability, int level, sf::Texture * texture, sf::Texture * hdTex1, sf::Texture * hdTex2) {
    for(int i = 0; i < name.size(); i++) {
        name[i] = std::toupper(name[i]);
    }
    
    this->name = name;
    this->ability = ability;
    this->level = level;

    this->icon.setTexture(* texture);

    if(hdTex1 != NULL)
    this->hd.setTexture(* hdTex1);

    this->hdTexs.push_back(hdTex1);
    this->hdTexs.push_back(hdTex2);
};

void Pokemon::renderIcon(sf::RenderWindow & window, sf::Vector2f pos) {
    icon.setPosition(pos);
    window.draw(icon);
};

void Pokemon::renderHD(sf::RenderWindow & window, sf::Vector2f pos) {
    existenceTimer += 1;

    if(existenceTimer > 35 && existenceTimer < 60 && hdTexs[1] != NULL) {
        hd.setTexture(* hdTexs[1]);
        hd.setPosition(pos);
        window.draw(hd);
    } else if(hdTexs[0] != NULL) {
        hd.setTexture(* hdTexs[0]);
        hd.setPosition(pos);
        window.draw(hd);
    }
};

void Pokemon::resetExistenceTimer() {
    existenceTimer = 0;
};