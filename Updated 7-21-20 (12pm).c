#include<iostream>
using namespace std;
#include<math.h> //Lets us use basic math functions


/*
class Monsters(){
//A class to store all of our "monster" characters and their stats in.

    public:

    private:

};

class Player(){
//A class to store our Player character and their stats in.

    public:

    private:

};

*/

int main(){

    //cout << "Hello world" << endl;








    //NOTICE: Below is just window opening stuff, ignore it for now!

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

}
