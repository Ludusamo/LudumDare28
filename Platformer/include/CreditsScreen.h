#ifndef CREDITSSCREEN_H
#define CREDITSSCREEN_H

#include "Screen.h"
#include "SFML/Graphics.hpp"
#include "Player.h"

class CreditsScreen : public Screen {
    public:
        CreditsScreen();
        ~CreditsScreen();

        void loadContent();
        void unloadContent();
        void update();
        void render(sf::RenderWindow &window);
    protected:
    private:
        sf::Sprite sprite;
        sf::Texture tex;
        sf::View view;
};

#endif // CREDITSSCREEN_H
