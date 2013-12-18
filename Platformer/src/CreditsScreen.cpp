#include "CreditsScreen.h"

CreditsScreen::CreditsScreen()
{
    //ctor
}

CreditsScreen::~CreditsScreen()
{
    //dtor
}

void CreditsScreen::loadContent() {
    tex.loadFromFile("res/imgs/credits.png");
    sprite.setTexture(tex);
    sprite.setPosition(0, 0);

    sound.loadContent();
    sound.playMusic("hub");
}

void CreditsScreen::unloadContent() {
    sound.unloadContent();
}

void CreditsScreen::update() {

}

void CreditsScreen::render(sf::RenderWindow& window) {
    window.clear();
    view = window.getDefaultView();
    view.setCenter(400, 300);
    view.zoom(1);
    window.setView(view);
    window.draw(sprite);
}
