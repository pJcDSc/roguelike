#ifndef PLAYER_H
#define PLAYER_H
#include "Collider.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
public:
    Player(RectangleShape& body);
    virtual ~Player();

    Vector2f GetPosition() { return body.getPosition(); }

    Collider GetCollider() { return Collider(body); }

private:
    RectangleShape body;
};

#endif // PLAYER_H
