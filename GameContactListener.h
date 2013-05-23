#ifndef GAMECONTACTLISTENER_H
#define GAMECONTACTLISTENER_H

#include <Box2D/Box2D.h>

#include "Entity.h"

class GameContactListener : public b2ContactListener
{

public:
    virtual void BeginContact(b2Contact *contact);
    virtual void EndContact(b2Contact *contact);

};

#endif // GAMECONTACTLISTENER_H
