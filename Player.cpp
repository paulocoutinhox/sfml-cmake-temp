#include "Player.h"

Player::Player()
{
    width  = 40;
    height = 56;

    texture = new sf::Texture();
    texture->loadFromFile(resourcePath() + "images/player1.png");

    walkingAnimation = new Animation();
    walkingAnimation->setSpriteSheet(*texture);
    walkingAnimation->addFrame(sf::IntRect(0, 2*height, width, height));
    walkingAnimation->addFrame(sf::IntRect(1*width, 2*height, width, height));
    walkingAnimation->addFrame(sf::IntRect(2*width, 2*height, width, height));
    walkingAnimation->addFrame(sf::IntRect(3*width, 2*height, width, height));

    stoppedAnimation = new Animation();
    stoppedAnimation->setSpriteSheet(*texture);
    stoppedAnimation->addFrame(sf::IntRect(0, 2*height, width, height));

    jumpingAnimation = new Animation();
    jumpingAnimation->setSpriteSheet(*texture);
    jumpingAnimation->addFrame(sf::IntRect(0, 2*height, width, height));

    sprite = new AnimatedSprite(sf::seconds(0.2));
    sprite->setAnimation(*stoppedAnimation);
    //sprite->setColor(sf::Color::Red);
    sprite->setOrigin(width/2.f,height/2.f);

    createEntityPhysics(*GameObjects::world, 50, 50, width, height);
}

void Player::updateEvents(sf::Event event)
{
    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::W)
        {
            float impulse = body->GetMass() * 6;
            body->SetAwake(true);
            body->ApplyLinearImpulse( b2Vec2(0,-impulse), body->GetWorldCenter() );
            sprite->setAnimation(*jumpingAnimation);
            state = Entity::STATE_JUMPING;
        }

        if (event.key.code == sf::Keyboard::A)
        {
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 0;
            body->SetLinearVelocity(vel);
            sprite->setAnimation(*stoppedAnimation);
            state = Entity::STATE_STOPPED;
        }

        if (event.key.code == sf::Keyboard::D)
        {
            b2Vec2 vel = body->GetLinearVelocity();
            vel.x = 0;
            body->SetLinearVelocity(vel);
            sprite->setAnimation(*stoppedAnimation);
            state = Entity::STATE_STOPPED;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = -3;
        body->SetAwake(true);
        body->SetLinearVelocity(vel);

        if (side != Entity::SIDE_LEFT)
        {
            side = Entity::SIDE_LEFT;
            sprite->setScale(-1, 1);
        }

        if (state != Entity::STATE_WALKING && state != Entity::STATE_JUMPING)
        {
            state = Entity::STATE_WALKING;
            sprite->setAnimation(*walkingAnimation);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        b2Vec2 vel = body->GetLinearVelocity();
        vel.x = 3;
        body->SetAwake(true);
        body->SetLinearVelocity(vel);

        if (side != Entity::SIDE_RIGHT)
        {
            side = Entity::SIDE_RIGHT;
            sprite->setScale(1, 1);
        }

        if (state != Entity::STATE_WALKING && state != Entity::STATE_JUMPING)
        {
            state = Entity::STATE_WALKING;
            sprite->setAnimation(*walkingAnimation);
        }
    }
}
