// this is for the move controls with a player sprite
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(VideoMode(400, 400), "Roguelike");

	// these are used later to slow down movement (can't hold down a key and move)
	bool isWPressed = false;
	bool isAPressed = false;
	bool isSPressed = false;
	bool isDPressed = false;

	// this is a rectangle background thing, it's white for now so we can see the text
	RectangleShape background;
	background.setSize(Vector2f(400, 400));
	background.setPosition(0, 0);
	background.setFillColor(Color(255, 255, 255));

	const int tileSize = 10; // number of units things should be moving. we'll probably change it and it'll be used a lot so it's easier to make it a variable

	// loading sprite sheet
	Texture playerTexture;
	playerTexture.loadFromFile("Human_Player_Character.png"); // loading sprite sheet

	// setting up sprite
	Sprite playerSprite;
	playerSprite.setTexture(playerTexture); // here's the image loading thing
	// playerSprite.setOrigin(1, 14); // origin (which part of the sprite
	playerSprite.setPosition(200, 200);

	while (window.isOpen()) {
		Event event;

		// window closing stuff
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			
			// if key is released check if it's control key and if so reset that bool so that things can be pressed again
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::W) {
					isWPressed = false;
				}
				if (event.key.code == Keyboard::A) {
					isAPressed = false;
				}
				if (event.key.code == Keyboard::S) {
					isSPressed = false;
				}
				if (event.key.code == Keyboard::D) {
					isDPressed = false;
				}
			}
		}
		
		window.clear();

		// if no keys are currently being pressed because being able to hold a key down and move just seemed weird somehow (this can be changed to make that allowed, I don't really care)
		if ((isWPressed == false) && (isAPressed == false) && (isSPressed == false) && (isDPressed == false)) {
			// moves player (tile size) units up if W key is pressed
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				isWPressed = true;
				playerSprite.move(0, -1 * tileSize); // there are other ways to do this (like a get position, set position thing) but this is shorter
			}
			// moves player (tile size) units left if A key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::A)) { // else if because player should only move in one direction at a time
				isAPressed = true;
				playerSprite.move(-1 * tileSize, 0);
			}
			// moves player (tile size) units down if S key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				isSPressed = true;
				playerSprite.move(0, tileSize);
			}
			// moves player (tile size) units right if D key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				isDPressed = true;
				playerSprite.move(tileSize, 0);
			}
		}

		window.draw(background);
		window.draw(playerSprite);

		window.display();
	}
}