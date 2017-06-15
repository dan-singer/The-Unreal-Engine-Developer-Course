/* This is the console executable that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame; //instantiate a new game


//Entry point for our application
int main() 
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

//introduce game
void PrintIntro()
{
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
	return;
}

//Loop for number of TURNS
void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	//Loop for number of turns asking for guesses
	for (int32 i = 0; i < MaxTries; i++) { 	//TODO change from for to while loop once we validate tries
		FText Guess = GetValidGuess(); 

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}

	//TODO add a game summary

}



//Loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		//Get guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n";
				break;
			default:
				//Assume guess is valid.
				break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'Y' || Response[0] == 'y');
}
