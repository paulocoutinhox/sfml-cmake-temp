#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

class GameObjects
{

public:
    static const float SCALE = 30.0f;
    static b2Vec2 *gravity;
    static b2World *world;
    static sf::RenderWindow *window;

};

#endif // GAMEOBJECTS_H
