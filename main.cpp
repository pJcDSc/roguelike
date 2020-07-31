
// this is just about everything we have at this point as far as I can tell
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Mutant.h"
#include "Spider.h"
#include "Dog.h"
#include "Bat.h"
#include "Bear.h"
#include "Human.h"
using namespace std;
using namespace sf;

int main() {
	srand(time(NULL)); // you have to run srand once to get better random numbers

	// window size
	const int windowX = 800;
	const int windowY = 800;
	int spiderNum = 4; // number of monsters in each room (i have deleted the const because we may want to modify it eventually)
	int batNum = 2;
	int dogNum = 2;
	int bearNum = 2;
	int humanNum = 2;
	int monsterNum = spiderNum + batNum + dogNum + bearNum + humanNum; //Might make a method for this if it gets too repetitive to do this every time
	int screen = 0; // which screen is showing
	bool isLeftButtonPressed = false; // avoiding spam clicks or things where multiple things get selected
	bool isRightButtonPressed = false; // I haven't really thought about it yet but this feels like something we'll need once we start working on those controls
	bool isUpArrowPressed = false; // it feels like you shouldn't be able to fight and dodge at the same time
	bool isDownArrowPressed = false;

	// window setup
	RenderWindow window(VideoMode(windowX, windowY), "Roguelike");
	window.setFramerateLimit(30);

	// setting up font
	Font font;
	font.loadFromFile("arial.ttf"); // you have to have this in the same folder as this program and saved under the same name as it is here for this to load

	// title
	Text title; // object name
	title.setFont(font); // the font it's in
	title.setString("Roguelike"); // what the text actually says (we never talked about the title but this seemed like an obvious choice)
	title.setCharacterSize(windowX / 13.33); // how big the letters are, it's dependent on window size
	title.setFillColor(Color(255, 255, 255)); // white letters to contrast with the black background
	title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2); // which part of the object actually goes to the coordinates, etc. (I'm setting origin at center because it's easier to do the math with than the default of top left corner)
	title.setPosition(windowX / 2, windowY / 4); // where it goes

	// menu button (I don't know what the menu would have yet)
	Text menu;
	menu.setFont(font);
	menu.setString("Menu");
	menu.setCharacterSize(windowX / 26.67);
	menu.setFillColor(Color(255, 255, 255));
	menu.setOrigin(menu.getLocalBounds().width / 2, menu.getLocalBounds().height / 2);
	menu.setPosition(windowX / 4, windowY / 1.33);

	// controls link
	Text controls;
	controls.setFont(font);
	controls.setString("Controls");
	controls.setCharacterSize(windowX / 26.67);
	controls.setFillColor(Color(255, 255, 255));
	controls.setOrigin(controls.getLocalBounds().width / 2, menu.getLocalBounds().height / 2);
	controls.setPosition(windowX / 1.33, windowY / 1.33);

	// start button
	Text start;
	start.setFont(font);
	start.setString("Start Game");
	start.setCharacterSize(windowX / 16);
	start.setFillColor(Color(255, 255, 255));
	start.setOrigin(start.getLocalBounds().width / 2, start.getLocalBounds().height / 2);
	start.setPosition(windowX / 2, windowY / 2);

	// controls list
	Text controlKeys;
	controlKeys.setFont(font);
	controlKeys.setString("Movement - WASD\nAttack - Up Arrow\nDodge - Down Arrow\nSelect - Left Click\nPick Up/Use Item - Right Click");
	controlKeys.setCharacterSize(windowX / 26.67);
	controlKeys.setFillColor(Color(255, 255, 255));
	controlKeys.setOrigin(controlKeys.getLocalBounds().width / 2, controlKeys.getLocalBounds().height / 2);
	controlKeys.setPosition(windowX / 2, (controls.getLocalBounds().height + windowY / 5));

	// back button
	Text back;
	back.setFont(font);
	back.setString("Back");
	back.setCharacterSize(windowX / 26.67);
	back.setFillColor(Color(255, 255, 255));
	back.setOrigin(back.getLocalBounds().width / 2, back.getLocalBounds().height / 2);
	back.setPosition(windowX / 2, windowY / 2);

	// backstory
	Text intro;
	intro.setFont(font);
	// don't mess with the spacing here unless you're messing with the words too, this gets it more or less aligned and centered
	intro.setString("A dangerous chemical has been released and has infected\n\
		people and animals in the area. You are a scientist\n\
		and must fight your way to your laboratory so that\n\
	 you can stop its spread, synthesize a cure to reverse\n\
			  its effects, and save the world. Good luck!");
	intro.setCharacterSize(windowX / 26.67);
	intro.setFillColor(Color(255, 255, 255));
	intro.setOrigin(intro.getLocalBounds().width / 2, intro.getLocalBounds().height / 2);
	intro.setPosition(windowX / 2, windowY / 4);

	// continue
	Text clickContinue;
	clickContinue.setFont(font);
	clickContinue.setString("Click here to continue");
	clickContinue.setCharacterSize(windowX / 26.67);
	clickContinue.setFillColor(Color(255, 255, 255));
	clickContinue.setOrigin(clickContinue.getLocalBounds().width / 2, clickContinue.getLocalBounds().height / 2);
	clickContinue.setPosition(windowX / 2, windowY / 1.33);

	// coordinates boxes for later when we need to figure out if something has been clicked
	FloatRect startBoundingBox = start.getGlobalBounds();
	FloatRect menuBoundingBox = menu.getGlobalBounds();
	FloatRect controlsBoundingBox = controls.getGlobalBounds();
	FloatRect backBoundingBox = back.getGlobalBounds();
	FloatRect continueBoundingBox = clickContinue.getGlobalBounds();
	Vector2f mouseCoordinates = Vector2f(0, 0); // will store mouse coordinates to determine clicking later on

	// these are used later to slow down movement (with the way I've set it up here, you can't hold down a key and move)
	bool isWPressed = false;
	bool isAPressed = false;
	bool isSPressed = false;
	bool isDPressed = false;

	// we need arrays for directions because each monster should have a seperate value (otherwise all the monsters move in the same direction)
	/*
	int spiderDirection[monsterNum];
	int dogDirection[monsterNum];
	int batsDirection[monsterNum];
	int bearDirection[monsterNum];
	int humanDirection[monsterNum];
	*/

	// Storing each monster
	vector<Mutant*> mutants; //Needs to store pointers to mutants, because mutants are declared inside a scope but used outside, meaning if they aren't in the heap they get deleted after exiting the scope.

	// this is just making the arrays not empty
	/*
	for (int i = 0; i < monsterNum; i++) {
		spiderDirection[i] = -1;
		dogDirection[i] = -1;
		batsDirection[i] = -1;
		bearDirection[i] = -1;
		humanDirection[i] = -1;
	}
	*/

	// number of units sprites move
	const int tileX = 3;
	const int tileY = 3;
	const int playerX = 3; //New adjuster values for player speed
	const int playerY = 3; 
	// how much space should always be between the center of a monster and the borders of the window
	int marginX = 15 + tileX;
	int marginY = 15 + tileY;

	int directionsx[4] = { -1, 1, 0, 0 }; //Stores the multiplier for x movement based on direction value
	int directionsy[4] = { 0, 0, -1, 1 }; //Same for y

	// this is a rectangle background thing, it's white for now so we can see the sprites (we can remove it once I get the actual backgrounds loaded)
	RectangleShape background; // name
	background.setSize(Vector2f(windowX, windowY)); // size (whole window)
	background.setPosition(0, 0); // no math here so top left corner origin works to set coordinates
	background.setFillColor(Color(255, 255, 255)); // it's white because a lot of the sprites are dark colors

	// player sprite setup
	// texture (image) setup
	Texture playerTexture; // name of texture
	playerTexture.loadFromFile("Human_Player_Character.png"); // loading sprite sheet
	// setting up sprite
	Sprite playerSprite; // name
	playerSprite.setTexture(playerTexture); // setting texture
	playerSprite.setOrigin(15, 15); // it is a lot easier to have the origin at the center of a sprite
	playerSprite.setPosition(tileX, windowY / 2); // begin at left and center

	// spider sprite setup
	Texture spiderTexture;
	spiderTexture.loadFromFile("Mutant_Spider.png");
	//vector<Sprite> spiderSprites; // stores all the sprites so that we can make a lot of them very easily (vectors are like arrays but they have more freedom with what variable types you can put in them and don't have a set size)
	for (int i = 0; i < spiderNum; i++) { // repeat as many times as the number of monsters we want
		Sprite* spiderSprite = new Sprite();
		spiderSprite -> setTexture(spiderTexture);
		spiderSprite -> setOrigin(15, 15);
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		spiderSprite -> setPosition(x, y); // set sprite coordinates
		cout << "Setup monster at " << x << ", " << y << endl;
		//spiderSprites.push_back(spiderSprite); // this sprite is now at the most recent index of the vector
		Mutant* spider = new Spider(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		spider -> setSprite(spiderSprite);
		mutants.push_back(spider);
	}

	// dog sprite setup
	Texture dogTexture;
	dogTexture.loadFromFile("Mutant_Dog.png");
	//vector<Sprite> dogSprites;
	for (int i = 0; i < dogNum; i++) {
		Sprite* dogSprite = new Sprite();
		dogSprite->setTexture(dogTexture);
		dogSprite->setTextureRect(IntRect(0, 0, 32, 32));
		dogSprite->setOrigin(15, 15);
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		dogSprite->setPosition(x, y); // set sprite coordinates
		cout << "Setup monster at " << x << ", " << y << endl;
		//dogSprites.push_back(dogSprite); // this sprite is now at the most recent index of the vector
		Mutant* dog = new Dog(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		dog->setSprite(dogSprite);
		mutants.push_back(dog);
	}

	// bats sprite setup
	Texture batsTexture;
	batsTexture.loadFromFile("Mutant_Bats.png");
	//vector<Sprite> batsSprites;
	for (int i = 0; i < batNum; i++) {
		Sprite* batsSprite = new Sprite();
		batsSprite->setTexture(batsTexture);
		batsSprite->setOrigin(15, 15);
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		batsSprite->setPosition(x, y); // set sprite coordinates
		cout << "Setup monster at " << x << ", " << y << endl;
		//batsSprites.push_back(batsSprite); // this sprite is now at the most recent index of the vector
		Mutant* bats = new Bat(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		bats->setSprite(batsSprite);
		mutants.push_back(bats);
	}

	// bear sprite setup
	Texture bearTexture;
	bearTexture.loadFromFile("Mutant_Bear_Monster.png");
	vector<Sprite> bearSprites;
	for (int i = 0; i < bearNum; i++) {
		Sprite* bearSprite = new Sprite();
		bearSprite -> setTexture(bearTexture);
		bearSprite -> setTextureRect(IntRect(0, 0, 32, 32));
		bearSprite -> setOrigin(15, 15);
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		bearSprite -> setPosition(x, y); // set sprite coordinates
		//spiderSprites.push_back(spiderSprite); // this sprite is now at the most recent index of the vector
		Mutant* bear = new Bear(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		bear->setSprite(bearSprite);
		mutants.push_back(bear);
	}

	// human sprite setup
	Texture humanTexture;
	humanTexture.loadFromFile("Mutant_Human.png");
	//vector<Sprite> humanSprites;
	for (int i = 0; i < humanNum; i++) {
		Sprite* humanSprite = new Sprite();
		humanSprite->setTexture(humanTexture);
		humanSprite->setOrigin(15, 15);
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		humanSprite->setPosition(x, y); // set sprite coordinates
		cout << "Setup monster at " << x << ", " << y << endl;
		//humanSprites.push_back(humanSprite); // this sprite is now at the most recent index of the vector
		Mutant* human = new Human(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		human->setSprite(humanSprite);
		mutants.push_back(human);
	}

	//int counter = -1; // for knowing when to generate another random direction for each monster
						// Note from peter: As far as I can tell the only reason this counter is implemented is to wait a while before reupdating the sprites directions, I've reimplemented this a bit differently.

	// drawing stuff
	while (window.isOpen()) {
		//counter++; // new cycle so add to the counter

		// checking for certain events
		Event event;
		while (window.pollEvent(event)) {
			// window closing stuff
			if (event.type == Event::Closed) {
				window.close();
			}
			// checking for mouse button releases, if it has been reset bool so things can be clicked on again
			if (event.type == Event::MouseButtonReleased) {
				if (event.mouseButton.button == Mouse::Left) {
					isLeftButtonPressed = false;
				}
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
				if (event.key.code == Keyboard::Up) {
					isUpArrowPressed = false;
				}
				if (event.key.code == Keyboard::Down) {
					isDownArrowPressed = false;
				}
			}
		}

		window.clear();

		// if mouse is pressed
		if ((Mouse::isButtonPressed(Mouse::Left)) && (isLeftButtonPressed == false)) { // if left mouse button is clicked (not held down)
			// get mouse coordinates
			mouseCoordinates = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
			isLeftButtonPressed = true; // so that it can't be held down

			// if mouse is touching start text and it's the right screen
			if ((startBoundingBox.contains(mouseCoordinates)) && (screen == 0)) {
				screen = 1; // change screen to start screen
			}
			if ((menuBoundingBox.contains(mouseCoordinates)) && (screen == 0)) {
				screen = 2;
			}
			if ((controlsBoundingBox.contains(mouseCoordinates)) && (screen == 0)) {
				screen = 3;
			}
			if ((backBoundingBox.contains(mouseCoordinates)) && ((screen == 2) || (screen == 3))) {
				screen = 0;
			}
			if ((continueBoundingBox.contains(mouseCoordinates)) && (screen == 1)) {
				screen = 4;
			}
		}
		
		//Note from peter: I had to change tileX and tileY to make up for monsters being faster after refactoring, so I'm going to make a separate value for player movement that can be individually adjusted
		// if no keys are currently being pressed because being able to hold a key down and move just seemed weird somehow (this can be changed to make that allowed, I don't really care)
		//if ((isWPressed == false) && (isAPressed == false) && (isSPressed == false) && (isDPressed == false)) {
			// moves player (tile size) units up if W key is pressed
			if (Keyboard::isKeyPressed(Keyboard::W)) {
				isWPressed = true;
				playerSprite.move(0, -1 * playerY); // there are other ways to do this (like a get position, set position thing) but this is shorter
			}
			// moves player (tile size) units left if A key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::A)) { // else if because player should only move in one direction at a time
				isAPressed = true;
				playerSprite.move(-1 * playerX, 0);
			}
			// moves player (tile size) units down if S key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::S)) {
				isSPressed = true;
				playerSprite.move(0, playerY);
			}
			// moves player (tile size) units right if D key is pressed
			else if (Keyboard::isKeyPressed(Keyboard::D)) {
				isDPressed = true;
				playerSprite.move(playerX, 0);
			}
		//}

		for (int i = 0; i < monsterNum; i++) {
			Mutant* m = mutants.at(i);
			if (rand() % 10 == 0) { // % chance to reupdate direction
				m -> setDirection(rand() % 4);
			}
			
			int mDir = m->getDirection();

			if (m -> getType().compare("Dog") == 0) { //Bear and dog need a bit of extra texture manipulation (directional sprites)
				m -> getSprite()->setTextureRect(mDir == 0 ? IntRect(0, 0, 32, 32) : IntRect(0, 32, 32, 32)); //Short ternary statement basically choosing which half of the sprite to use (untested, both bear and dog aren't used yet)
			}
			if (m->getType().compare("Bear") == 0) {
				m->getSprite()->setTextureRect(mDir == 1 ? IntRect(0, 0, 32, 32) : IntRect(0, 32, 32, 32)); //Short ternary statement basically choosing which half of the sprite to use (untested, both bear and dog aren't used yet
			}

			if (directionsx[mDir] < 0 && m->getX() > marginX || directionsx[mDir] > 0 && m->getX() < (windowX - marginX) || 
				directionsy[mDir] < 0 && m->getY() > marginY || directionsy[mDir] > 0 && m->getY() < (windowY - marginY))
				m->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
			else //Give it a new direction to move in 
				m->setDirection(rand() % 4);
			//if (i == 0) cout << "Monster number " << i << " is at " << newX << ", " << newY << endl;

			/*
			// spider movement
			if ((spiderDirection[i] == 0) && (spiderSprites[i].getPosition().x > marginX)) { // if the direction is a certain value and the spider is within the boundaries
				spiderSprites[i].move(-1 * tileX, 0); // move the spider in the proper direction
			}
			if ((spiderDirection[i] == 1) && (spiderSprites[i].getPosition().x < (windowX - marginX))) {
				spiderSprites[i].move(tileX, 0);
			}
			if ((spiderDirection[i] == 2) && (spiderSprites[i].getPosition().y > marginY)) {
				spiderSprites[i].move(0, -1 * tileY);
			}
			if ((spiderDirection[i] == 3) && (spiderSprites[i].getPosition().y < (windowY - marginY))) {
				spiderSprites[i].move(0, tileY);
			}

			// dog movement
			if ((dogDirection[i] == 0) && (dogSprites[i].getPosition().x > marginX)) {
				dogSprites[i].setTextureRect(IntRect(0, 0, 32, 32));
				dogSprites[i].move(-1 * tileX, 0);
			}
			if ((dogDirection[i] == 1) && (dogSprites[i].getPosition().x < (windowX / 5 - marginX))) {
				dogSprites[i].setTextureRect(IntRect(0, 32, 32, 32));
				dogSprites[i].move(tileX, 0);
			}
			if ((dogDirection[i] == 2) && (dogSprites[i].getPosition().y > marginY)) {
				dogSprites[i].move(0, -1 * tileY);
			}
			if ((dogDirection[i] == 3) && (dogSprites[i].getPosition().y < (windowY - marginY))) {
				dogSprites[i].move(0, tileY);
			}

			// bats movement
			if ((batsDirection[i] == 0) && (batsSprites[i].getPosition().x > marginX)) {
				batsSprites[i].move(-1 * tileX, 0);
			}
			if ((batsDirection[i] == 1) && (batsSprites[i].getPosition().x < (windowX / 5 - marginX))) {
				batsSprites[i].move(tileX, 0);
			}
			if ((batsDirection[i] == 2) && (batsSprites[i].getPosition().y > marginY)) {
				batsSprites[i].move(0, -1 * tileY);
			}
			if ((batsDirection[i] == 3) && (batsSprites[i].getPosition().y < (windowY - marginY))) {
				batsSprites[i].move(0, tileY);
			}

			// bear movement
			if ((bearDirection[i] == 0) && (bearSprites[i].getPosition().x > marginX)) {
				bearSprites[i].setTextureRect(IntRect(0, 32, 32, 32));
				bearSprites[i].move(-1 * tileX, 0);
			}
			if ((bearDirection[i] == 1) && (bearSprites[i].getPosition().x < (windowX / 5 - marginX))) {
				bearSprites[i].setTextureRect(IntRect(0, 0, 32, 32));
				bearSprites[i].move(tileX, 0);
			}
			if ((bearDirection[i] == 2) && (bearSprites[i].getPosition().y > marginY)) {
				bearSprites[i].move(0, -1 * tileY);
			}
			if ((bearDirection[i] == 3) && (bearSprites[i].getPosition().y < (windowY - marginY))) {
				bearSprites[i].move(0, tileY);
			}

			// human movement
			if ((humanDirection[i] == 0) && (humanSprites[i].getPosition().x > marginX)) {
				humanSprites[i].move(-1 * tileX, 0);
			}
			if ((humanDirection[i] == 1) && (humanSprites[i].getPosition().x < (windowX / 5 - marginX))) {
				humanSprites[i].move(tileX, 0);
			}
			if ((humanDirection[i] == 2) && (humanSprites[i].getPosition().y > marginY)) {
				humanSprites[i].move(0, -1 * tileY);
			}
			if ((humanDirection[i] == 3) && (humanSprites[i].getPosition().y < (windowY - marginY))) {
				humanSprites[i].move(0, tileY);
			}
			*/
		}

		if (screen == 0) { // checking which screen should be showing, this one is the first screen that pops up
			// draw what's supposed to be on that screen
			menu.setPosition(windowX / 4, windowY / 1.33); // menu text moves around on certain screens so it has to be reset each time
			controls.setPosition(windowX / 1.33, windowY / 1.33);
			window.draw(title);
			window.draw(menu);
			window.draw(controls);
			window.draw(start);
		}
		if (screen == 1) { // this is the backstory page
			window.draw(intro);
			window.draw(clickContinue);
		}
		if (screen == 2) { // menu page, can someone please tell me what's supposed to be here because I have no idea
			menu.setPosition(windowX / 2, menu.getLocalBounds().height);
			window.draw(menu);
			window.draw(back);
		}
		if (screen == 3) { // controls list
			controls.setPosition(windowX / 2, controls.getLocalBounds().height);
			window.draw(controls);
			window.draw(controlKeys);
			window.draw(back);
		}
		if (screen >= 4) { // at this point it's all monster rooms from here for now
			window.draw(background);
			window.draw(playerSprite);
			// this monster shows up in this room
			for (int i = 0; i < monsterNum; i++) {
				window.draw(*(mutants.at(i)->getSprite()));
				//cout << mutants.at(i)->getSprite() << endl;
			}
		}


		window.display();
	}
}
