#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//Don't use "using namespace" in header files!
//Const after a method header makes sure that member vars can't be modified in the method - only works on member functions
//constexpr requires variables to be known at compile time


//All values initialized to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame 
{
public:
	FBullCowGame(); //Constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	bool CheckGuessValidity(FString) const; //TODO make a more rich return value

	void Reset(); //TODO make a more rich return value
	FBullCowCount SubmitGuess(FString);

private:
	//See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};

