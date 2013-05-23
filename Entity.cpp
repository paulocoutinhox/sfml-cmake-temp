#include "Entity.h"

Entity::Entity()
{
}

void Entity::createEntityPhysics(b2World &World, int posX, int posY, int width, int height)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(posX/GameObjects::SCALE, posY/GameObjects::SCALE);
    BodyDef.type = b2_dynamicBody;
    body = World.CreateBody(&BodyDef);
    body->SetUserData(this);
    body->SetFixedRotation(true);

    b2PolygonShape Shape;
    Shape.SetAsBox((width/2)/GameObjects::SCALE, (height/2)/GameObjects::SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.0f;
    FixtureDef.friction = 0.9f;
    FixtureDef.shape = &Shape;
    body->CreateFixture(&FixtureDef);
}

int Entity::getType()
{
    return type;
}

void Entity::update(sf::Time delta)
{
    sprite->update(delta);
    sprite->setPosition(GameObjects::SCALE * body->GetPosition().x, GameObjects::SCALE * body->GetPosition().y);
    sprite->setRotation(body->GetAngle() * 180/b2_pi);
}

void Entity::updateEvents(sf::Event event)
{
}

void Entity::draw()
{
    GameObjects::window->draw(*sprite);
}
