#ifndef ENTITY_H
#define ENTITY_H

#if __APPLE__
#include "ResourcePath.hpp"
#else
std::string resourcePath(void) { return ""; }
#endif

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

#include "AnimatedSprite.h"
#include "GameObjects.h"

class GameObjects;

class Entity
{

public:

    static const int SIDE_LEFT  = 1;
    static const int SIDE_RIGHT = 2;

    static const int STATE_STOPPED   = 1;
    static const int STATE_WALKING   = 2;
    static const int STATE_JUMPING   = 3;

    static const int ENTITY_TYPE_PLAYER = 1;
    static const int ENTITY_TYPE_GROUND = 2;

    b2Body* body;

    AnimatedSprite *sprite;
    sf::Texture *texture;
    int side;
    int state;
    int width;
    int height;
    int type;

    Entity();
    void createEntityPhysics(b2World& World, int posX, int posY, int width, int height);
    int getType();
    void update(sf::Time delta);
    void updateEvents(sf::Event event);
    void draw();

};

#endif // ENTITY_H
