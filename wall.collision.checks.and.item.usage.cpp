// adding backgrounds, walls, and items
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
// class headers
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

	// window size, the proportions are so the background doesn't get stretched weird
	const int windowX = 1280;
	const int windowY = 640;
	int spiderNum = 4; // number of spiders (i have deleted the const because we may want to modify it eventually)
	int batNum = 2; // number of bats
	int dogNum = 2; // number of dogs
	int bearNum = 2; // number of bears
	int humanNum = 2;
	int monsterNum = spiderNum + batNum + dogNum + bearNum + humanNum;
	int screen = 0; // which screen is showing
	bool isLeftButtonPressed = false; // avoiding spam clicks or things where multiple things get selected
	bool isRightButtonPressed = false; // I haven't really thought about it yet but this feels like something we'll need once we start working on those controls
	bool isUpArrowPressed = false; // it feels like you shouldn't be able to fight and dodge at the same time
	bool isDownArrowPressed = false;

	// window setup
	RenderWindow window(VideoMode(windowX, windowY), "Roguelike");
	window.setFramerateLimit(30);

	// border lines for border checks
	RectangleShape leftLine;
	leftLine.setSize(Vector2f(1, windowY));
	leftLine.setPosition(0, 0);

	RectangleShape topLine;
	topLine.setSize(Vector2f(windowX, 1));
	topLine.setPosition(0, 0);

	RectangleShape rightLine;
	rightLine.setSize(Vector2f(1, windowY));
	rightLine.setPosition(windowX, 0);

	RectangleShape bottomLine;
	bottomLine.setSize(Vector2f(windowX, 1));
	bottomLine.setPosition(0, windowY);

	// bounding boxes for border checks
	FloatRect leftLineBoundingBox = leftLine.getGlobalBounds();
	FloatRect topLineBoundingBox = topLine.getGlobalBounds();
	FloatRect rightLineBoundingBox = rightLine.getGlobalBounds();
	FloatRect bottomLineBoundingBox = bottomLine.getGlobalBounds();

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
	controlKeys.setPosition(windowX / 2, windowY / 3);

	// back button
	Text back;
	back.setFont(font);
	back.setString("Back");
	back.setCharacterSize(windowX / 26.67);
	back.setFillColor(Color(255, 255, 255));
	back.setOrigin(back.getLocalBounds().width / 2, back.getLocalBounds().height / 2);
	back.setPosition(windowX / 2, windowY / 1.33);

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

	// Storing each monster
	vector<Mutant*> mutants; //Needs to store pointers to mutants, because mutants are declared inside a scope but used outside, meaning if they aren't in the heap they get deleted after exiting the scope.

	// number of units sprites move
	const int tileX = 3;
	const int tileY = 3;
	const int playerX = 3; //New adjuster values for player speed
	const int playerY = 3;

	int directionsx[4] = { -1, 1, 0, 0 }; //Stores the multiplier for x movement based on direction value
	int directionsy[4] = { 0, 0, -1, 1 }; //Same for y

	// backgrounds
	// cave
	Texture caveTexture;
	caveTexture.loadFromFile("Cave_Area_1.png");
	Sprite caveSprite;
	caveSprite.setTexture(caveTexture);
	caveSprite.scale(Vector2f(10.f, 10.f)); // I don't know how to call variables in this command so we're just going to have to change this anytime the window size changes unless somebody else knows a better way

	// junkyard
	Texture junkyardTexture;
	junkyardTexture.loadFromFile("Junkyard_Area_2.png");
	Sprite junkyardSprite;
	junkyardSprite.setTexture(junkyardTexture);
	junkyardSprite.scale(Vector2f(10.f, 10.f));

	// catacombs
	Texture catacombsTexture;
	catacombsTexture.loadFromFile("Catacombs_Area_3.png");
	Sprite catacombsSprite;
	catacombsSprite.setTexture(catacombsTexture);
	catacombsSprite.scale(Vector2f(10.f, 10.f));

	// forest
	Texture forestTexture;
	forestTexture.loadFromFile("Forest_Area_4.png");
	Sprite forestSprite;
	forestSprite.setTexture(forestTexture);
	forestSprite.scale(Vector2f(10.f, 10.f));

	// lab
	Texture labTexture;
	labTexture.loadFromFile("Lab_Area_5.png");
	Sprite labSprite;
	labSprite.setTexture(labTexture);
	labSprite.scale(Vector2f(10.f, 10.f));

	// walls
	// cave
	Texture caveWallTexture;
	caveWallTexture.loadFromFile("Cave_Wall.png");
	Sprite caveWallSprite;
	caveWallSprite.setTexture(caveWallTexture);
	caveWallSprite.scale(Vector2f(10.f, 10.f));
	caveWallSprite.setPosition(windowX - caveWallSprite.getGlobalBounds().width, 0);

	// junkyard
	Texture junkyardWallTexture;
	junkyardWallTexture.loadFromFile("Junkyard_Wall.png");
	Sprite junkyardWallSprite;
	junkyardWallSprite.setTexture(junkyardWallTexture);
	junkyardWallSprite.scale(Vector2f(10.f, 10.f));
	junkyardWallSprite.setPosition(windowX - junkyardWallSprite.getGlobalBounds().width, 0);

	// catacombs
	Texture catacombsWallTexture;
	catacombsWallTexture.loadFromFile("Catacombs_Wall.png");
	Sprite catacombsWallSprite;
	catacombsWallSprite.setTexture(catacombsWallTexture);
	catacombsWallSprite.scale(Vector2f(10.f, 10.f));
	catacombsWallSprite.setPosition(windowX - catacombsWallSprite.getGlobalBounds().width, 0);

	// forest
	Texture forestWallTexture;
	forestWallTexture.loadFromFile("Forest_Wall.png");
	Sprite forestWallSprite;
	forestWallSprite.setTexture(forestWallTexture);
	forestWallSprite.scale(Vector2f(10.f, 10.f));
	forestWallSprite.setPosition(windowX - forestWallSprite.getGlobalBounds().width, 0);

	// lab
	Texture labWallTexture;
	labWallTexture.loadFromFile("Lab_Wall_End_Game.png");
	Sprite labWallSprite;
	labWallSprite.setTexture(labWallTexture);
	labWallSprite.scale(Vector2f(10.f, 10.f));
	labWallSprite.setPosition(windowX - labWallSprite.getGlobalBounds().width, 0);

	// wall bounding boxes
	FloatRect caveWallBoundingBox = caveWallSprite.getGlobalBounds();
	FloatRect junkyardWallBoundingBox = junkyardWallSprite.getGlobalBounds();
	FloatRect catacombsWallBoundingBox = catacombsWallSprite.getGlobalBounds();
	FloatRect forestWallBoundingBox = forestWallSprite.getGlobalBounds();
	FloatRect labWallBoundingBox = labWallSprite.getGlobalBounds();

	// player dealing with wall checks
	bool isCaveWallDown = false;
	bool isJunkyardWallDown = false;
	bool isCatacombsWallDown = false;
	bool isForestWallDown = false;
	bool isLabWallDown = false;

	// player sprite setup
	// texture (image) setup
	Texture playerTexture; // name of texture
	playerTexture.loadFromFile("Human_Player_Character.png"); // loading sprite sheet
	// setting up sprite
	Sprite playerSprite; // name
	playerSprite.setTexture(playerTexture); // setting texture
	playerSprite.setOrigin(15, 15); // it is a lot easier to have the origin at the center of a sprite
	playerSprite.setPosition(0, windowY / 2); // begin at left and center
	playerSprite.scale(Vector2f(4.f, 4.f));

	// spider sprite setup
	Texture spiderTexture;
	spiderTexture.loadFromFile("Mutant_Spider.png");
	//vector<Sprite> spiderSprites; // stores all the sprites so that we can make a lot of them very easily (vectors are like arrays but they have more freedom with what variable types you can put in them and don't have a set size)
	for (int i = 0; i < spiderNum; i++) { // repeat as many times as the number of monsters we want
		Sprite* spiderSprite = new Sprite();
		spiderSprite->setTexture(spiderTexture);
		spiderSprite->setOrigin(15, 15);
		spiderSprite->scale(Vector2f(3.f, 3.f));
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		spiderSprite->setPosition(x, y); // set sprite coordinates
		Mutant* spider = new Spider(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		spider->setSprite(spiderSprite);
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
		dogSprite->scale(Vector2f(3.f, 3.f));
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		dogSprite->setPosition(x, y); // set sprite coordinates
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
		batsSprite->scale(Vector2f(3.f, 3.f));
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		batsSprite->setPosition(x, y); // set sprite coordinates
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
		bearSprite->setTexture(bearTexture);
		bearSprite->setTextureRect(IntRect(0, 0, 32, 32));
		bearSprite->setOrigin(15, 15);
		bearSprite->scale(Vector2f(3.f, 3.f));
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		bearSprite->setPosition(x, y); // set sprite coordinates
		Mutant* bear = new Bear(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		bear->setSprite(bearSprite);
		mutants.push_back(bear);
	}

	// human sprite setup
	Texture humanTexture;
	humanTexture.loadFromFile("Mutant_Human.png");
	for (int i = 0; i < humanNum; i++) {
		Sprite* humanSprite = new Sprite();
		humanSprite->setTexture(humanTexture);
		humanSprite->setOrigin(15, 15);
		humanSprite->scale(Vector2f(3.f, 3.f));
		int x = (rand() % (windowX / tileX) * tileX); // get random coordinates
		int y = (rand() % (windowY / tileY) * tileY);
		humanSprite->setPosition(x, y); // set sprite coordinates
		Mutant* human = new Human(10, 10, x, y); //Hp, Attack damage, x, y (coords)
		human->setSprite(humanSprite);
		mutants.push_back(human);
	}

	// bounding boxes for player and monsters, no idea if we're doing something else for collision code but I need the player one for item checks and figured I might as well at least set up the others
	FloatRect playerBoundingBox = playerSprite.getGlobalBounds();
	while (playerBoundingBox.intersects(leftLineBoundingBox)) {
		playerSprite.move(playerX, 0);
		playerBoundingBox = playerSprite.getGlobalBounds();
	}

	vector<FloatRect> mutantBoundingBoxes;
	for (int i = 0; i < monsterNum; i++) {
		mutantBoundingBoxes.push_back(mutants.at(i)->getSprite()->getGlobalBounds());
	}

	// items
	// pickaxe
	Texture pickaxeTexture;
	pickaxeTexture.loadFromFile("Pickaxe_Item.png");
	Sprite pickaxeSprite;
	pickaxeSprite.setTexture(pickaxeTexture);
	pickaxeSprite.setOrigin(14, 14);
	pickaxeSprite.scale(Vector2f(3.f, 3.f));
	pickaxeSprite.setPosition(rand() % (windowX / playerX) * playerX, rand() % (windowY / playerY) * playerY);

	// trash can
	Texture trashCanTexture;
	trashCanTexture.loadFromFile("Trash_Can_Item.png");
	Sprite trashCanSprite;
	trashCanSprite.setTexture(trashCanTexture);
	trashCanSprite.setOrigin(14, 14);
	trashCanSprite.scale(Vector2f(3.f, 3.f));
	trashCanSprite.setPosition(rand() % (windowX / playerX) * playerX, rand() % (windowY / playerY) * playerY);

	// sword
	Texture swordTexture;
	swordTexture.loadFromFile("Sword_Item.png");
	Sprite swordSprite;
	swordSprite.setTexture(swordTexture);
	swordSprite.setOrigin(14, 14);
	swordSprite.scale(Vector2f(3.f, 3.f));
	swordSprite.setPosition(rand() % (windowX / playerX) * playerX, rand() % (windowY / playerY) * playerY);

	// axe
	Texture axeTexture;
	axeTexture.loadFromFile("Axe_Item.png");
	Sprite axeSprite;
	axeSprite.setTexture(axeTexture);
	axeSprite.setOrigin(14, 14);
	axeSprite.scale(Vector2f(3.f, 3.f));
	axeSprite.setPosition(rand() % (windowX / playerX) * playerX, rand() % (windowY / playerY) * playerY);

	// key
	Texture keyTexture;
	keyTexture.loadFromFile("Key_Item.png");
	Sprite keySprite;
	keySprite.setTexture(keyTexture);
	keySprite.setOrigin(14, 14);
	keySprite.scale(Vector2f(3.f, 3.f));
	keySprite.setPosition(rand() % (windowX / playerX) * playerX, rand() % (windowY / playerY) * playerY);

	// bounding boxes for items so we can tell when they've been clicked on
	FloatRect pickaxeBoundingBox = pickaxeSprite.getGlobalBounds();
	while (pickaxeBoundingBox.intersects(leftLineBoundingBox)) {
		pickaxeSprite.move(playerX, 0);
		pickaxeBoundingBox = pickaxeSprite.getGlobalBounds();
	}
	while (pickaxeBoundingBox.intersects(topLineBoundingBox)) {
		pickaxeSprite.move(0, playerY);
		pickaxeBoundingBox = pickaxeSprite.getGlobalBounds();
	}
	while (pickaxeBoundingBox.intersects(caveWallBoundingBox)) {
		pickaxeSprite.move(-1 * playerX, 0);
		pickaxeBoundingBox = pickaxeSprite.getGlobalBounds();
	}
	while (pickaxeBoundingBox.intersects(bottomLineBoundingBox)) {
		pickaxeSprite.move(0, -1 * playerY);
		pickaxeBoundingBox = pickaxeSprite.getGlobalBounds();
	}

	FloatRect trashCanBoundingBox = trashCanSprite.getGlobalBounds();
	while (trashCanBoundingBox.intersects(leftLineBoundingBox)) {
		trashCanSprite.move(playerX, 0);
		trashCanBoundingBox = trashCanSprite.getGlobalBounds();
	}
	while (trashCanBoundingBox.intersects(topLineBoundingBox)) {
		trashCanSprite.move(0, playerY);
		trashCanBoundingBox = trashCanSprite.getGlobalBounds();
	}
	while (trashCanBoundingBox.intersects(junkyardWallBoundingBox)) {
		trashCanSprite.move(-1 * playerX, 0);
		trashCanBoundingBox = trashCanSprite.getGlobalBounds();
	}
	while (trashCanBoundingBox.intersects(bottomLineBoundingBox)) {
		trashCanSprite.move(0, -1 * playerY);
		trashCanBoundingBox = trashCanSprite.getGlobalBounds();
	}

	FloatRect swordBoundingBox = swordSprite.getGlobalBounds();
	while (swordBoundingBox.intersects(leftLineBoundingBox)) {
		swordSprite.move(playerX, 0);
		swordBoundingBox = swordSprite.getGlobalBounds();
	}
	while (swordBoundingBox.intersects(topLineBoundingBox)) {
		swordSprite.move(0, playerY);
		swordBoundingBox = swordSprite.getGlobalBounds();
	}
	while (swordBoundingBox.intersects(catacombsWallBoundingBox)) {
		swordSprite.move(-1 * playerX, 0);
		swordBoundingBox = swordSprite.getGlobalBounds();
	}
	while (swordBoundingBox.intersects(bottomLineBoundingBox)) {
		swordSprite.move(0, -1 * playerY);
		swordBoundingBox = swordSprite.getGlobalBounds();
	}

	FloatRect axeBoundingBox = axeSprite.getGlobalBounds();
	while (axeBoundingBox.intersects(leftLineBoundingBox)) {
		axeSprite.move(playerX, 0);
		axeBoundingBox = axeSprite.getGlobalBounds();
	}
	while (axeBoundingBox.intersects(topLineBoundingBox)) {
		axeSprite.move(0, playerY);
		axeBoundingBox = axeSprite.getGlobalBounds();
	}
	while (axeBoundingBox.intersects(forestWallBoundingBox)) {
		axeSprite.move(-1 * playerX, 0);
		axeBoundingBox = axeSprite.getGlobalBounds();
	}
	while (axeBoundingBox.intersects(bottomLineBoundingBox)) {
		axeSprite.move(0, -1 * playerY);
		axeBoundingBox = axeSprite.getGlobalBounds();
	}

	FloatRect keyBoundingBox = keySprite.getGlobalBounds();
	while (keyBoundingBox.intersects(leftLineBoundingBox)) {
		keySprite.move(playerX, 0);
		keyBoundingBox = keySprite.getGlobalBounds();
	}
	while (keyBoundingBox.intersects(topLineBoundingBox)) {
		keySprite.move(0, playerY);
		keyBoundingBox = keySprite.getGlobalBounds();
	}
	while (keyBoundingBox.intersects(labWallBoundingBox)) {
		keySprite.move(-1 * playerX, 0);
		keyBoundingBox = keySprite.getGlobalBounds();
	}
	while (keyBoundingBox.intersects(bottomLineBoundingBox)) {
		keySprite.move(0, -1 * playerY);
		keyBoundingBox = keySprite.getGlobalBounds();
	}

	// inventory checks
	bool isPickaxeInInventory = false;
	bool isTrashCanInInventory = false;
	bool isSwordInInventory = false;
	bool isAxeInInventory = false;
	bool isKeyInInventory = false;

	// drawing stuff
	while (window.isOpen()) {
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
				if (event.mouseButton.button == Mouse::Right) {
					isRightButtonPressed = false;
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

		mouseCoordinates = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		playerBoundingBox = playerSprite.getGlobalBounds();
		for (int i = 0; i < monsterNum; i++) {
			mutantBoundingBoxes[i] = mutants.at(i)->getSprite()->getGlobalBounds();
		}
		// if mouse is pressed
		if (Mouse::isButtonPressed(Mouse::Left) && isLeftButtonPressed == false) { // if left mouse button is clicked (not held down)
			// get mouse coordinates
			isLeftButtonPressed = true; // so that it can't be held down

			// if mouse is touching start text and it's the right screen
			if (startBoundingBox.contains(mouseCoordinates) && screen == 0) {
				screen = 1; // change screen to start screen
			}
			if (menuBoundingBox.contains(mouseCoordinates) && screen == 0) {
				screen = 2;
			}
			if (controlsBoundingBox.contains(mouseCoordinates) && screen == 0) {
				screen = 3;
			}
			if (backBoundingBox.contains(mouseCoordinates) && (screen == 2 || screen == 3)) {
				screen = 0;
			}
			if (continueBoundingBox.contains(mouseCoordinates) && screen == 1) {
				screen = 4;
			}
		}
		else if (Mouse::isButtonPressed(Mouse::Right) && isRightButtonPressed == false) {
			isRightButtonPressed = true;
			// right now this doesn't take into account where the player is, I don't know how to do that kind of collision code
			if (screen == 4) {
				if (pickaxeBoundingBox.contains(mouseCoordinates) && pickaxeBoundingBox.intersects(playerBoundingBox)) {
					isPickaxeInInventory = true;
				}
				if (caveWallBoundingBox.contains(mouseCoordinates) && caveWallBoundingBox.intersects(playerBoundingBox) && isPickaxeInInventory == true) {
					isCaveWallDown = true;
				}
			}
			if (screen == 5) {
				if (trashCanBoundingBox.contains(mouseCoordinates) && trashCanBoundingBox.intersects(playerBoundingBox)) {
					isTrashCanInInventory = true;
				}
				if (junkyardWallBoundingBox.contains(mouseCoordinates) && junkyardWallBoundingBox.intersects(playerBoundingBox) && isTrashCanInInventory == true) {
					isJunkyardWallDown = true;
				}
			}
			if (screen == 6) {
				if (swordBoundingBox.contains(mouseCoordinates) && swordBoundingBox.intersects(playerBoundingBox)) {
					isSwordInInventory = true;
				}
				if (catacombsWallBoundingBox.contains(mouseCoordinates) && catacombsWallBoundingBox.intersects(playerBoundingBox) && isSwordInInventory == true) {
					isCatacombsWallDown = true;
				}
			}
			if (screen == 7) {
				if (axeBoundingBox.contains(mouseCoordinates) && axeBoundingBox.intersects(playerBoundingBox)) {
					isAxeInInventory = true;
				}
				if (forestWallBoundingBox.contains(mouseCoordinates) && forestWallBoundingBox.intersects(playerBoundingBox) && isAxeInInventory == true) {
					isForestWallDown = true;
				}
			}
			if (screen == 8) {
				if (keyBoundingBox.contains(mouseCoordinates) && keyBoundingBox.intersects(playerBoundingBox)) {
					isKeyInInventory = true;
				}
				if (labWallBoundingBox.contains(mouseCoordinates) && labWallBoundingBox.intersects(playerBoundingBox) && isKeyInInventory == true) {
					isLabWallDown = true;
				}
			}
		}

		//Note from peter: I had to change tileX and tileY to make up for monsters being faster after refactoring, so I'm going to make a separate value for player movement that can be individually adjusted
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			isWPressed = true;

			if (!playerBoundingBox.intersects(topLineBoundingBox)) {
				playerSprite.move(0, -1 * playerY); // there are other ways to do this (like a get position, set position thing) but this is shorter
			}
		}
		// moves player (tile size) units left if A key is pressed
		else if (Keyboard::isKeyPressed(Keyboard::A)) { // else if because player should only move in one direction at a time
			isAPressed = true;

			if (!playerBoundingBox.intersects(leftLineBoundingBox)) {
				playerSprite.move(-1 * playerX, 0);
			}
		}
		// moves player (tile size) units down if S key is pressed
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			isSPressed = true;

			if (!playerBoundingBox.intersects(bottomLineBoundingBox)) {
				playerSprite.move(0, playerY);
			}
		}
		// moves player (tile size) units right if D key is pressed
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			isDPressed = true;

			if (!playerBoundingBox.intersects(rightLineBoundingBox)) {
				if (screen == 4) {
					if (!playerBoundingBox.intersects(caveWallBoundingBox) && isCaveWallDown == false) {
						playerSprite.move(playerX, 0);
					}
					if (isCaveWallDown == true) {
						playerSprite.move(playerX, 0);
					}
				}
				if (screen == 5) {
					if (!playerBoundingBox.intersects(junkyardWallBoundingBox) && isJunkyardWallDown == false) {
						playerSprite.move(playerX, 0);
					}
					if (isJunkyardWallDown == true) {
						playerSprite.move(playerX, 0);
					}
				}
				if (screen == 6) {
					if (!playerBoundingBox.intersects(catacombsWallBoundingBox) && isCatacombsWallDown == false) {
						playerSprite.move(playerX, 0);
					}
					if (isCatacombsWallDown == true) {
						playerSprite.move(playerX, 0);
					}
				}
				if (screen == 7) {
					if (!playerBoundingBox.intersects(forestWallBoundingBox) && isForestWallDown == false) {
						playerSprite.move(playerX, 0);
					}
					if (isForestWallDown == true) {
						playerSprite.move(playerX, 0);
					}
				}
				if (screen == 8) {
					if (!playerBoundingBox.intersects(labWallBoundingBox) && isLabWallDown == false) {
						playerSprite.move(playerX, 0);
					}
					if (isLabWallDown == true) {
						playerSprite.move(playerX, 0);
					}
				}
			}
			else {
				screen++;
				playerSprite.setPosition(0, windowY / 2);
				playerBoundingBox = playerSprite.getGlobalBounds();
				while (playerBoundingBox.intersects(leftLineBoundingBox)) {
					playerSprite.move(playerX, 0);
					playerBoundingBox = playerSprite.getGlobalBounds();
				}
			}
		}

		for (int i = 0; i < monsterNum; i++) {
			Mutant* m = mutants.at(i);
			if (rand() % 10 == 0) { // % chance to reupdate direction
				m->setDirection(rand() % 4);
			}

			int mDir = m->getDirection();

			if (m->getType().compare("Dog") == 0) { //Bear and dog need a bit of extra texture manipulation (directional sprites)
				m->getSprite()->setTextureRect(mDir == 0 ? IntRect(0, 0, 32, 32) : IntRect(0, 32, 32, 32)); //Short ternary statement basically choosing which half of the sprite to use (untested, both bear and dog aren't used yet)
			}
			if (m->getType().compare("Bear") == 0) {
				m->getSprite()->setTextureRect(mDir == 1 ? IntRect(0, 0, 32, 32) : IntRect(0, 32, 32, 32)); //Short ternary statement basically choosing which half of the sprite to use (untested, both bear and dog aren't used yet)
			}

			mutantBoundingBoxes[i] = m->getSprite()->getGlobalBounds();
			/*if ((directionsx[mDir] < 0 && !mutantBoundingBoxes[i].intersects(leftLineBoundingBox)) ||
				(directionsx > 0 && !mutantBoundingBoxes[i].intersects(junkyardWallBoundingBox)) ||
				(directionsy[mDir] < 0 && !mutantBoundingBoxes[i].intersects(topLineBoundingBox)) ||
				(directionsy[mDir] > 0 && !mutantBoundingBoxes[i].intersects(bottomLineBoundingBox))) {
				m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
			}*/

			if (screen == 4) {
				if (directionsx[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(leftLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsx[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(caveWallBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(topLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(bottomLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
			}
			if (screen == 5) {
				i -= spiderNum;
				if (directionsx[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(leftLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsx[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(junkyardWallBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(topLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(bottomLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				i += spiderNum;
			}
			if (screen == 6) {
				i -= spiderNum + dogNum;
				if (directionsx[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(leftLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsx[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(catacombsWallBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(topLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(bottomLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				i += spiderNum + dogNum;
			}
			if (screen == 7) {
				i -= spiderNum + dogNum + batNum;
				if (directionsx[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(leftLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsx[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(forestWallBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(topLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(bottomLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				i += spiderNum + dogNum + batNum;
			}
			if (screen == 8) {
				i -= spiderNum + dogNum + batNum + bearNum;
				if (directionsx[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(leftLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsx[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(labWallBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] < 0) {
					if (!mutantBoundingBoxes[i].intersects(topLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				if (directionsy[mDir] > 0) {
					if (!mutantBoundingBoxes[i].intersects(bottomLineBoundingBox)) {
						m->getSprite()->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
					}
				}
				i += spiderNum + dogNum + batNum + bearNum;
			}
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
		if (screen == 4) {
			window.draw(caveSprite);
			if (isCaveWallDown == false) {
				window.draw(caveWallSprite);
			}
			if (isPickaxeInInventory == false) {
				window.draw(pickaxeSprite);
			}
			window.draw(playerSprite);
			for (int i = 0; i < spiderNum; i++) {
				window.draw(*(mutants.at(i)->getSprite()));
			}
		}
		if (screen == 5) {
			window.draw(junkyardSprite);
			if (isJunkyardWallDown == false) {
				window.draw(junkyardWallSprite);
			}
			if (isTrashCanInInventory == false) {
				window.draw(trashCanSprite);
			}
			window.draw(playerSprite);
			for (int i = 0; i < dogNum; i++) {
				i += spiderNum; // spiders have already been drawn
				window.draw(*(mutants.at(i)->getSprite()));
				i -= spiderNum; // this is so that the modified i for the right index doesn't break the loop
			}
		}
		if (screen == 6) {
			window.draw(catacombsSprite);
			if (isCatacombsWallDown == false) {
				window.draw(catacombsWallSprite);
			}
			if (isSwordInInventory == false) {
				window.draw(swordSprite);
			}
			window.draw(playerSprite);
			for (int i = 0; i < batNum; i++) {
				i += spiderNum + dogNum;
				window.draw(*(mutants.at(i)->getSprite()));
				i -= spiderNum + dogNum;
			}
		}
		if (screen == 7) {
			window.draw(forestSprite);
			if (isForestWallDown == false) {
				window.draw(forestWallSprite);
			}
			if (isAxeInInventory == false) {
				window.draw(axeSprite);
			}
			window.draw(playerSprite);
			for (int i = 0; i < bearNum; i++) {
				i += spiderNum + dogNum + batNum;
				window.draw(*(mutants.at(i)->getSprite()));
				i -= spiderNum + dogNum + batNum;
			}
		}
		if (screen == 8) {
			window.draw(labSprite);
			if (isLabWallDown == false) {
				window.draw(labWallSprite);
			}
			if (isKeyInInventory == false) {
				window.draw(keySprite);
			}
			window.draw(playerSprite);
			for (int i = 0; i < humanNum; i++) {
				i += spiderNum + dogNum + batNum + bearNum;
				window.draw(*(mutants.at(i)->getSprite()));
			}
		}
		if (screen == 9) {

		}

		window.display();
	}
}