#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "SFML/Audio.hpp"
#include "string"

class SoundManager
{
    public:
        SoundManager();
        ~SoundManager();

        void loadContent();
        void unloadContent();
        void playSound(int sound);
        void playMusic(std::string song);
        void stopMusic();
    protected:
    private:
        sf::Sound attack, grab, hurt, pickup, selectS, teleport, throwS;
        sf::SoundBuffer attackB, grabB, hurtB, pickupB, selectB, teleportB, throwSB;
        sf::Music music;
};

#endif // SOUNDMANAGER_H
