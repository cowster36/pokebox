#include "pokemon.hpp"
#include "box.hpp"
#include "gamemanager.hpp"

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    srand(time(NULL));

    GameManager gameManager (256, 200);

    sf::RenderWindow window(sf::VideoMode(gameManager.width, gameManager.height), "PokeBox");
    window.setFramerateLimit(60);

    gameManager.loadAssets();
    gameManager.createCursor();

    gameManager.playMusic();

    for(int i = 0; i < 37; i++) {
        gameManager.addBox();
    }

    for(int i = 0; i < 721; i++) {
        gameManager.addPokemon("Bulbasaur", "None", 1, i + 1, gameManager.getBoxPointer(floor(i/20)));
    }

    while(window.isOpen()) {
        sf::Event event;

        gameManager.eventHandler(window, event);
    
        window.clear();
        gameManager.render(window);
        window.display();
    }
}
