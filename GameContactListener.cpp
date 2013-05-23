#include "GameContactListener.h"

void GameContactListener::BeginContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyAUserData && bodyBUserData)
    {
        Entity *entityA = static_cast<Entity*>(bodyAUserData);
        Entity *entityB = static_cast<Entity*>(bodyBUserData);

        if (entityA->getType() == Entity::ENTITY_TYPE_PLAYER && entityB->getType() == Entity::ENTITY_TYPE_GROUND)
        {

        }

        if (entityA->getType() == Entity::ENTITY_TYPE_GROUND && entityB->getType() == Entity::ENTITY_TYPE_PLAYER)
        {

        }
    }
}

void GameContactListener::EndContact(b2Contact* contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

    if (bodyAUserData && bodyBUserData)
    {
        Entity *entityA = static_cast<Entity*>(bodyAUserData);
        Entity *entityB = static_cast<Entity*>(bodyBUserData);

        if (entityA->getType() == Entity::ENTITY_TYPE_PLAYER && entityB->getType() == Entity::ENTITY_TYPE_GROUND)
        {

        }

        if (entityA->getType() == Entity::ENTITY_TYPE_GROUND && entityB->getType() == Entity::ENTITY_TYPE_PLAYER)
        {

        }
    }
}
