#include "GameScreen.h"

GameScreen::GameScreen() {
    //ctor
}

GameScreen::~GameScreen() {
    //dtor
}

void GameScreen::loadContent() {
    level.load();
    level.loadLevel("res/imgs/Tilesheet_A.png", "hub.png");

    if (level.getPlayer().getPosition().x - (WIDTH / SCALE / 2) < 0) center.x = (WIDTH / SCALE / 2);
    else if (level.getPlayer().getPosition().x + (WIDTH / SCALE / 2) > (level.getWidth() * TILE_SIZE)) center.x = (level.getWidth() * TILE_SIZE) - (WIDTH / SCALE / 2);
    else center.x = level.getPlayer().getPosition().x;
    if (level.getPlayer().getPosition().y - (HEIGHT / SCALE / 2) < 0) center.y = (HEIGHT / SCALE / 2);
    else if (level.getPlayer().getPosition().y + (HEIGHT / SCALE / 2) > (level.getHeight() * TILE_SIZE)) center.y = (level.getHeight() * TILE_SIZE) - (WIDTH / SCALE / 2);
    else center.y = level.getPlayer().getPosition().y;

    sound.loadContent();
    sound.playMusic("song");
}

void GameScreen::unloadContent() {
    level.unload();
}

void GameScreen::update() {
    level.update(input, sound);

    if (level.getPlayer().getPosition().x - (WIDTH / SCALE / 2) < 0) center.x = (WIDTH / SCALE / 2);
    else if (level.getPlayer().getPosition().x + (WIDTH / SCALE / 2) > (level.getWidth() * TILE_SIZE)) center.x = (level.getWidth() * TILE_SIZE) - (WIDTH / SCALE / 2);
    else center.x = level.getPlayer().getPosition().x;
    if (level.getPlayer().getPosition().y - (HEIGHT / SCALE / 2) < 0) center.y = (HEIGHT / SCALE / 2);
    else if (level.getPlayer().getPosition().y + (HEIGHT / SCALE / 2) > (level.getHeight() * TILE_SIZE)) center.y = (level.getHeight() * TILE_SIZE) - (HEIGHT / SCALE / 2);
    else center.y = level.getPlayer().getPosition().y;
}

void GameScreen::render(sf::RenderWindow &window) {
    level.render(window);
    mainView = window.getDefaultView();
    mainView.setCenter(center);
    mainView.zoom(1 / SCALE);
    window.setView(mainView);
    if (level.isReading()) {
        signView = window.getDefaultView();
        signView.setCenter(200, 150);
        signView.zoom(1 / SCALE);
        window.setView(signView);
    }
}
