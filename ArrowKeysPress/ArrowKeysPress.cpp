#include <conio.h>
#include <iostream>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
    int in = 0; // Variable Name "in" Stands for Input


    while(in = getch())
    {

        switch(in) {
        case KEY_UP:
            cout << endl << "Up Arrow Key Was Pressed" << endl; // Detect Up Arrow Key
            break;
        case KEY_DOWN:
            cout << endl << "Down Arrow Key Was Pressed" << endl; // Detect Down Arrow Key
            break;
        case KEY_LEFT:
            cout << endl << "Left Arrow Key Was Pressed" << endl; // Detect Left Arrow Key
            break;
        case KEY_RIGHT:
            cout << endl << "Right Arrow Key Was Pressed" << endl; // Detect Right Arrow Key
            break;
        }

    }

    return 0;
}
