#include <math.h>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


int main() {
   
    RenderWindow Window(VideoMode(600, 500), "Health Bar Display Code"); //Creates a window where the graphics will be displayed

    RectangleShape HP1; //Creates a rectangle shape called "HP1" (for healthpoint one)
    RectangleShape HP2;
    RectangleShape HP3;
    RectangleShape HP4;
    RectangleShape HP5;
    RectangleShape HP6;
    RectangleShape HP7;
    RectangleShape HP8;
    RectangleShape HP9;
    RectangleShape HP10;

    int healthPoints = 0; //Place holder for actual health points (to be set when code is merged with player/mutant classes)
    //^^^ X hp out of 10 (with the way the code is currently set up)

    HP1.setSize(Vector2f(50, 30)); //Sets the size of rectangle shape HP1
    HP1.setPosition(0, 470); //Sets position of HP1
    
    HP2.setSize(Vector2f(50, 30));
    HP2.setPosition(60, 470);
   
    HP3.setSize(Vector2f(50, 30));
    HP3.setPosition(120, 470);
  
    HP4.setSize(Vector2f(50, 30));
    HP4.setPosition(180, 470);

    HP5.setSize(Vector2f(50, 30));
    HP5.setPosition(240, 470); 

    HP6.setSize(Vector2f(50, 30));
    HP6.setPosition(300, 470);

    HP7.setSize(Vector2f(50, 30));
    HP7.setPosition(360, 470); 

    HP8.setSize(Vector2f(50, 30));
    HP8.setPosition(420, 470);

    HP9.setSize(Vector2f(50, 30));
    HP9.setPosition(480, 470);

    HP10.setSize(Vector2f(50, 30));
    HP10.setPosition(540, 470);
    

    if(healthPoints == 10) {
        HP1.setFillColor(Color(0, 255, 0, 255)); //Sets color of HP1 (to full opaque/not see through and green)
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(0, 255, 0, 255));
        HP5.setFillColor(Color(0, 255, 0, 255));
        HP6.setFillColor(Color(0, 255, 0, 255));
        HP7.setFillColor(Color(0, 255, 0, 255));
        HP8.setFillColor(Color(0, 255, 0, 255));
        HP9.setFillColor(Color(0, 255, 0, 255));
        HP10.setFillColor(Color(0, 255, 0, 255));
    }

    else if (healthPoints == 9) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(0, 255, 0, 255));
        HP5.setFillColor(Color(0, 255, 0, 255));
        HP6.setFillColor(Color(0, 255, 0, 255));
        HP7.setFillColor(Color(0, 255, 0, 255));
        HP8.setFillColor(Color(0, 255, 0, 255));
        HP9.setFillColor(Color(0, 255, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255)); //Sets color of HP1 (to full opaque/not see through and red)

    }

    else if (healthPoints == 8) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(0, 255, 0, 255));
        HP5.setFillColor(Color(0, 255, 0, 255));
        HP6.setFillColor(Color(0, 255, 0, 255));
        HP7.setFillColor(Color(0, 255, 0, 255));
        HP8.setFillColor(Color(0, 255, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else if (healthPoints == 7) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(0, 255, 0, 255));
        HP5.setFillColor(Color(0, 255, 0, 255));
        HP6.setFillColor(Color(0, 255, 0, 255));
        HP7.setFillColor(Color(0, 255, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else if (healthPoints == 6) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(0, 255, 0, 255));
        HP5.setFillColor(Color(0, 255, 0, 255));
        HP6.setFillColor(Color(0, 255, 0, 255));
        HP7.setFillColor(Color(225, 0, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else if(healthPoints == 5) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(0, 255, 0, 255));
        HP5.setFillColor(Color(0, 255, 0, 255));
        HP6.setFillColor(Color(225, 0, 0, 255));
        HP7.setFillColor(Color(225, 0, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else if(healthPoints == 4) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(0, 255, 0, 255));
        HP5.setFillColor(Color(225, 0, 0, 255));
        HP6.setFillColor(Color(225, 0, 0, 255));
        HP7.setFillColor(Color(225, 0, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else if (healthPoints == 3) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(0, 255, 0, 255));
        HP4.setFillColor(Color(225, 0, 0, 255));
        HP5.setFillColor(Color(225, 0, 0, 255));
        HP6.setFillColor(Color(225, 0, 0, 255));
        HP7.setFillColor(Color(225, 0, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else if (healthPoints == 2) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(0, 255, 0, 255));
        HP3.setFillColor(Color(225, 0, 0, 255));
        HP4.setFillColor(Color(225, 0, 0, 255));
        HP5.setFillColor(Color(225, 0, 0, 255));
        HP6.setFillColor(Color(225, 0, 0, 255));
        HP7.setFillColor(Color(225, 0, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else if (healthPoints == 1) {
        HP1.setFillColor(Color(0, 255, 0, 255));
        HP2.setFillColor(Color(225, 0, 0, 255));
        HP3.setFillColor(Color(225, 0, 0, 255));
        HP4.setFillColor(Color(225, 0, 0, 255));
        HP5.setFillColor(Color(225, 0, 0, 255));
        HP6.setFillColor(Color(225, 0, 0, 255));
        HP7.setFillColor(Color(225, 0, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }

    else{
        HP1.setFillColor(Color(255, 0, 0, 255));
        HP2.setFillColor(Color(225, 0, 0, 255));
        HP3.setFillColor(Color(225, 0, 0, 255));
        HP4.setFillColor(Color(225, 0, 0, 255));
        HP5.setFillColor(Color(225, 0, 0, 255));
        HP6.setFillColor(Color(225, 0, 0, 255));
        HP7.setFillColor(Color(225, 0, 0, 255));
        HP8.setFillColor(Color(225, 0, 0, 255));
        HP9.setFillColor(Color(225, 0, 0, 255));
        HP10.setFillColor(Color(225, 0, 0, 255));
    }


    while (Window.isOpen()) {

        Event event;

        while (Window.pollEvent(event)) {

            if (event.type == Event::Closed)
                Window.close();
        }

        Window.clear(); //Clears the window to prepare it for drawing graphics
        
        Window.draw(HP1); // Draws HP1 to the window (not yet displayed)
        Window.draw(HP2);
        Window.draw(HP3);
        Window.draw(HP4);
        Window.draw(HP5);
        Window.draw(HP6);
        Window.draw(HP7);
        Window.draw(HP8);
        Window.draw(HP9);
        Window.draw(HP10);
        
        Window.display(); //Displays the shapes drawn on the window
    }

}