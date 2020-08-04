#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Collision.h"

using namespace sf;
using namespace std;

int main( )
{
    RenderWindow window(VideoMode(512, 512), "Collision Detection");

    Texture playerTexture;
    Collision::CreateTextureAndBitmask(playerTexture, "Human_Player_Character.png");

    Texture caveWallTexture;
    Collision::CreateTextureAndBitmask(caveWallTexture, "Cave_Wall.png");

    Sprite playerCharacter;
    playerCharacter.setTexture(playerTexture);

    Sprite caveWall;
    caveWall.setTexture(caveWallTexture);

    caveWall.setPosition(window.getSize().x / 2 - caveWall.getLocalBounds().width / 2, window.getSize().y / 2 - caveWall.getLocalBounds().height / 2);

    while(window.isOpen())
    {
        Event event;

        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case Event::Closed:
                    window.close();
                break;
            }
        }


        if(Keyboard::isKeyPressed(Keyboard::Key::W)) // Specifies Which Key Controls Going Up
        {
            playerCharacter.move(0.0f, -0.1f); // Moves Player Object Up
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::A)) // Specifies Which Key Controls Going Left
        {
            playerCharacter.move(-0.1f, 0.0f); // Moves Player Object Left
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::S)) // Specifies Which Key Controls Going Down
        {
            playerCharacter.move(0.0f, 0.1f); // Moves Player Object Down
        }
        if(Keyboard::isKeyPressed(Keyboard::Key::D)) // Specifies Which Key Controls Going Right
        {
            playerCharacter.move(0.1f, 0.0f); // Moves Player Object Right
        }


        if (Collision::PixelPerfectTest(playerCharacter, caveWall) ) // Check Whether The Sprites Have Actually Collided Using Pixel Perfect Collision Detection
        {
            cout << "The Sprites Have Collided" << endl;
        }

        window.clear();
        window.draw(playerCharacter);
        window.draw(caveWall);
        window.display();
    }

    return 0;
}
