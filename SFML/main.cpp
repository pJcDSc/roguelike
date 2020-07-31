#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Collider.h"
#include "../Player.h"
#include "../Platform.h"

using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(512, 512), "Player Movement"); // Draws Window With Specified Attributes
    View view(Vector2f(0.0f, 0.0f), Vector2f(512.0f, 512.0f));

    RectangleShape player(Vector2f(60.0f, 60.0f)); // Creating Player Object And Sets It's Size
    player.setPosition(206.0f, 206.0f); // Sets Player Object's Start Position

    Texture playerTexture; // Creates Player Texture Object
    playerTexture.loadFromFile("Human_Player_Character.png"); // Loads Player Object Sprite From File
    player.setTexture(&playerTexture); // Sets The Texture To The Sprite Object

    Platform platform1(nullptr, Vector2f(400.0f, 200.0f), Vector2f(500.0f, 200.0f));
    Platform platform2(nullptr, Vector2f(400.0f, 200.0f), Vector2f(500.0f, 0.0f));


    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
        }
    if(Keyboard::isKeyPressed(Keyboard::Key::W)) // Specifies Which Key Controls Going Up
    {
        player.move(0.0f, -0.1f); // Moves Player Object Up
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::A)) // Specifies Which Key Controls Going Left
    {
        player.move(-0.1f, 0.0f); // Moves Player Object Left
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::S)) // Specifies Which Key Controls Going Down
    {
        player.move(0.0f, 0.1f); // Moves Player Object Down
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::D)) // Specifies Which Key Controls Going Right
    {
        player.move(0.1f, 0.0f); // Moves Player Object Right
    }


    platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);
    platform2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

        view.setCenter(player.getPosition());

        window.clear();
        window.draw(player);
        platform1.Draw(window);
        platform2.Draw(window);
        window.display(); // Draws Player Object On The Screen
    }

    return 0;
}
