#include <iostream>
#include <string>

using namespace std;



void PrintIntro();
string GetGuessAndPrintBack();

//Entry point for our application
int main() 
{
	PrintIntro();
	GetGuessAndPrintBack();
	GetGuessAndPrintBack();
	return 0;
}

//introduce game
void PrintIntro() 
{
	constexpr int WORD_LENGTH = 5;
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
	return;
}

//Get the guess from the player
string GetGuessAndPrintBack()
{
	cout << "Enter your guess: ";
	string Guess = "";
	getline(cin, Guess);
	//print guess back to them
	cout << "Your guess was: " << Guess << endl;
	return Guess;
}
