// this combines the fighting mechanics with the graphics and other already put together code
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

// class headers
#include "Mutant.h"
#include "Spider.h"
#include "Dog.h"
#include "Bat.h"
#include "Bear.h"
#include "Human.h"

using namespace std;
using namespace sf;

Text createText(Font *font, string string, int characterSize, int x, int y);
Sprite createBackground(Texture *texture, int windowX);
Sprite createWall(Texture *texture, int windowX);
vector<Mutant*> createMutants(Texture *texture, int windowX, string mutantType);
vector<FloatRect> getBounds(vector<Mutant*> mutants);
void avoidBorders(Sprite *sprite, int windowX);
void mutantAvoidBorders(Sprite* sprite, int windowX); // needs separate functions because I don't know how to convert from Sprite* to Sprite type
Sprite createItem(Texture *texture, int windowX);
Mutant* getClosestMonster(vector<Mutant*> m, int px, int py, int range);
int getIndex(vector<Mutant*> mutants, Mutant* m);
bool areMutantsTouching(vector<Mutant*> mutants, int index);



int main() {
	srand(time(NULL)); // you have to run srand once to get better random numbers

	/* window size, the proportions are windowX = 2 * windowY so the background doesn't get stretched weird and using variables saves a 
	lot of time if we ever want to change it
	*/
	const int windowX = 1280;

	// window setup
	RenderWindow window(VideoMode(windowX, windowX / 2), "Roguelike");
	window.setFramerateLimit(30);

	/* text sizes are in terms of x because there's more risk of heading off of the window in that dimension than with y, although it
	doesn't matter so much now that x and y are proportional to each other
	*/
	int largeTextSize = windowX / 13.33;
	int mediumTextSize = windowX / 16;
	int smallTextSize = windowX / 26.67;

	// setting up font
	Font font;
	font.loadFromFile("arial.ttf"); // you have to have this in the same folder as this program and saved under the same name as it is here for this to load

	// title
	Text title = createText(&font, "Roguelike", largeTextSize, windowX / 2, windowX / 8);

	// start button
	Text start = createText(&font, "Start Game", mediumTextSize, windowX / 2, windowX / 4);
	FloatRect startBounds = start.getGlobalBounds();

	// menu link (I don't know what the menu would have so it's going to link to a blank page for now)
	Text menu = createText(&font, "Menu", smallTextSize, windowX / 4, windowX / 2.67); // dividing by 2.67 gives ~3/8 of original value
	FloatRect menuBounds = menu.getGlobalBounds(); // helpful for determining if something has been clicked

	// controls link
	Text controls = createText(&font, "Controls", smallTextSize, windowX / 1.33, windowX / 2.67);
	FloatRect controlsBounds = controls.getGlobalBounds();

	// controls list
	Text controlKeys = createText(&font, "Movement - WASD\nAttack - Up Arrow\nDodge - Down Arrow\nSelect - Left Click\nPick Up/Use Item - Right Click", smallTextSize, windowX / 2, windowX / 6);

	// back button (from menu and controls list)
	Text back = createText(&font, "Back", smallTextSize, windowX / 2, windowX / 2.67);
	FloatRect backBounds = back.getGlobalBounds();

	// backstory
	// don't mess with the spacing here unless you're messing with the words too, the way it is right now is mostly aligned and centered
	Text intro = createText(&font, "A dangerous chemical has been released and has infected\n\
		people and animals in the area. You are a scientist\n\
		and must fight your way to your laboratory so that\n\
	 you can stop its spread, synthesize a cure to reverse\n\
			  its effects, and save the world. Good luck!", smallTextSize, windowX / 2, windowX / 8);

	// continue
	Text clickContinue = createText(&font, "Click here to continue", smallTextSize, windowX / 2, windowX / 2.67);
	FloatRect continueBounds = clickContinue.getGlobalBounds();

	// right bound is the only one that needs to be here
	RectangleShape right;
	right.setSize(Vector2f(1, windowX / 2));
	right.setPosition(windowX, 0);
	FloatRect rightBound = right.getGlobalBounds();

	// backgrounds, in order of which appears first
	vector<Sprite> backgrounds; 

	Texture caveTexture;
	caveTexture.loadFromFile("Cave_Area_1.png");
	backgrounds.push_back(createBackground(&caveTexture, windowX));

	Texture junkyardTexture;
	junkyardTexture.loadFromFile("Junkyard_Area_2.png");
	backgrounds.push_back(createBackground(&junkyardTexture, windowX));

	Texture catacombsTexture;
	catacombsTexture.loadFromFile("Catacombs_Area_3.png");
	backgrounds.push_back(createBackground(&catacombsTexture, windowX));

	Texture forestTexture;
	forestTexture.loadFromFile("Forest_Area_4.png");
	backgrounds.push_back(createBackground(&forestTexture, windowX));

	Texture labTexture;
	labTexture.loadFromFile("Lab_Area_5.png");
	backgrounds.push_back(createBackground(&labTexture, windowX));

	// walls
	vector<Sprite> walls;

	Texture caveWallTexture;
	caveWallTexture.loadFromFile("Cave_Wall.png");
	walls.push_back(createWall(&caveWallTexture, windowX));

	Texture junkyardWallTexture;
	junkyardWallTexture.loadFromFile("Junkyard_Wall.png");
	walls.push_back(createWall(&junkyardWallTexture, windowX));

	Texture catacombsWallTexture;
	catacombsWallTexture.loadFromFile("Catacombs_Wall.png");
	walls.push_back(createWall(&catacombsWallTexture, windowX));

	Texture forestWallTexture;
	forestWallTexture.loadFromFile("Forest_Wall.png");
	walls.push_back(createWall(&forestWallTexture, windowX));

	Texture labWallTexture;
	labWallTexture.loadFromFile("Lab_Wall.png");
	walls.push_back(createWall(&labWallTexture, windowX));

	vector<bool> isWallDown;
	for (int i = 0; i < 5; i++) {
		isWallDown.push_back(false); // has the player dealt with this wall yet?
	}
	FloatRect wallBounds = walls[0].getGlobalBounds(); // walls are all the same size

	// monsters
	// monster numbers stored and dependent on windowX so that they can be easily changed, we can figure out a nice density later
	int spiderNum = windowX / 320;
	int batsNum = windowX / 320;
	int dogNum = windowX / 320;
	int bearNum = windowX / 320;
	int humanNum = windowX / 320;
	int mutantNum = spiderNum + batsNum + dogNum + bearNum + humanNum;

	// number of units monsters can move each frame
	const int tileX = windowX / 426.67;
	const int tileY = windowX / 426.67;

	// Storing each monster
	vector<Mutant*> mutants; // Needs to store pointers to mutants, because mutants are declared inside a scope but used outside, meaning if they aren't in the heap they get deleted after exiting the scope
	vector<FloatRect> mutantBounds;

	// spiders setup
	Texture spiderTexture;
	spiderTexture.loadFromFile("Mutant_Spider.png");
	vector<Mutant*> spiders = createMutants(&spiderTexture, windowX, "Spider"); // it's going to be a lot easier if there are separate vectors for the different types of mutants in addition to the one for all of them
	mutants.insert(mutants.end(), spiders.begin(), spiders.end()); // adding to total mutants vector
	vector<FloatRect> spiderBounds = getBounds(spiders); // spider bounding boxes
	mutantBounds.insert(mutantBounds.end(), spiderBounds.begin(), spiderBounds.end());

	// dogs setup
	Texture dogTexture;
	dogTexture.loadFromFile("Mutant_Dog.png");
	vector<Mutant*> dogs = createMutants(&dogTexture, windowX, "Dog");
	mutants.insert(mutants.end(), dogs.begin(), dogs.end());
	vector<FloatRect> dogBounds = getBounds(dogs);
	mutantBounds.insert(mutantBounds.end(), dogBounds.begin(), dogBounds.end());

	// bats setup
	Texture batTexture;
	batTexture.loadFromFile("Mutant_Bats.png");
	vector<Mutant*> bats = createMutants(&batTexture, windowX, "Bats");
	mutants.insert(mutants.end(), bats.begin(), bats.end());
	vector<FloatRect> batBounds = getBounds(bats);
	mutantBounds.insert(mutantBounds.end(), batBounds.begin(), batBounds.end());

	// bears setup
	Texture bearTexture;
	bearTexture.loadFromFile("Mutant_Bear.png");
	vector<Mutant*> bears = createMutants(&bearTexture, windowX, "Bear");
	mutants.insert(mutants.end(), bears.begin(), bears.end());
	vector<FloatRect> bearBounds = getBounds(bears);
	mutantBounds.insert(mutantBounds.end(), bearBounds.begin(), bearBounds.end());

	// human sprite setup
	Texture humanTexture;
	humanTexture.loadFromFile("Mutant_Human.png");
	vector<Mutant*> humans = createMutants(&humanTexture, windowX, "Human");
	mutants.insert(mutants.end(), humans.begin(), humans.end());
	vector<FloatRect> humanBounds = getBounds(humans);
	mutantBounds.insert(mutantBounds.end(), humanBounds.begin(), humanBounds.end());

	// number of units player can move
	const int pTileX = windowX / 320;
	const int pTileY = windowX / 320;

	//Player stats
	int playerHealth = 40;
	int playerDamage = 3;
	int atkCooldown = 5; // cooldown in frames  (so you can't attack once a frame)
	int cooldown = atkCooldown; // countdown to cooldown over
	int playerX = 0; // Coords set on sprite, change if you change where the sprite spawns
	int playerY = windowX / 4;
	int playerRange = windowX / 12.8; // some range for player attack range

	// player sprite setup
	Texture playerTexture;
	playerTexture.loadFromFile("Human_Player_Character.png"); // loading sprite sheet
	// setting up sprite
	Sprite player; // name
	player.setTexture(playerTexture); // setting texture
	player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2); // it is a lot easier to have the origin at the center of a sprite
	player.setPosition(playerX, playerY); // begin at left and center
	player.scale(Vector2f(4.f, 4.f));
	avoidBorders(&player, windowX);
	FloatRect playerBounds = player.getGlobalBounds();

	// items
	vector<Sprite> items;

	Texture pickaxeTexture;
	pickaxeTexture.loadFromFile("Pickaxe_Item.png");
	items.push_back(createItem(&pickaxeTexture, windowX));

	Texture trashCanTexture;
	trashCanTexture.loadFromFile("Trash_Can_Item.png");
	items.push_back(createItem(&trashCanTexture, windowX));

	Texture swordTexture;
	swordTexture.loadFromFile("Sword_Item.png");
	items.push_back(createItem(&swordTexture, windowX));

	Texture axeTexture;
	axeTexture.loadFromFile("Axe_Item.png");
	items.push_back(createItem(&axeTexture, windowX));

	Texture keyTexture;
	keyTexture.loadFromFile("Key_Item.png");
	items.push_back(createItem(&keyTexture, windowX));

	vector<FloatRect> itemBounds;
	vector<bool> isItemInInventory;
	for (int i = 0; i < 5; i++) {
		avoidBorders(&items[i], windowX);																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													
		itemBounds.push_back(items[i].getGlobalBounds());
		isItemInInventory.push_back(false);
	}

	int screen = 0; // which screen is showing
	int index;
	bool isLeftButtonPressed = false; // avoiding spam clicks or things where multiple things get selected
	bool isRightButtonPressed = false; // I haven't really thought about it yet but this feels like something we'll need once we start working on those controls
	bool isUpArrowPressed = false; // it feels like you shouldn't be able to fight and dodge at the same time
	bool isDownArrowPressed = false;
	int directionsx[4] = { -1, 1, 0, 0 }; // stores direction multipliers for x
	int directionsy[4] = { 0, 0, -1, 1 }; // same for y

	// drawing stuff
	while (window.isOpen()) {

		playerBounds = player.getGlobalBounds();

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
			// checking for up/down arrow releases (triggers for fighting/dodging, respectively)
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Up) {
					isUpArrowPressed = false;
				}
				if (event.key.code == Keyboard::Down) {
					isDownArrowPressed = false;
				}
			}
		}
		
		if (cooldown > 0) {
			cooldown--;
		}

		window.clear();

		Vector2f mouseCoordinates = Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		// if mouse is pressed
		if (Mouse::isButtonPressed(Mouse::Left) && isLeftButtonPressed == false && isRightButtonPressed == false) { // if left mouse button is clicked (not held down)
			isLeftButtonPressed = true; // so that it can't be held down

			// if mouse is touching start text and it's the right screen
			if ((startBounds.contains(mouseCoordinates)) && (screen == 0)) {
				screen = 1; // change screen to start screen
			}
			else if (menuBounds.contains(mouseCoordinates) && screen == 0) {
				screen = 2;
			}
			else if (controlsBounds.contains(mouseCoordinates) && screen == 0) {
				screen = 3;
			}
			else if (backBounds.contains(mouseCoordinates) && screen == 2 || screen == 3) {
				screen = 0;
			}
			else if (continueBounds.contains(mouseCoordinates) && screen == 1) {
				screen = 4;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Right) && isLeftButtonPressed == false && isRightButtonPressed == false) {
			for (int i = 0; i < 5; i++) {
				if (screen == i + 4) {
					if (itemBounds[i].contains(mouseCoordinates) && itemBounds[i].intersects(playerBounds)) {
						isItemInInventory[i] = true;
					}
					if (wallBounds.intersects(playerBounds) && wallBounds.contains(mouseCoordinates) && isItemInInventory[i] == true) {
						isWallDown[i] = true;
					}
				}
			}
		}

		index = screen - 4;

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.move(0, -1 * pTileY); // there are other ways to do this (like a get position, set position thing) but this is shorter
			avoidBorders(&player, windowX);
		}
		// moves player (tile size) units left if A key is pressed
		else if (Keyboard::isKeyPressed(Keyboard::A)) { // else if because player should only move in one direction at a time
			//isAPressed = true;
			player.move(-1 * pTileX, 0);
			avoidBorders(&player, windowX);
		}
		// moves player (tile size) units down if S key is pressed
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			//isSPressed = true;
			player.move(0, pTileY);
			avoidBorders(&player, windowX);
		}
		// moves player (tile size) units right if D key is pressed
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			//isDPressed = true;
			player.move(pTileX, 0);
			if (isWallDown[index] == true) {
				if (playerBounds.intersects(rightBound)) {
					screen++;
					player.setPosition(0, windowX / 4);

				}
			}
			
			else {
				avoidBorders(&player, windowX);
			}
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Up) && cooldown <= 0) {
			//isUpArrowPressed = true;
			cooldown = atkCooldown;

			Mutant* m = getClosestMonster(mutants, playerX, playerY, playerRange);

			if (m == NULL) {
				cout << "No monsters in range!" << endl;
				//other out of range things
			}
			else {
				cout << "monster in range!!!!!!!" << endl;
				m->takeDamage(playerDamage);
				m->reportStatus();
			}
		}
		vector<Mutant*>::iterator it = mutants.begin();
		while (it != mutants.end()) {
			Mutant* m = *it;
			if (m->isDead() == true) { //remove dead monsters
				it = mutants.erase(it);
				delete m;
				continue;
			}

			it++;

			if (rand() % 10 == 0) { // % chance to reupdate direction
				m->setDirection(rand() % 4);
			}

			int mDir = m->getDirection();

			if (m->getType().compare("Dog") == 0) { //Bear and dog need a bit of extra texture manipulation (directional sprites)
				m->getSprite()->setTextureRect(mDir == 0 ? IntRect(0, 0, 32, 32) : IntRect(0, 32, 32, 32)); //Short ternary statement basically choosing which half of the sprite to use (untested, both bear and dog aren't used yet)
			}
			if (m->getType().compare("Bear") == 0) {
				m->getSprite()->setTextureRect(mDir == 1 ? IntRect(0, 0, 32, 32) : IntRect(0, 32, 32, 32)); //Short ternary statement basically choosing which half of the sprite to use (untested, both bear and dog aren't used yet
			}

			if ((directionsx[mDir] < 0 || directionsx[mDir] > 0 || directionsy[mDir] < 0 || directionsy[mDir] > 0)
				&& areMutantsTouching(mutants, getIndex(mutants, m)) == true) {
				m->move(directionsx[mDir] * tileX, directionsy[mDir] * tileY);
				mutantAvoidBorders(m->getSprite(), windowX);
			}
			else //Give it a new direction to move in 
				m->setDirection(rand() % 4);
		}

		if (screen == 0) { // checking which screen should be showing, this one is the first screen that pops up
			// draw what's supposed to be on that screen
			menu.setPosition(windowX / 4, windowX / 2.67); // menu text moves around on certain screens so it has to be reset each time
			controls.setPosition(windowX / 1.33, windowX / 2.67);
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
		if (screen >= 4 && screen < 9) { // at this point it's all monster rooms from here for now
			index = screen - 4;
			window.draw(backgrounds[index]);
			if (isWallDown[index] == false) {
				window.draw(walls[index]);
			}
			
			if (isItemInInventory[index] == false) { //Doesn't draw the item if it's already been picked up by the player
				window.draw(items[index]);
			}


			window.draw(player);
			// this monster shows up in this room
			if (screen == 4) {
				vector<Mutant*>::iterator it = spiders.begin();
				while (it != spiders.end()) {
					window.draw(*((*it)->getSprite())); //if the mutant isn't dead draw it
					it++;
				}
			}
			if (screen == 5) {
				vector<Mutant*>::iterator it = dogs.begin();
				while (it != dogs.end()) {
					window.draw(*((*it)->getSprite())); //if the mutant isn't dead draw it
					it++;
				}
			}
			if (screen == 6) {
				vector<Mutant*>::iterator it = bats.begin();
				while (it != bats.end()) {
					window.draw(*((*it)->getSprite())); //if the mutant isn't dead draw it
					it++;
				}
			}
			if (screen == 7) {
				vector<Mutant*>::iterator it = bears.begin();
				while (it != bears.end()) {
					window.draw(*((*it)->getSprite())); //if the mutant isn't dead draw it
					it++;
				}
			}
			if (screen == 8) {
				vector<Mutant*>::iterator it = humans.begin();
				while (it != humans.end()) {
					window.draw(*((*it)->getSprite())); //if the mutant isn't dead draw it
					it++;
				}
			}
		}
		window.display();
	}
}

Text createText(Font *font, string string, int characterSize, int x, int y) {
	Text text;
	text.setFont(*font);
	text.setString(string);
	text.setCharacterSize(characterSize);
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(x, y);
	text.setFillColor(Color(255, 255, 255));

	return text;
}

Sprite createBackground(Texture *texture, int windowX) {
	Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setPosition(0, 0);
	sprite.setScale(windowX / sprite.getLocalBounds().width, windowX / (2 * sprite.getLocalBounds().height)); // this is supposed to be absolute size but somehow it's scale factors?
	sprite.setPosition(0, 0);

	return sprite;
}

Sprite createWall(Texture *texture, int windowX) {
	Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setScale(windowX / (8.53 * sprite.getLocalBounds().width), windowX / (2 * sprite.getLocalBounds().height));
	sprite.setPosition(windowX - sprite.getGlobalBounds().width, 0);

	return sprite;
}

vector<Mutant*> createMutants(Texture *texture, int windowX, string mutantType) {
	
	Sprite* sprite;

	Mutant* mutant;


	vector<Mutant*> mutants;

	for (int i = 0; i < windowX / 320; i++) {
		sprite = new Sprite();
		mutant = new Mutant();

		sprite->setTexture(*texture);

		sprite->setTextureRect(IntRect(0, 0, 32, 32)); //Prevents some of the sprites from looking smushed (the bear & dog were having issues)

		sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);
		sprite->setScale(windowX / (13.33 * sprite->getLocalBounds().width), windowX / (13.33 * sprite->getLocalBounds().height));

		int x = rand() % (windowX / 3) * 3;
		int y = rand() % (windowX / 6) * 3;
		sprite->setPosition(x, y);

		if (mutantType == "Spider") {
			mutant = new Spider(10, 2, x, y); // Hp, Attack damage, x, y (coords)
		}
		if (mutantType == "Dog") {
			mutant = new Dog(10, 10, x, y);

		}
		if (mutantType == "Bats") {
			mutant = new Bat(10, 10, x, y);
		}
		if (mutantType == "Bear") {
			mutant = new Bear(10, 10, x, y);
		}
		if (mutantType == "Human") {
			mutant = new Human(10, 10, x, y);
		}

		mutant->setSprite(sprite);

		mutants.push_back(mutant);
	}

	return mutants;
}

vector<FloatRect> getBounds(vector<Mutant*> mutants) {
	vector<FloatRect> mutantBounds;
	for (int i = 0; i < mutants.size(); i++) {
		mutantBounds.push_back(mutants.at(i)->getSprite()->getGlobalBounds());
	}

	return mutantBounds;
}

void avoidBorders(Sprite *sprite, int windowX) {
	// borders for sprite-window border collision checks
	RectangleShape top;
	top.setSize(Vector2f(windowX, 1));
	top.setPosition(0, 0);
	FloatRect topBound = top.getGlobalBounds(); // this command stores the rectangle the text takes up (location and size), used here for sprite-window border collision checks

	RectangleShape left;
	left.setSize(Vector2f(1, windowX / 2));
	left.setPosition(0, 0);
	FloatRect leftBound = left.getGlobalBounds();

	RectangleShape bottom;
	bottom.setSize(Vector2f(windowX, 1));
	bottom.setPosition(0, windowX / 2);
	FloatRect bottomBound = bottom.getGlobalBounds();

	RectangleShape right;
	right.setSize(Vector2f(1, windowX / 2));
	right.setPosition(windowX / 1.13, 0);
	FloatRect rightBound = right.getGlobalBounds();

	FloatRect spriteBounds = sprite->getGlobalBounds();
	while (spriteBounds.intersects(topBound)) {
		sprite->move(0, windowX / 320);
		spriteBounds = sprite->getGlobalBounds();
	}
	while (spriteBounds.intersects(leftBound)) {
		sprite->move(windowX / 320, 0);
		spriteBounds = sprite->getGlobalBounds();
	}
	while (spriteBounds.intersects(bottomBound)) {
		sprite->move(0, -1 * windowX / 320);
		spriteBounds = sprite->getGlobalBounds();
	}
	while (spriteBounds.intersects(rightBound)) {
		sprite->move(-1 * windowX / 320, 0);
		spriteBounds = sprite->getGlobalBounds();
	}
}

void mutantAvoidBorders(Sprite* sprite, int windowX) {
	// borders for sprite-window border collision checks
	RectangleShape top;
	top.setSize(Vector2f(windowX, 1));
	top.setPosition(0, 0);
	FloatRect topBound = top.getGlobalBounds(); // this command stores the rectangle the text takes up (location and size), used here for sprite-window border collision checks

	RectangleShape left;
	left.setSize(Vector2f(1, windowX / 2));
	left.setPosition(0, 0);
	FloatRect leftBound = left.getGlobalBounds();

	RectangleShape bottom;
	bottom.setSize(Vector2f(windowX, 1));
	bottom.setPosition(0, windowX / 2);
	FloatRect bottomBound = bottom.getGlobalBounds();

	RectangleShape right;
	right.setSize(Vector2f(1, windowX / 2));
	right.setPosition(windowX / 1.13, 0);
	FloatRect rightBound = right.getGlobalBounds();

	FloatRect spriteBounds = sprite->getGlobalBounds();
	while (spriteBounds.intersects(topBound)) {
		sprite->move(0, windowX / 320);
		spriteBounds = sprite->getGlobalBounds();
	}
	while (spriteBounds.intersects(leftBound)) {
		sprite->move(windowX / 320, 0);
		spriteBounds = sprite->getGlobalBounds();
	}
	while (spriteBounds.intersects(bottomBound)) {
		sprite->move(0, -1 * windowX / 320);
		spriteBounds = sprite->getGlobalBounds();
	}
	while (spriteBounds.intersects(rightBound)) {
		sprite->move(-1 * windowX / 320, 0);
		spriteBounds = sprite->getGlobalBounds();
	}
}

Sprite createItem(Texture *texture, int windowX) {
	Sprite sprite;
	sprite.setTexture(*texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(windowX / (14.22 * sprite.getLocalBounds().width), windowX / (14.22 * sprite.getLocalBounds().height));
	int x = rand() % (windowX / 4) * 4;
	int y = rand() % (windowX / 8) * 4;
	 
	while (x >= (windowX - 200)) { //Prevents item from spawing out of bounds (i.e. in the wall where player can reach it)
		x = rand() % (windowX / 4) * 4;
	}
	
	sprite.setPosition(x, y);
	return sprite;
}

Mutant* getClosestMonster(vector<Mutant*> m, int px, int py, int range) {
	vector<Mutant*>::iterator it = m.begin();
	double mindist = INT_MAX;
	Mutant* ret = NULL;
	for (; it != m.end(); it++) {
		double dx = (double)(*it)->getX() - px;
		double dy = (double)(*it)->getY() - py;
		double dist = sqrt(dx * dx + dy * dy);
		//cout << "x, y, px, py " << x << ", " << y << ", " << px << ", " << py << "; " << "dist: " << dist << endl;
		if (dist > range) continue;
		if (dist < mindist) {
			mindist = dist;
			ret = (*it);
		}
	}
	return ret;
}

int getIndex(vector<Mutant*> mutants, Mutant* m) {
	vector<Mutant*>::iterator itr = find(mutants.begin(), mutants.end(), m);
	int index;
	if (itr != mutants.cend()) {
		index = distance(mutants.begin(), itr);
	}
	return index;
}

bool areMutantsTouching(vector<Mutant*> mutants, int index) {
	for (int i = 0; i < mutants.size(); i++) {
		FloatRect mutant1Bound = mutants.at(index)->getSprite()->getGlobalBounds();
		FloatRect mutant2Bound = mutants.at(i)->getSprite()->getGlobalBounds();
		if (mutant1Bound.intersects(mutant2Bound)) {
			return true;
		}
	}
	return false;
}