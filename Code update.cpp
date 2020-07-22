#include<iostream>
using namespace std;
#include<math.h> //Lets us use basic math functions


class Mutants{
//A class to store all of our mutant/monster characters and their stats in.

    public:
        int healthPoints; //Initializes/creates an integer for health points.
        int attackStrength;
        string mutantName;//Initializes/creates a string for the mutant's name.
        string attackName;
        void reportStatus();
        Mutant(int hlthPnts, int attckStrngth, string mtntName, string attckName);
        //^^^ Dictates what characteristics every "mutant" needs to have.

};

void Mutants::reportStatus(){
    cout << mutantName << ":" << endl;
    cout << "HP: " << healthPoints << endl;
    cout << "AP: " << attackStrength << endl;
    cout << "AN: " << attackName << endl;

}

Mutants::Human(int hlthPnts = 100, int attckStrngth = 50, string mtntName = "Human", string attckName = "FILLER"){
//Human character, of class "mutants".
//Above sets stats at the start of game, below sets the class stats equal to starting stats.
    healthPoints = hlthPnts;
    attackStrength = attckStrngth;
    mutantName = mtntName;
    attackName = attckName;

}

Mutants::Bear(int hlthPnts = 60, int atckStrngth = 30, string mtntName = "Bear", string attckName = "FILLER"){
//Bear character, of class "mutants".
//Above sets stats at the start of game, below sets the class stats equal to starting stats.
    healthPoints = hlthPnts;
    attackStrength = attckStrngth;
    mutantName = mtntName;
    attackName = attckName;

}

Mutants::BirdBat(int hlthPnts = 40, int attckStrngth = 20, string mtntName = "Birds/Bats", string attckName = "FILLER"){
//Bird or Bat (group of) character(s), of class "mutants".
//Above sets stats at the start of game, below sets the class stats equal to starting stats.
    healthPoints = hlthPnts;
    attackStrength = attckStrngth;
    mutantName = mtntName;
    attackName = attckName;

}

Mutants::Dog(int hlthPnts = 20, int attckStrngth = 10, string mtntName = "Dog", string attckName = "FILLER"){
//Dog character, of class "mutants".
//Above sets stats at the start of game, below sets the class stats equal to starting stats.
    healthPoints = hlthPnts;
    attackStrength = attckStrngth;
    mutantName = mtntName;
    attackName = attckName;

}

Mutants::Spider(int hlthPnts = 10, int attckStrngth = 5, string mtntName = "Spider", string attckName = "FILLER"){
//Spider character, of class "mutants".
//Above sets stats at the start of game, below sets the class stats equal to starting stats.
    healthPoints = hlthPnts;
    attackStrength = attckStrngth;
    mutantName = mtntName;
    attackName = attckName;

}

/*

//Ignore this for now, haven't set up/decided sats for player yet.

class Player{
//A class to store our Player character and their stats in.

    public:
        string plyrName;
        int plyrHealth;
        int plyrAttackStrength;
};
*/

int main(){


    Mutant Human;
    Mutant Bear;
    Mutant BirdBat;
    Mutant Dog;
    Mutant Spider;

    Human.reportStatus();
    Bear.reportStatus();
    BirdBat.reportStatus();
    Dog.reportStatus();
    Spider.reportStatus();


    //NOTICE: Below is just window opening stuff, ignore it for now!

    /*
    while(Window.isOpen()){
    //Open drawing window.

        Event event; // events are things like key presses and mouse movement

    	while(Window.pollEvent(event)){
        	//This lets us close the window by clicking on the "X"
        	if(event.type == Event::Closed)
            	Window.close();
        }

    	Window.clear(); //Start drawing by clearing window. (Makes a blank canvas basically.)

    	//This is where you draw everything before you "reveal"/display it to the user.

    	Window.display(); //End drawing by "revealing" what you drew.
	}
    */
}
