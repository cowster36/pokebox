#ifndef POKEMON
#define POKEMON

#include <SFML/Graphics.hpp>
#include <string>

class Pokemon {
private:
    int existenceTimer = 0;
public:
    std::string name;
    std::string ability;
    int level;
    
    sf::Sprite icon;
    sf::Sprite hd;
    std::vector<sf::Texture *> hdTexs;

    Pokemon();
    Pokemon(std::string, std::string, int, sf::Texture *, sf::Texture * = NULL, sf::Texture * = NULL);

    void renderIcon(sf::RenderWindow & window, sf::Vector2f pos);
    void renderHD(sf::RenderWindow & window, sf::Vector2f pos);
    void resetExistenceTimer();

};

#endif