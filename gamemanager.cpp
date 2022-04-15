#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>

#include "pokemon.hpp"
#include "box.hpp"
#include "animation.hpp"
#include "gamemanager.hpp"

GameManager::GameManager(int width, int height) {
    this->width = width;
    this->height = height;
};

Pokemon * GameManager::createPokemon(Pokemon newPoke) {
    pokemon.push_back(new Pokemon);
    (* pokemon.back()) = newPoke;

    return pokemon.back();
};

void GameManager::createBox(Box box) {
    boxes.push_back(new Box);
    (* boxes.back()) = box;

    if(currentBox == NULL) currentBox = boxes.back();
};

sf::Texture * GameManager::addAsset(std::string fileName) {
    //assets.push_back((sf::Texture *) malloc(sizeof(sf::Texture)));
    assets.push_back(new sf::Texture);
    
    if(assets.back()->loadFromFile(fileName) == false) {
        delete assets.back();
        return NULL;
    }

    return assets.back();
};

void GameManager::loadAssets() {
    //icon textures: 0 - 720
    for(int i = 1; i < 722; i++) {
        addAsset("assets/pokemon-icons/" + std::to_string(i) + ".png");
    }

    //box misc: 721, 722
    addAsset("assets/background.png");
    addAsset("assets/leftmenu.png");

    //box textures: 723 - 754
    for(int i = 0; i < 32; i++) {
        addAsset("assets/boxes/" + std::to_string(i) + ".png");
    }

    //cursor textures: 755, 756, 757
    addAsset("assets/cursor.png");
    addAsset("assets/cursor2.png");
    addAsset("assets/cursor3.png");

    //HD textures: 759 - ...
    for(int i = 1; addAsset("assets/pokemon-sprites/" + std::to_string(i) + "-1.png") != NULL; i++) {
        addAsset("assets/pokemon-sprites/" + std::to_string(i) + "-2.png");
    }

    std::ifstream namesFile("assets/names.txt");
    std::string currentName;

    for(int i = 0; getline(namesFile, currentName); i++) {
        pokemonNames[i] = currentName;
    }

    namesFile.close();

    std::ifstream abilitiesFile("assets/abilities.txt");
    std::string currentLine;

    for(int i = 0; getline(abilitiesFile, currentLine); i++) {
        std::string formattedAbility = "";
        int commaCount = 0;
        for(int j = 0; j < currentLine.size(); j++) {
            if(currentLine[j] == ',') {
                commaCount += 1;

                if(commaCount == 3) break;
            }

            if(commaCount > 1 && currentLine[j] != ',') {
                formattedAbility += currentLine[j];
            }
        }

        abilities[i] = formattedAbility;
    }

    abilitiesFile.close();

    font.loadFromFile("assets/font.ttf");

    bgm.openFromFile("assets/music.wav");
};

void GameManager::createCursor() {
    cursor = Cursor(assets[755], assets[756], assets[757], NULL);
};

sf::Texture * GameManager::getPokeIcon(int dexNum) {
    return assets[dexNum - 1];
};

sf::Texture * GameManager::getBoxSprite(int index) {
    return assets[721 + index];
};

sf::Texture * GameManager::getPokeHD1(int dexNum) {
    int hd1index = (dexNum - 1) * 2 + 758;
    if(assets.size() - 1 > hd1index) {
        return assets[hd1index];
    } else {
        return NULL;
    }
};

sf::Texture * GameManager::getPokeHD2(int dexNum) {
    int hd2index = (dexNum - 1) * 2 + 758 + 1;
    if(assets.size() - 1 > hd2index) {
        return assets[hd2index];
    } else {
        return NULL;
    }
};

void GameManager::addPokemon(std::string name, std::string ability, int level, int dexNum, Box * box) {
    box->addEntry(createPokemon(Pokemon(pokemonNames[dexNum - 1], 
                                        abilities[rand() % 263],
                                        level, 
                                        getPokeIcon(dexNum),
                                        getPokeHD1(dexNum),
                                        getPokeHD2(dexNum))));
};

void GameManager::addBox() {
    std::string name = "BOX ";
    name += std::to_string(boxes.size() + 1);
    createBox(Box(getBoxSprite(0), getBoxSprite(1), getBoxSprite(boxes.size() % 32 + 2), &font, name));
};

void GameManager::scrollBoxLeft() {
    if(boxNum > 0) {
        boxNum -= 1;
    } else {
        boxNum = boxes.size() - 1;
    }

    currentBox = getBoxPointer(boxNum);
};

void GameManager::scrollBoxRight() {
    if(boxNum < boxes.size() - 1) {
        boxNum += 1;
    } else {
        boxNum = 0;
    }

    currentBox = getBoxPointer(boxNum);
};

Box * GameManager::getBoxPointer(int boxNum) {
    return boxes[boxNum];
};

void GameManager::render(sf::RenderWindow & window) {
    currentBox->renderBackground(window);
    currentBox->renderContainer(window);
    currentBox->renderLeftMenu(window);

    if(currentAnimation != NULL) {
        if(currentAnimation->update() == true) {
            if(currentAnimation->getDirection() > 0) {
                scrollBoxLeft();
            } else {
                scrollBoxRight();
            }

            delete currentAnimation;
            currentAnimation = NULL;

            currentBox->renderBackground(window);
            currentBox->renderContainer(window);
            currentBox->renderLeftMenu(window);

            lockKeys = false;
        } else {
            if(currentAnimation->getDirection() > 1) {
                currentBox->renderBackground(window);
                currentBox->renderContainer(window);
                currentBox->renderLeftMenu(window);
                currentAnimation->getBox2()->renderContainer(window);
            } else {
                currentBox->renderBackground(window);
                currentBox->renderContainer(window);
                currentAnimation->getBox2()->renderContainer(window);
                currentBox->renderLeftMenu(window);
            }
        }
    } else {
        Pokemon * displayPokemon = NULL;

        if(cursor.grabbedPokemon != NULL) {
            displayPokemon = cursor.grabbedPokemon;
        } else if(cursor.boxSelector == false) {
            BoxEntry * currentEntry = cursor.getCurrentEntry(currentBox);
            displayPokemon = currentEntry->getPokemon();
        }

        if(displayPokemon != NULL) {
            currentBox->renderPokemonInfo(window, displayPokemon);
        }
    }

    cursor.render(window, frameCount);

    frameCount += 1;
};

void GameManager::eventHandler(sf::RenderWindow & window, sf::Event & event) {
    while(window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                window.close();
            break;
            case sf::Event::KeyPressed:
                if(lockKeys == true) break;

                switch(event.key.code) {
                    case sf::Keyboard::Left:
                        leftPressed = true;

                        if(cursor.boxSelector == false) {
                            if(cursor.grabbedPokemon == NULL && 
                                cursor.getCurrentEntry(currentBox)->getPokemon() != NULL)
                            cursor.getCurrentEntry(currentBox)->getPokemon()->resetExistenceTimer();
                            cursor.moveLeft();
                        } else {
                            lockKeys = true;

                            Box * nextBox;
                            if(boxNum == 0) {
                                nextBox = boxes[boxes.size() - 1];
                            } else {
                                nextBox = boxes[boxNum - 1];
                            }
                            nextBox->offset = sf::Vector2f(-width * 0.75f, 0);

                            currentAnimation = new 
                            Animation(currentBox, sf::Vector2f(width * 0.75f, 0), nextBox, sf::Vector2f(0, 0), sf::Vector2f(4, 0));
                        }
                    break;
                    case sf::Keyboard::Right:
                        rightPressed = true;
                        if(cursor.boxSelector == false) {
                            if(cursor.grabbedPokemon == NULL && 
                                cursor.getCurrentEntry(currentBox)->getPokemon() != NULL)
                            cursor.getCurrentEntry(currentBox)->getPokemon()->resetExistenceTimer();
                            cursor.moveRight();

                        } else {
                            lockKeys = true;
                            
                            Box * nextBox;
                            if(boxNum == boxes.size() - 1) {
                                nextBox = boxes[0];
                            } else {
                                nextBox = boxes[boxNum + 1];
                            }

                            nextBox->offset = sf::Vector2f(width * 0.75f, 0);

                            currentAnimation = new 
                            Animation(currentBox, sf::Vector2f(-width * 0.75f, 0), nextBox, sf::Vector2f(0, 0), sf::Vector2f(-4, 0));
                        }
                    break;
                    case sf::Keyboard::Up:
                        upPressed = true;

                        if(cursor.boxSelector == false && cursor.grabbedPokemon == NULL && 
                        cursor.getCurrentEntry(currentBox)->getPokemon() != NULL) {
                            cursor.getCurrentEntry(currentBox)->getPokemon()->resetExistenceTimer();
                        }

                        cursor.moveUp();
                    break;
                    case sf::Keyboard::Down:
                        downPressed = true;

                        if(cursor.boxSelector == false && cursor.grabbedPokemon == NULL && 
                        cursor.getCurrentEntry(currentBox)->getPokemon() != NULL) {
                            cursor.getCurrentEntry(currentBox)->getPokemon()->resetExistenceTimer();
                        }

                        cursor.moveDown();
                    break;
                    case sf::Keyboard::Return:
                        if(cursor.boxSelector == true) break;

                        if(cursor.grabbedEntry == NULL) {
                            BoxEntry * currentEntry = cursor.getCurrentEntry(currentBox);
                            cursor.grabbedEntry = currentEntry;
                            cursor.grabbedPokemon = currentEntry->getPokemon();
                            currentEntry->setPokemon(NULL);
                        } else {
                            BoxEntry * currentEntry = cursor.getCurrentEntry(currentBox);

                            cursor.grabbedEntry->setPokemon(cursor.grabbedPokemon);
                            currentBox->movePokemon(cursor.grabbedEntry, currentEntry);
                            cursor.grabbedEntry = NULL;
                            cursor.grabbedPokemon = NULL;
                        }
                    break;
                }
            break;
            case sf::Event::KeyReleased:
                switch(event.key.code) {
                    case sf::Keyboard::Left:
                        leftPressed = false;
                    break;
                    case sf::Keyboard::Right:
                        rightPressed = false;
                    break;
                    case sf::Keyboard::Up:
                        upPressed = false;
                    break;
                    case sf::Keyboard::Down:
                        downPressed = false;
                    break;
                }
            break;
            case sf::Event::Resized:
                float oldRatio = (float) width/height;
                float newRatio = (float) window.getSize().x/window.getSize().y;

                sf::View newView = window.getDefaultView();

                if(newRatio > oldRatio) {
                    int newWidth = window.getSize().x;
                    int newHeight = window.getSize().y;
                    float scaledWidth = newHeight * oldRatio;
                    float newCornerX = (newWidth - scaledWidth)/2.f;

                    newView.setViewport(sf::FloatRect(newCornerX/newWidth, 0.f, scaledWidth/newWidth, 1.f));
                } else if(newRatio < oldRatio) {
                    int newWidth = window.getSize().x;
                    int newHeight = window.getSize().y;
                    float scaledHeight = newWidth / oldRatio;
                    float newCornerY = (newHeight - scaledHeight)/2.f;

                    newView.setViewport(sf::FloatRect(0.f, newCornerY/newHeight, 1.f, scaledHeight/newHeight));
                }

                window.setView(newView);
            break;
        }

    }
};

void GameManager::playMusic() {
    bgm.play();
};