#include "SoundManager.h"

SoundManager::SoundManager()
{
    //ctor
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::loadContent() {
    std::string x = "res/sounds/";
    std::string y = ".wav";
    attackB.loadFromFile(x + "attack" + y);
    grabB.loadFromFile(x + "grab" + y);
    hurtB.loadFromFile(x + "hurt" + y);
    pickupB.loadFromFile(x + "pickup" + y);
    selectB.loadFromFile(x + "select" + y);
    teleportB.loadFromFile(x + "teleport" + y);
    throwSB.loadFromFile(x + "throw" + y);
    attack.setBuffer(attackB);
    grab.setBuffer(grabB);
    hurt.setBuffer(hurtB);
    pickup.setBuffer(pickupB);
    selectS.setBuffer(selectB);
    teleport.setBuffer(teleportB);
    throwS.setBuffer(throwSB);
}

void SoundManager::unloadContent() {
    stopMusic();
}

void SoundManager::playSound(int sound) {
    switch (sound) {
    case 0:
        attack.play();
        break;
    case 1:
        grab.play();
        break;
    case 2:
        hurt.play();
        break;
    case 3:
        pickup.play();
        break;
    case 4:
        selectS.play();
        break;
    case 5:
        teleport.play();
        break;
    case 6:
        throwS.play();
        break;
    }
}

void SoundManager::playMusic(std::string song) {
    music.openFromFile("res/sounds/" + song + ".wav");
    music.setLoop(true);
    music.play();
}

void SoundManager::stopMusic() {
    music.stop();
}
