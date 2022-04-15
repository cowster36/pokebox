#ifndef GAMEMANAGER
#define GAMEMANAGER

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "pokemon.hpp"
#include "box.hpp"
#include "cursor.hpp"
#include "animation.hpp"

class GameManager {
private:
    std::vector<sf::Texture *> assets;
    std::string pokemonNames[721];
    std::string abilities[263];
    std::vector<Pokemon *> pokemon;
    std::vector<Box *> boxes;

    sf::Font font;

    Pokemon * createPokemon(Pokemon newPoke);

    void createBox(Box box);

    sf::Texture * addAsset(std::string fileName);

    sf::Vector2f scaleFactor;

    sf::Texture * getPokeIcon(int dexNum);

    sf::Texture * getPokeHD1(int dexNum);

    sf::Texture * getPokeHD2(int dexNum);

    sf::Texture * getBoxSprite(int index);

    bool leftPressed = false;
    bool rightPressed = false;
    bool upPressed = false;
    bool downPressed = false;
    bool lockKeys = false;

    Cursor cursor;
public:
    int frameCount = 0;
    Box * currentBox;
    int boxNum = 0;
    int width;
    int height;
    sf::Music bgm;

    Animation * currentAnimation = NULL;

    GameManager(int, int);

    void loadAssets();

    void createCursor();

    void addPokemon(std::string name, std::string ability, int level, int dexNum, Box * box);

    void addBox();

    void scrollBoxLeft();

    void scrollBoxRight();

    Box * getBoxPointer(int boxNum);

    void render(sf::RenderWindow & window);

    void eventHandler(sf::RenderWindow &, sf::Event &);

    void playMusic();
};

#endif