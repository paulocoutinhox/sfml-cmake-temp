#include "Engine.h"

Engine::Engine()
{
    Util::log("Engine::Engine");
    resetRandom();
    setupScreen();
    setupBackgroundColor();

    showSampleContent = true;
}

Engine::~Engine()
{
    Util::log("Engine::~Engine");
}

void Engine::run()
{
    Util::log("Engine::run");

    GameObjects::gravity = new b2Vec2(0.f, 9.8f);
    GameObjects::world   = new b2World(*GameObjects::gravity);

    player = new Player();

    CreateGround(*GameObjects::world, 400.f, 500.f);

    initializeGraphics();

    sf::Sprite sampleSprite;
    sf::Texture sampleTexture;

    if (showSampleContent)
    {
        if (sampleTexture.loadFromFile(resourcePath() + "images/logo.png") != true)
        {
            Util::log("Cannot load texture: logo.png");
            return;
        }

        sampleSprite.setTexture(sampleTexture);
        sampleSprite.setPosition((screenWidth / 2) - (sampleSprite.getLocalBounds().width / 2), (screenHeight / 2) - (sampleSprite.getLocalBounds().height / 2));
    }

    sf::Texture BoxTexture;
    BoxTexture.loadFromFile(resourcePath() + "images/box.png");
    sf::Texture GroundTexture;
    GroundTexture.loadFromFile(resourcePath() + "images/ground.png");


    sf::Clock frameClock;

    while (GameObjects::window->isOpen())
    {
        sf::Time delta = frameClock.restart();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            int MouseX = sf::Mouse::getPosition(*GameObjects::window).x;
            int MouseY = sf::Mouse::getPosition(*GameObjects::window).y;
            CreateBox(*GameObjects::world, MouseX, MouseY);
        }
        GameObjects::world->Step(1/60.f, 8, 3);

        checkEvents();

        GameObjects::window->clear(backgroundColor);

        if (showSampleContent)
        {
            GameObjects::window->draw(sampleSprite);
        }

        player->update(delta);
        player->draw();

        /*
        int BodyCount = 0;
        for (b2Body* BodyIterator = GameObjects::world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if (BodyIterator->GetType() == b2_dynamicBody)
            {
                sf::Sprite Sprite;
                Sprite.setTexture(BoxTexture);
                Sprite.setOrigin(16.f, 16.f);
                Sprite.setPosition(GameObjects::SCALE * BodyIterator->GetPosition().x, GameObjects::SCALE * BodyIterator->GetPosition().y);
                Sprite.setRotation(BodyIterator->GetAngle() * 180/b2_pi);
                GameObjects::window->draw(Sprite);
                ++BodyCount;
            }
            else
            {
                sf::Sprite GroundSprite;
                GroundSprite.setTexture(GroundTexture);
                GroundSprite.setOrigin(400.f, 8.f);
                GroundSprite.setPosition(BodyIterator->GetPosition().x * GameObjects::SCALE, BodyIterator->GetPosition().y * GameObjects::SCALE);
                GroundSprite.setRotation(180/b2_pi * BodyIterator->GetAngle());
                GameObjects::window->draw(GroundSprite);
            }
        }
        */



        /*
        sf::RectangleShape rectangle(sf::Vector2f(playerSprite->getLocalBounds().width, playerSprite->getLocalBounds().height));
        rectangle.setFillColor(sf::Color(150, 50, 250));
        rectangle.setPosition(playerSprite->getPosition());
        rectangle.setOrigin(width/2.f,height/2.f);
        rectangle.setFillColor(sf::Color(255,0,0,100));
        GameObjects::window->draw(rectangle);
        */


        GameObjects::window->display();

        sf::sleep(sf::milliseconds(1));
    }
}

void Engine::initializeGraphics()
{
    Util::log("Engine::initializeGraphics");

    sf::ContextSettings settings;
    settings.depthBits = 0;
    settings.stencilBits = 0;
    settings.antialiasingLevel = 0;

    GameObjects::window = new sf::RenderWindow(sf::VideoMode(screenWidth, screenHeight, screenBitsPerPixel), screenTitle, sf::Style::Close, settings);
    GameObjects::window->setVerticalSyncEnabled(true);
}

void Engine::checkEvents()
{
    sf::Event Event;

    while (GameObjects::window->pollEvent(Event))
    {
        if (Event.type == sf::Event::Closed)
        {
            GameObjects::window->close();
            return;
        }

        player->updateEvents(Event);
    }

    player->updateEvents(Event);
}

void Engine::resetRandom()
{
    srand(time(NULL));
}

void Engine::setupScreen()
{
    screenWidth        = 800;
    screenHeight       = 600;
    screenBitsPerPixel = 32;
    screenTitle        = "Magic And Zombie";
}

void Engine::setupBackgroundColor()
{
    backgroundColor = sf::Color(0, 0, 0);
}

void Engine::CreateBox(b2World& World, int MouseX, int MouseY)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/GameObjects::SCALE, MouseY/GameObjects::SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.f/2)/GameObjects::SCALE, (32.f/2)/GameObjects::SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.3f;
    FixtureDef.restitution = 0.2;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

void Engine::CreateGround(b2World& World, float X, float Y)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/GameObjects::SCALE, Y/GameObjects::SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);
    Body->SetUserData((void*)Entity::ENTITY_TYPE_GROUND);

    b2PolygonShape Shape;
    Shape.SetAsBox((800.f/2)/GameObjects::SCALE, (16.f/2)/GameObjects::SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}
