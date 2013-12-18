#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "Screen.h"
#include "ScreenManager.h"
#include "FileManager.h"
#include <SFML/Graphics.hpp>
#include "CreditsScreen.h"

class MainMenuScreen : public Screen {
public:
    MainMenuScreen();
    ~MainMenuScreen();

    void loadContent();
    void unloadContent();
    void update();
    void render(sf::RenderWindow &window);
protected:
private:
    sf::Text text, title;
    sf::Font font;
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::Keyboard::Key> confirm;
};

#endif // MAINMENUSCREEN_H
