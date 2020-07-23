#include <conio.h>
#include <iostream>
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

int main()
{
    int in = 0;
    while(1)
    {
        in = 0;

        switch((in = getch())) {
        case KEY_UP:
            cout << endl << "Up" << endl; // Detect Up Arrow Key
            break;
        case KEY_DOWN:
            cout << endl << "Down" << endl; // Detect Down Arrow Key
            break;
        case KEY_LEFT:
            cout << endl << "Left" << endl; // Detect Left Arrow Key
            break;
        case KEY_RIGHT:
            cout << endl << "Right" << endl; // Detect Right Arrow Key
            break;
        }

    }

    return 0;
}
