#include <iostream>
#include <conio.h>
using namespace std;



int main()
{
    int in = 0; // Variable Name "in" Stands for Input

    while(in = getch())
    {

        switch(in)
        {
            case 'W':
            case 'w':
                cout << "W Key Was Pressed" << endl; // Detects "W" Key
                break;
            case 'A':
            case 'a':
                cout << "A Key Was Pressed" << endl; // Detects "A" Key
                break;
            case 'S':
            case 's':
                cout << "S Key Was Pressed" << endl; // Detects "S" Key
                break;
            case 'D':
            case 'd':
                cout << "D Key Was Pressed" << endl; // Detects "D" Key
                break;

        }

    }

    return 0;
}
