#include <iostream>
#include "MainMenuScreen.h"

MainMenuScreen::MainMenuScreen() {
    //ctor
}

MainMenuScreen::~MainMenuScreen() {
    //dtor
}

void MainMenuScreen::loadContent() {
    if (!font.loadFromFile("res/fonts/Bellerose.ttf"))
        std::cout << "Could Not Find Specified Font." << std::endl;

    text.setFont(font);
    text.setString("Click Return To Start");
    text.setPosition(280, 500);
    title.setFont(font);
    title.setString("Vita");
    title.setPosition(375, 200);

    confirm.push_back(sf::Keyboard::Return);
    confirm.push_back(sf::Keyboard::Space);

    texture.loadFromFile("res/imgs/mainmenu.png");
    sprite.setTexture(texture);

    sound.loadContent();
    sound.playMusic("hub");
}

void MainMenuScreen::unloadContent() {
    Screen::unloadContent();
    sound.unloadContent();
}

void MainMenuScreen::update() {
    if (input.keyPressed(confirm))
        ScreenManager::getInstance().addScreen(new GameScreen);
}

void MainMenuScreen::render(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(text);
    window.draw(title);
}
