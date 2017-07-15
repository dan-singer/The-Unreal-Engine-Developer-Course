/* This is the console executable that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//To make syntax Unreal-friendly
using FText = std::string;
using int32 = int;

//function prototypes outside of a class
void PrintIntro();
void GetWordLengthFromUser();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();


FBullCowGame BCGame; //instantiate a new game, which we reuse across plays


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

void PrintIntro()
{
	int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "         -----           " << std::endl;
	std::cout << "        - ||| -          " << std::endl;
	std::cout << "         -----           " << std::endl;
	return;
}



//Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	GetWordLengthFromUser();
	int32 MaxTries = BCGame.GetMaxTries();
	//Loop asking for guesses while game is not won and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) { 
		FText Guess = GetValidGuess(); 

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}
	PrintGameSummary();
	return;

}


//Have the user select a word length, and then send that to BCGame. 
//Currently does not account for non-number inputs
void GetWordLengthFromUser()
{
	FWordLengthConstraints constraints = BCGame.GetLengthConstraints();
	int32 length = 0;
	bool wrong = length < constraints.Min || length > constraints.Max;
	do
	{
		std::cout << "Select a word length between " << constraints.Min << " and " << constraints.Max << " : ";
		FString input = "";
		std::getline(std::cin, input);
		length = std::stoi(input);
		wrong = length < constraints.Min || length > constraints.Max;

		if (wrong)
		{
			std::cout << "Invalid word length!" << std::endl;
		}
	} while (wrong);
	BCGame.SetHiddenWordByLength(length);

}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You Won!";
	}
	else
	{
		std::cout << "Better luck next time!";
	}
	std::cout << std::endl;
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
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter your guess : ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n\n";
				break;
			default:
				//Assume guess is valid.
				break;
		}
		} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return Guess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (Y/N) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'Y' || Response[0] == 'y');
}
