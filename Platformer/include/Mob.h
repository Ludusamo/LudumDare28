#ifndef MOB_H
#define MOB_H

#include <SFML/Graphics.hpp>
#include <Entity.h>
#include <Animation.h>
#include <iostream>
#include <math.h>

#define FRICTION 0.9

class Mob : public Entity {
public:
    Mob();
    ~Mob();

    virtual void load(sf::Vector2f pos, sf::Texture &texture, float MAX_VEL, sf::Vector2i mSize);
    virtual void unload();
    virtual void update(std::vector<std::vector<int>> colMap);
    void moveM(std::vector<std::vector<int>> colMap);

    void checkCollision(std::vector<std::vector<int>> colMap);

    void setAccelerationX(float a);
    void setAccelerationY(float a);
    void setVelocityX(float v);
    void setVelocityY(float v);

    void setTexCoords(int startX, int startY);

    sf::FloatRect &getBounds();

    void subtractHealth(float dmg);

    int getDir();
    int getCurrentState();
    void setCurrentState(int state);

    Animation &getAnimation();
    sf::FloatRect getCollision();
protected:
    // Physics
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float MAX_VEL;
    bool collided = false;

    // Graphics
    sf::Vector2i mSize;
    Animation animation;

    // Collision
    std::vector<sf::FloatRect> collidable;
    sf::FloatRect collision;
    sf::FloatRect bounds;
    int startX, endX, startY, endY;
    int bmX, bmY; // Bound x and y modifiers

    int currentState;

    // Attributes
    float health;
    bool invincible = false, flying = false;

    int currentDir;
    enum direction { UP, DOWN, LEFT, RIGHT };
private:
    void collidableTiles(std::vector<std::vector<int>> colMap, int startX, int endX, int startY, int endY);
    bool contains(sf::FloatRect x, sf::FloatRect y);
};

#endif // MOB_H
