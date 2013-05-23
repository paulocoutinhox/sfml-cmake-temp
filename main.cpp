#include "Engine.h"

int main()
{
    Engine *engine = new Engine();
    engine->run();

    return EXIT_SUCCESS;
}

/*
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Box2D/Box2D.h>
#include <SFML/OpenGL.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <iostream>


const float PPM = 32.0f;
const float MPP = 0.03125f;
const float pi  = 3.14159265358979323f;
const float R2D = 180.0f/pi;

//You can put me in a Header file instead of up here.
//I have a game class to help keep the game nice and clean
//by sending a pointer to any class that might need these public resources I.E Player Class
class Game
{
public:
    sf::RenderWindow *Window;
    sf::Event        *Event;
    sf::View         *Camera;
    sf::View         *Debug;
    b2World          *World;

    //Use this for TimeSteps with Box2D or anything you might want consistant on all machines time wise
    sf::Clock*     GameClock;
    sf::Time       m_NowTime;
    sf::Time       m_LastTime;
};

//You can put me in a Header file instead of up here.
//Biggest class on here and thats because its vital to the use of SFML and Box2D becasue OpenGL doesn't requires conversion of Metric to Pixels which SFML uses.
class RedDraw : public b2Draw
{
public:
    void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < vertexCount; ++i)
        {
            glVertex2f(vertices[i].x/MPP , vertices[i].y/MPP );
        }
        glEnd();
    }
    void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
    {
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
        for (int32 i = 0; i < vertexCount; ++i)
        {
            glVertex2f(vertices[i].x/MPP, vertices[i].y/MPP);
        }
        glEnd();
        glDisable(GL_BLEND);

        glColor4f(color.r, color.g, color.b, 1.0f);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < vertexCount; ++i)
        {
            glVertex2f(vertices[i].x/MPP, vertices[i].y/MPP);
        }
        glEnd();
    }
    void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
    {
        const float32 k_segments = 16.0f;
        const float32 k_increment = 2.0f * b2_pi / k_segments;
        float32 theta = 0.0f;
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < k_segments; ++i)
        {
            b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
            glVertex2f(v.x/MPP, v.y/MPP);
            theta += k_increment;
        }
        glEnd();
    }
    void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
    {
        const float32 k_segments = 16.0f;
        const float32 k_increment = 2.0f * b2_pi / k_segments;
        float32 theta = 0.0f;
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);
        glBegin(GL_TRIANGLE_FAN);
        for (int32 i = 0; i < k_segments; ++i)
        {
            b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta)/MPP);
            glVertex2f(v.x/MPP, v.y/MPP);
            theta += k_increment;
        }
        glEnd();
        glDisable(GL_BLEND);

        theta = 0.0f;
        glColor4f(color.r, color.g, color.b, 1.0f);
        glBegin(GL_LINE_LOOP);
        for (int32 i = 0; i < k_segments; ++i)
        {
            b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta)/MPP);
            glVertex2f(v.x/MPP, v.y/MPP);
            theta += k_increment;
        }
        glEnd();

        b2Vec2 p = center + radius * axis;
        glBegin(GL_LINES);
        glVertex2f(center.x/MPP, center.y/MPP);
        glVertex2f(p.x/MPP, p.y/MPP);
        glEnd();
    }
    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
    {
        glColor3f(color.r, color.g, color.b);//Box Green
        glBegin(GL_LINES);
        glVertex2f(p1.x/MPP, p1.y/MPP);
        glVertex2f(p2.x/MPP, p2.y/MPP);
        glEnd();
    }
    void DrawTransform(const b2Transform& xf)
    {
        b2Vec2 p1 = xf.p, p2;
        const float32 k_axisScale = 0.4f;
        glBegin(GL_LINES);

        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(p1.x/MPP, p1.y/MPP);
        p2 = p1 + k_axisScale * xf.q.GetXAxis();
        glVertex2f(p2.x/MPP, p2.y/MPP);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(p1.x/MPP, p1.y/MPP);
        p2 = p1 + k_axisScale * xf.q.GetYAxis();
        glVertex2f(p2.x/MPP, p2.y/MPP);

        glEnd();
    }
    void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
    {
        glPointSize(size);
        glBegin(GL_POINTS);
        glColor3f(color.r, color.g, color.b);
        glVertex2f(p.x, p.y);
        glEnd();
        glPointSize(1.0f);
    }
    void DrawAABB(b2AABB* aabb, const b2Color& color)
    {
        glColor3f(color.r, color.g, color.b);
        glBegin(GL_LINE_LOOP);
        glVertex2f(aabb->lowerBound.x, aabb->lowerBound.y);
        glVertex2f(aabb->upperBound.x, aabb->lowerBound.y);
        glVertex2f(aabb->upperBound.x, aabb->upperBound.y);
        glVertex2f(aabb->lowerBound.x, aabb->upperBound.y);
        glEnd();
    }
};

//You can put me in a Header file instead of up here.
//Actor class, The base class I derive anything from with polymorphism.
class Actor
{
public:
    virtual void init(double x, double y,double r,Game* game) = 0;
    virtual void HandleEvents(Game* game) = 0;
    virtual void Update(Game* game) = 0;
    virtual void Draw(Game* game) = 0;

    sf::Sprite Sprite;
    b2Body * m_body;

protected:
    sf::Image   Image;//Because there will be no texture file, I'm making one in game.
    sf::Texture Texture;
    sf::IntRect TextureRect;
};

int numFootContacts = 0;

//You can put me in a Header file instead of over here.
//You need a contact listener if you want to check if something is touching some other thing
//I use it for jumping
//Note that the code is taken from iforce2d
class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact)
    {

        //check if fixture A were the sensors
        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
        if(contact->GetFixtureB()->GetUserData() == 0)
        {
            if ( (intptr_t)fixtureUserData == 1 )//Foot
                numFootContacts++;
        }
        //check if fixture B was the foot sensor
        fixtureUserData = contact->GetFixtureB()->GetUserData();
        if(contact->GetFixtureA()->GetUserData() == 0)
        {
            if ( (intptr_t)fixtureUserData == 1 )//Foot
                numFootContacts++;
        }
    }

    void EndContact(b2Contact* contact)
    {
        //check if fixture A was the foot sensor
        void* fixtureUserData = contact->GetFixtureA()->GetUserData();
        if(contact->GetFixtureB()->GetUserData() == 0)
        {
            if ( (intptr_t)fixtureUserData == 1 )//foot
                numFootContacts--;
        }
        //check if fixture B was the foot sensor
        fixtureUserData = contact->GetFixtureB()->GetUserData();
        if(contact->GetFixtureA()->GetUserData() == 0)
        {
            if ( (intptr_t)fixtureUserData == 1 )//You
                numFootContacts--;
        }
    }


};


//You can put me in a Header file instead of over here.
//Player Class
class Player : public Actor
{
public:
    void init(double x, double y,double r,Game* game)
    {
        b2BodyDef        Definition;    //Use this to descibe the body before making it.
        b2PolygonShape   Shape;         //This describes the shape of said player
        b2FixtureDef     Fixture;       //Desribes small things like density or if its a sensor
        b2Fixture       *footSensorFixture;
        Shape.SetAsBox(0.5f,0.5f);            //Its a sqaure
        Fixture.shape = &Shape;          //Applaying fixture shape
        Fixture.density = 75.0f;        //Density
        Fixture.friction = 0.10f;        //Friction
        Definition.type = b2_dynamicBody;//If you want the object to move
        Definition.gravityScale = 3;     //You can multiply the amount of gravity of a object, 0 = unchanged, More than 0 - More Gravity, Less than 0 - Less Gravity
        Definition.position.Set(x,y);   //Set position
        Definition.angle = r;           //Not required but its nice to have all things working

        m_body = game->World->CreateBody(&Definition);
        m_body->SetFixedRotation(true); //So the player will stay upright
        m_body->SetSleepingAllowed(false);//Has to do with optimization of misc object but because its the player it has to be awake.

        m_body->CreateFixture(&Fixture);

        //add foot sensor fixture for jumping
        Shape.SetAsBox(0.50f,0.10f,b2Vec2(0,0.5f), 0);
        Fixture.isSensor = true;
        footSensorFixture = m_body->CreateFixture(&Fixture);
        footSensorFixture->SetUserData( (void*)1 );//Its a signal to say that the player is touching the ground or multiple contact with its feet.

        Image.create(1*PPM,1*PPM,sf::Color::Red);
        Texture.loadFromImage(Image);
        Sprite.setTexture(Texture);
        //Very important that you set the orgin to anything to be the center
        //Box2D returns locations of all Physics objects to thier center so you need to make SFML does the same.
        Sprite.setOrigin(Sprite.getGlobalBounds().width /2, Sprite.getGlobalBounds().height/2);
    }
    void HandleEvents(Game* game)
    {
        float32 Delta = (game->m_NowTime.asSeconds() - game->m_LastTime.asSeconds());
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            Player::m_body->ApplyLinearImpulse(b2Vec2(1000.0f*Delta,0),m_body->GetPosition());
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            Player::m_body->ApplyLinearImpulse(b2Vec2(-1000.0f*Delta,0),m_body->GetPosition());
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && numFootContacts > 0)
        {
            Player::m_body->ApplyLinearImpulse(b2Vec2(0,-16000.0f*Delta),m_body->GetPosition());
        }
    }
    void Update(Game* game)
    {
        Sprite.setRotation( m_body->GetAngle() * R2D);//You have to convert Radians to Degrees for SFML(Hence R2D)
        Sprite.setPosition( m_body->GetPosition().x*PPM, m_body->GetPosition().y*PPM);//You have to convert Meters to Pixels(hence PPM)
    }
    void Draw(Game* game)
    {
        game->Window->draw(Sprite);
    }
};

class Tile : public Actor
{
public:
    void init(double x, double y,double r,Game* game)
    {
        b2BodyDef        Definition;    //Use this to descibe the body before making it.
        b2PolygonShape   Shape;         //This describes the shape of said player
        b2FixtureDef     Fixture;       //Desribes small things like density or if its a sensor
        Shape.SetAsBox(2,2);            //Its a sqaure
        Fixture.shape = &Shape;          //Applaying fixture shape
        Fixture.density = 75.0f;        //Density
        Definition.position.Set(x,y);   //Set position
        Definition.angle = r;           //Not required but its nice to have all things working

        m_body = game->World->CreateBody(&Definition);
        m_body->CreateFixture(&Fixture);

        Image.create(4*PPM,4*PPM,sf::Color::Blue);
        Texture.loadFromImage(Image);
        Sprite.setTexture(Texture);
        //Very important that you set the orgin to anything to be the center
        //Box2D returns locations of all Physics objects to thier center so you need to make SFML does the same.
        Sprite.setOrigin(Sprite.getGlobalBounds().width /2, Sprite.getGlobalBounds().height/2);
        Sprite.setRotation( m_body->GetAngle() * R2D);//You have to convert Radians to Degrees for SFML(Hence R2D)
        Sprite.setPosition( m_body->GetPosition().x*PPM, m_body->GetPosition().y*PPM);//You have to convert Meters to Pixels(hence PPM)
    }
    void HandleEvents(Game* game)
    {
        //Its a tile and requires no such thing as events so we leave it blank
    }
    void Update(Game* game)
    {
        //Same goes here.
    }
    void Draw(Game* game)
    {
        game->Window->draw(Sprite);
    }
};

std::string convertInt(int number)
{
    std::stringstream ss;//create a stringstream
    ss << number;//add number to the stream
    return ss.str();//return a string with the contents of the stream
}

MyContactListener myContactListenerInstance;
RedDraw DebugDraw;
int main()
{
    Game NewGame;
    NewGame.Window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML works with Box2D!");
    NewGame.Event  = new sf::Event;
    NewGame.World  = new b2World(b2Vec2(0,9.8f));//Gravity!
    NewGame.Camera = new sf::View();
    NewGame.Debug  = new sf::View();
    NewGame.GameClock = new sf::Clock;

    NewGame.World->SetDebugDraw( &DebugDraw);
    DebugDraw.SetFlags( b2Draw::e_shapeBit + b2Draw::e_centerOfMassBit);

    NewGame.World->SetContactListener(&myContactListenerInstance);//Setting the contact listener for the players jumping abilities


    //FPS shows up as the Title for the window
    int m_FPS = 0;
    sf::Clock FPSTimer;

    //Bool to turn DebugDraw on and off... FYI its F3 turn it off and on
    bool ShowDebugDraw = 0;

    //Timestep related
    float timePassed = 0;


    //Lets make a level with a player and some tiles

    const int HowManyActors = 4;
    Actor *Actors[HowManyActors];

    Actors[0] = new Player;
    Actors[0]->init(1.0f,-3.0f,0.0f,&NewGame);

    Actors[1] = new Tile;
    Actors[1]->init(0,3.0f,0,&NewGame);

    Actors[2] = new Tile;
    Actors[2]->init(4.0f,3.0f,0,&NewGame);

    Actors[3] = new Tile;
    Actors[3]->init(-4.0f,3.0f,0,&NewGame);

    while (NewGame.Window->isOpen())
    {
        NewGame.m_LastTime = NewGame.m_NowTime;
        NewGame.m_NowTime  = NewGame.GameClock->getElapsedTime();

        if(NewGame.m_NowTime == sf::seconds(1))//To keep the Clock from over flowing
            NewGame.GameClock->restart();

        timePassed += (NewGame.m_NowTime.asSeconds() - NewGame.m_LastTime.asSeconds());
        while(timePassed > 1/60.0 )
        {
            NewGame.World->Step(1/60.0,10,10);
            timePassed -= 1/60.0;
        }

        m_FPS++;
        if(FPSTimer.getElapsedTime() >= sf::seconds(1))
        {
            NewGame.Window->setTitle("SFML works with Box2D! FPS:" + convertInt(m_FPS));
            m_FPS = 0;
            FPSTimer.restart();
        }

        while (NewGame.Window->pollEvent(*NewGame.Event))
        {
            if (NewGame.Event->type == sf::Event::Closed)
                NewGame.Window->close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
            {
                if(ShowDebugDraw == true)
                {
                    ShowDebugDraw = false;
                }
                else
                {
                    ShowDebugDraw = true;
                }
                std::cout << "Toggled ShowDebugDraw: " << ShowDebugDraw << std::endl;
            }
        }

        NewGame.Window->clear(sf::Color::Transparent);

        NewGame.Camera->setCenter(Actors[0]->Sprite.getPosition());
        NewGame.Camera->setSize(NewGame.Window->getSize().x,NewGame.Window->getSize().y);
        NewGame.Window->setView(*NewGame.Camera);

        int E=0;
        while(Actors[E])
        {

            Actors[E]->HandleEvents(&NewGame);
            Actors[E]->Update(&NewGame);
            Actors[E]->Draw(&NewGame);
            E++;

            if(E == HowManyActors)
                break;
        }

        if(ShowDebugDraw == true)
        {
            NewGame.Window->setView(*NewGame.Camera);
            glMatrixMode(GL_PROJECTION);
            glLoadMatrixf(NewGame.Camera->getTransform().getMatrix());
            NewGame.World->DrawDebugData();
            NewGame.Window->resetGLStates();
        }

        NewGame.Window->display();
    }

    return 0;
}
*/
