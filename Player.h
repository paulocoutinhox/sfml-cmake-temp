#ifndef PLAYER_H
#define PLAYER_H

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
#include "Entity.h"

class Player : public Entity
{

public:

    Player();
    void updateEvents(sf::Event event);

private:

    Animation *walkingAnimation;
    Animation *stoppedAnimation;
    Animation *jumpingAnimation;

};

#endif // PLAYER_H
