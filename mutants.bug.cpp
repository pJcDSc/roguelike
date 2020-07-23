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

class Mutant{

    public:
        int healthPoints;
        int attackDamage;
        string mutantName;
        string attackName;
        Mutant(string mtntName);
        void reportStatus();
};

Mutant::Mutant(string mtntName){
    if(mtntName == "Human"){
        healthPoints = 100;
        attackName = "Smack";
    }
    if(mtntName == "Bear"){
        healthPoints = 60;
        attackName = "Claw";
    }
    if(mtntName == "Bats"){
        healthPoints = 40;
        attackName = "Razor wings";
    }
    if(mtntName == "Dog"){
        healthPoints = 20;
        attackName = "Bite";
    }
    if(mtntName == "Spider"){
        healthPoints = 10;
        attackName = "Poison";
    }

    attackDamage = healthPoints/2;
    mutantName = mtntName;
}

void Mutant::reportStatus(){
    //Function to report the stats of the mutant "objects"/characters.
    cout << mutantName << ":" << endl;
    cout << "Health: " << healthPoints << endl;
    cout << "Damage: " << attackDamage << endl;
    cout << "Attack: " << attackName << endl;
}

int main(){

    //Initialize Mutants, set to default values:
    Mutant Human("Human");
    Mutant Bear("Bear");
    Mutant Bats("Bats");
    Mutant Dog("Dog");
    Mutant Spider("Spider");

    //Print out stats for all mutants:
    Human.reportStatus();
    Bear.reportStatus();
    Bats.reportStatus();
    Dog.reportStatus();
    Spider.reportStatus();

}
