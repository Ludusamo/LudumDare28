#include "GameScreen.h"

GameScreen::GameScreen() {
    //ctor
}

GameScreen::~GameScreen() {
    //dtor
}

void GameScreen::loadContent() {
    level.load();

    if (level.getPlayer().getPosition().x - (WIDTH / SCALE / 2) < 0) center.x = (WIDTH / SCALE / 2);
    else if (level.getPlayer().getPosition().x + (WIDTH / SCALE / 2) > (level.getWidth() * TILE_SIZE)) center.x = (level.getWidth() * TILE_SIZE) - (WIDTH / SCALE / 2);
    else center.x = level.getPlayer().getPosition().x;
    if (level.getPlayer().getPosition().y - (HEIGHT / SCALE / 2) < 0) center.y = (HEIGHT / SCALE / 2);
    else if (level.getPlayer().getPosition().y + (HEIGHT / SCALE / 2) > (level.getHeight() * TILE_SIZE)) center.y = (level.getHeight() * TILE_SIZE) - (WIDTH / SCALE / 2);
    else center.y = level.getPlayer().getPosition().y;

    sound.loadContent();
    sound.playMusic("song");

    font.loadFromFile("res/fonts/Bellerose.ttf");
    text.setFont(font);
    instructions = "Instructions: WASD For Directional H For Attack (Useless) J For Throw K For Teleport L For Grab *You Teleport With 1 Block Distance Between You And The Rock *You Grab With Two Blocks Distance Between You And The Rock";
    text.setString(instructions);
    text.setCharacterSize(9);
    text.setPosition(0, 0);
}

void GameScreen::unloadContent() {
    Screen::unloadContent();
    level.unload();
}

void GameScreen::update() {
    level.update(input, sound);
    if (level.isGameOver()) {
        ScreenManager::getInstance().addScreen(new MainMenuScreen);
        sound.stopMusic();
    }

    if (level.getPlayer().getPosition().x - (WIDTH / SCALE / 2) < 0) center.x = (WIDTH / SCALE / 2);
    else if (level.getPlayer().getPosition().x + (WIDTH / SCALE / 2) > (level.getWidth() * TILE_SIZE)) center.x = (level.getWidth() * TILE_SIZE) - (WIDTH / SCALE / 2);
    else center.x = level.getPlayer().getPosition().x;
    if (level.getPlayer().getPosition().y - (HEIGHT / SCALE / 2) < 0) center.y = (HEIGHT / SCALE / 2);
    else if (level.getPlayer().getPosition().y + (HEIGHT / SCALE / 2) > (level.getHeight() * TILE_SIZE)) center.y = (level.getHeight() * TILE_SIZE) - (HEIGHT / SCALE / 2);
    else center.y = level.getPlayer().getPosition().y;

    if (input.keyPressed(sf::Keyboard::Escape)) {
        if (pause) pause = false;
        else pause = true;
    }
}

void GameScreen::render(sf::RenderWindow &window) {
    level.render(window);
    if (pause) {
        window.clear();
        window.draw(text);
    }
    mainView = window.getDefaultView();
    if (!level.isSwitching() && !pause) mainView.setCenter(center);
    else mainView.setCenter(200, 150);
    mainView.zoom(1 / SCALE);
    window.setView(mainView);
    if (level.isReading()) {
        signView = window.getDefaultView();
        signView.setCenter(200, 150);
        signView.zoom(1 / SCALE);
        window.setView(signView);
    }
}
