#include<iostream>
using namespace std;

/*Program to test code for setting up all of the stats for each of the Mutant monsters, including their max hp,
hit/attack damage, name, and the name of their attack.

Should show their stats when the program is run, as:
Mutant Name:
Health: HP #
Damage: attack strength #
Attack: attack name
*/

class Mutants{

    public:
        int healthPoints;
        int attackDamage;
        string mutantName;
        string attackName;

        void reportStatus();

        /*
        //Default values:
        Mutants(){
            healthPoints = -1;
            attackDamage = -1;
            mutantName = "bug mutant";
            attackName = "bug name";
        }
        */

        //Substitution values:
        void Mutants(int x, int y, string "z", string "b"){
            //Function to set up the stats of each mutant, so they can be set in int main.
            healthPoints = x;
            attackDamage = y;
            mutantName = "z";
            attackName = "b";
        }

};

void Mutants::reportStatus(){
    //Function to report the stats of the mutant "objects"/characters.
    cout << mutantName << ":" << endl;
    cout << "Health: " << healthPoints << endl;
    cout << "Damage: " << attackDamage << endl;
    cout << "Attack: " << attackName << endl;
}

int main(){

    //Initialize Mutants, set to default values:
    Mutants Human(100, 50, "Human", "Smack (fill)");
    Mutants Bear(60, 30, "Bear", "Claw (fill)");
    Mutants Bats(40, 20 "Bats", "Razor wings (fill)");
    Mutants Dog(20, 10, "Dog", "Bite (fill)");
    Mutants Spider(10, 5, "Spider", "Poison (fill)");

    //Print out stats for all mutants:
    Human.reportStatus();
    Bear.reportStatus();
    Bats.reportStatus();
    Dog.reportStatus();
    Spider.reportStatus();

}
