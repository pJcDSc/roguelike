#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>
#include "Collider.h"

using namespace sf;

class Platform
{
public:
    Platform(Texture* texture, Vector2f size, Vector2f position);
    virtual ~Platform();

    void Draw(RenderWindow& window);
    Collider GetCollider() { return Collider(body); }


private:
    RectangleShape body;
};

#endif // PLATFORM_H
