#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ScreenManager.h"
#include "TileData.h"
#include "MapGenerator.h"
#include "Node.h"
#include "Charger.h"

int main() {
    MapGenerator test("res/lvls/1.comp");
    std::vector<std::vector<int16_t> > testvec = test.generate(10, 10, 0.2f);
    for(int i = 0; i < testvec.size(); i++) {
        for(int j = 0; j < testvec[0].size(); j++) {
            std::cout << testvec[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::pair<uint32_t,uint32_t> pos1, pos2;
    for(int i = 0; i < 10; i++)
    if(testvec[1][i] == 2) {
        pos1.first = 1;
        pos1.second = i;
        break;
    }
    for(int i = 9; i >= 0; i--)
    if(testvec[8][i] == 2) {
        pos2.first = 8;
        pos2.second = i;
        break;
    }

    Charger charger;
    std::vector<Node> test_path = charger.pathfind(pos1.first, pos1.second, pos2.first, pos2.second, testvec);
    for(int i = 0; i < test_path.size(); i++)
        std::cout << test_path[i].x << " " << test_path[i].y << std::endl;


    // Window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT, 32), "SFML Platformer");

    // Window Manager
    ScreenManager::getInstance().initialize();
    ScreenManager::getInstance().loadContent();

    // Timing
    sf::Clock clock;
    float delta;
    const int ups = 60; // Updates Per Second

    // Main Game Loop
    while (window.isOpen()) {
        sf::Event event;

        if (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Resets the Window
        window.clear();

        // Timing
        delta += clock.restart().asSeconds();

        // Update and Render Cycles: CURRENTLY LIMITED AT 60 UPS
        if (delta >= 1 / ups) {
            ScreenManager::getInstance().update(window);
            ScreenManager::getInstance().render(window);
            delta = 0;
        }

        // Just Displays the Screen
        window.display();
    }

    return 0;
}
