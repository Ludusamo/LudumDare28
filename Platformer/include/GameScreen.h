#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "ScreenManager.h"
#include "FileManager.h"
#include "Level.h"
#include <SFML/Graphics.hpp>

class GameScreen : public Screen {
public:
    GameScreen();
    ~GameScreen();

    void loadContent();
    void unloadContent();
    void update();
    void render(sf::RenderWindow &window);
protected:
private:
    Level level;
    sf::Vector2f center;
    sf::View mainView;

    FileManager file;
    std::vector<std::vector<std::string>> attributes, contents;
};

#endif // GAMESCREEN_H
