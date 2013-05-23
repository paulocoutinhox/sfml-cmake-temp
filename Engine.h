#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>

#include "Util.h"
#include "Engine.h"
#include "Player.h"
#include "GameObjects.h"

#if __APPLE__
#include "ResourcePath.hpp"
#else
std::string resourcePath(void) { return ""; }
#endif

class Engine
{

public:

    Engine();
    ~Engine();

    void run();

private:

    int screenWidth;
    int screenHeight;
    int screenBitsPerPixel;
    std::string screenTitle;
    sf::Color backgroundColor;
    bool showSampleContent;

    Player *player;

    void initializeGraphics();
    void checkEvents();
    void resetRandom();
    void setupScreen();
    void setupBackgroundColor();

    void CreateGround(b2World& World, float X, float Y);
    void CreateBox(b2World& World, int MouseX, int MouseY);

};

#endif // ENGINE_H
