// this is for the monster movement and player movement controls
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace sf;

int main() {
	// dimensions
	const int windowX = 400;
	const int windowY = 400;

	RenderWindow window(VideoMode(windowX, windowY), "Roguelike");
	window.setFramerateLimit(10);

	// these are used later to slow down movement (can't hold down a key and move)
	bool isWPressed = false;
	bool isAPressed = false;
	bool isSPressed = false;
	bool isDPressed = false;

	int spiderDirection = rand() % 4;
	int dogDirection = rand() % 4;
	int batsDirection = rand() % 4;
	int bearDirection = rand() % 4;
	int humanDirection = rand() % 4;

	int room = 1;
	const int tileX = 10; // number of units sprites should be moving side to side
	const int tileY = 10; // number of units sprites should be moving up and down
	int marginX = 15 + tileX;
	int marginY = 15 + tileY;

	// this is a rectangle background thing, it's white for now so we can see the sprites
	RectangleShape background;
	background.setSize(Vector2f(windowX, windowY));
	background.setPosition(0, 0);
	background.setFillColor(Color(255, 255, 255));

	// player sprite setup
	// loading sprite sheet
	Texture playerTexture;
	playerTexture.loadFromFile("Human_Player_Character.png"); // loading sprite sheet
	// setting up sprite
	Sprite playerSprite;
	playerSprite.setTexture(playerTexture); // here's the image loading thing
	playerSprite.setOrigin(15, 15);
	playerSprite.setPosition(tileX, windowY / 2);

	// spider sprite setup
	Texture spiderTexture;
	spiderTexture.loadFromFile("Mutant_Spider.png");
	Sprite spiderSprite;
	spiderSprite.setTexture(spiderTexture);
	spiderSprite.setOrigin(15, 15);
	spiderSprite.setPosition(rand() % windowX, rand() % windowY);

	// dog sprite setup
	Texture dogTexture;
	dogTexture.loadFromFile("Mutant_Dog.png");
	Sprite dogSprite;
	dogSprite.setTexture(dogTexture);
	dogSprite.setTextureRect(IntRect(0, 0, 32, 32));
	dogSprite.setOrigin(15, 15);
	dogSprite.setPosition(rand() % windowX, rand() % windowY);

	// bats sprite setup
	Texture batsTexture;
	batsTexture.loadFromFile("Mutant_Bats.png");
	Sprite batsSprite;
	batsSprite.setTexture(batsTexture);
	batsSprite.setOrigin(15, 15);
	batsSprite.setPosition(rand() % windowX, rand() % windowY);

	// bear sprite setup
	Texture bearTexture;
	bearTexture.loadFromFile("Mutant_Bear_Monster.png");
	Sprite bearSprite;
	bearSprite.setTexture(bearTexture);
	bearSprite.setTextureRect(IntRect(0, 0, 32, 32));
	bearSprite.setOrigin(15, 15);
	bearSprite.setPosition(rand() % windowX, rand() % windowY);

	// human sprite setup
	Texture humanTexture;
	humanTexture.loadFromFile("Mutant_Human.png");
	Sprite humanSprite;
	humanSprite.setTexture(humanTexture);
	humanSprite.setOrigin(15, 15);
	humanSprite.setPosition(rand() % windowX, rand() % windowY);

	int counter = 0;
	while (window.isOpen()) {
		counter++;
		Event event;

		// window closing stuff
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}

			// if key is released check if it's a control key and if so reset that bool so that things can be pressed again
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
				playerSprite.move(0, -1 * tileY); // there are other ways to do this (like a get position, set position thing) but this is shorter
			}
			// moves player (tile size) units left if A key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::A)) { // else if because player should only move in one direction at a time
				isAPressed = true;
				playerSprite.move(-1 * tileX, 0);
			}
			// moves player (tile size) units down if S key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				isSPressed = true;
				playerSprite.move(0, tileY);
			}
			// moves player (tile size) units right if D key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				isDPressed = true;
				playerSprite.move(tileX, 0);
			}
		}

		if (counter % 5 == 0) {
			spiderDirection = rand() % 4;
		}
		if (counter % 5 == 1) {
			dogDirection = rand() % 4;
		}
		if (counter % 5 == 2) {
			batsDirection = rand() % 4;
		}
		if (counter % 5 == 3) {
			bearDirection = rand() % 4;
		}
		if (counter % 5 == 4) {
			humanDirection = rand() % 4;
		}

		// spider movement
		if ((spiderDirection == 0) && (spiderSprite.getPosition().x > marginX)) {
			spiderSprite.move(-1 * tileX, 0);
		}
		if ((spiderDirection == 1) && (spiderSprite.getPosition().x < (windowX / 5 - marginX))) {
			spiderSprite.move(tileX, 0);
		}
		if ((spiderDirection == 2) && (spiderSprite.getPosition().y > marginY)) {
			spiderSprite.move(0, -1 * tileY);
		}
		if ((spiderDirection == 3) && (spiderSprite.getPosition().y < (windowY - marginY))) {
			spiderSprite.move(0, tileY);
		}

		// dog movement
		if ((dogDirection == 0) && (dogSprite.getPosition().x > marginX)) {
			dogSprite.setTextureRect(IntRect(0, 0, 32, 32));
			dogSprite.move(-1 * tileX, 0);
		}
		if ((dogDirection == 1) && (dogSprite.getPosition().x < (windowX / 5 - marginX))) {
			dogSprite.setTextureRect(IntRect(0, 32, 32, 32));
			dogSprite.move(tileX, 0);
		}
		if ((dogDirection == 2) && (dogSprite.getPosition().y > marginY)) {
			dogSprite.move(0, -1 * tileY);
		}
		if ((dogDirection == 3) && (dogSprite.getPosition().y < (windowY - marginY))) {
			dogSprite.move(0, tileY);
		}

		// bats movement
		if ((batsDirection == 0) && (batsSprite.getPosition().x > marginX)) {
			batsSprite.move(-1 * tileX, 0);
		}
		if ((batsDirection == 1) && (batsSprite.getPosition().x < (windowX / 5 - marginX))) {
			batsSprite.move(tileX, 0);
		}
		if ((batsDirection == 2) && (batsSprite.getPosition().y > marginY)) {
			batsSprite.move(0, -1 * tileY);
		}
		if ((batsDirection == 3) && (batsSprite.getPosition().y < (windowY - marginY))) {
			batsSprite.move(0, tileY);
		}

		// bear movement
		if ((bearDirection == 0) && (bearSprite.getPosition().x > marginX)) {
			bearSprite.setTextureRect(IntRect(0, 32, 32, 32));
			bearSprite.move(-1 * tileX, 0);
		}
		if ((bearDirection == 1) && (bearSprite.getPosition().x < (windowX / 5 - marginX))) {
			bearSprite.setTextureRect(IntRect(0, 0, 32, 32));
			bearSprite.move(tileX, 0);
		}
		if ((bearDirection == 2) && (bearSprite.getPosition().y > marginY)) {
			bearSprite.move(0, -1 * tileY);
		}
		if ((bearDirection == 3) && (bearSprite.getPosition().y < (windowY - marginY))) {
			bearSprite.move(0, tileY);
		}

		// human movement
		if ((humanDirection == 0) && (humanSprite.getPosition().x > marginX)) {
			humanSprite.move(-1 * tileX, 0);
		}
		if ((humanDirection == 1) && (humanSprite.getPosition().x < (windowX / 5 - marginX))) {
			humanSprite.move(tileX, 0);
		}
		if ((humanDirection == 2) && (humanSprite.getPosition().y > marginY)) {
			humanSprite.move(0, -1 * tileY);
		}
		if ((humanDirection == 3) && (humanSprite.getPosition().y < (windowY - marginY))) {
			humanSprite.move(0, tileY);
		}

		window.draw(background);

		window.draw(playerSprite);

		if (room == 1) {
			window.draw(spiderSprite);
		}
		if (room == 2) {
			window.draw(dogSprite);
		}
		if (room == 3){
			window.draw(batsSprite);
		}
		if (room == 4) {
			window.draw(bearSprite);
		}
		if (room == 5) {
			window.draw(humanSprite);
		}

		window.display();
	}
}