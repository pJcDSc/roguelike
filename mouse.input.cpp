#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main(){
    RenderWindow myWindow(VideoMode(800,600), "Mouse Input");
    // bools are so we don't get spam clicks
    bool isLeftButtonDown = false;
    bool isRightButtonDown = false;
    Mouse myMouse;

    while(myWindow.isOpen()){
        Event event;
        while(myWindow.pollEvent(event)){
            if(event.type == Event::Closed){
                myWindow.close();
            }
            if(event.type == Event::MouseButtonReleased){
                // this should print "Left button released" if the left button of the mouse is in fact released
                if(event.mouseButton.button == Mouse::Left){
                    isLeftButtonDown = false;
                    cout << "Left button released\n";
                }
                // this does the same as the above but for the right button
                if(event.mouseButton.button == Mouse::Right){
                    isRightButtonDown = false;
                    cout << "Right button released\n";
                }
            }
        }
        myWindow.clear();
        if((isLeftButtonDown == false) and (isRightButtonDown == false)){ // if there isn't any clicking happening already
            // this part prints "Left button pressed" if the left button is pressed and stops other things from being printed until it's released
            if(Mouse::isButtonPressed(Mouse::Left)){
                isLeftButtonDown = true;
                cout << "Left button pressed\n";
            }
            // this part does the same as the above but for the right button
            else if(Mouse::isButtonPressed(Mouse::Right)){
                isRightButtonDown = true;
                cout << "Right button pressed\n";
            }
        }
    }
}
