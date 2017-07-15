/*
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>
#include <map>
#define TMap std::map

//To make syntax Unreal-friendly
using FString = std::string;
using int32 = int;

//Don't use "using namespace" in header files!
//Const after a method header makes sure that member vars can't be modified in the method - only works on member functions
//constexpr requires variables to be known at compile time


struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

//Simple structure to store the minimum and maximum word lengths available
struct FWordLengthConstraints 
{
	int32 Min = 0;
	int32 Max = 0;
};

//Using class gives enums there own scope, and allows you to reuse enum values, like OK
enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};


class FBullCowGame 
{
public:
	FBullCowGame(); //Constructor
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	void SetHiddenWordByLength(int32);
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);
	FWordLengthConstraints GetLengthConstraints() const;

private:
	//See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxWordLength;
	int32 MyMinWordLength;
	FString MyHiddenWord;
	bool bIsGameWon;
	TMap<int32, FString> MyHiddenWords;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};

