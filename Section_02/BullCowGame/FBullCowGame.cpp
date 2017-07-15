#pragma once
#include "FBullCowGame.h"
#include <map>

//To make syntax more Unreal friendly
#define TMap std::map
using int32 = int;


FBullCowGame::FBullCowGame() //Default constructor
{
	Reset();
}

void FBullCowGame::Reset()
{
	//MyHiddenWord is set with SetHiddenWordByLength
	MyCurrentTry = 1;
	MyMinWordLength = 3;
	MyMaxWordLength = 7;
	bIsGameWon = false;

	return;
}



int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

//Sets the hidden word length by swapping the hidden word to an appropriate length
void FBullCowGame::SetHiddenWordByLength(int32 len)
{
	TMap<int32, FString> words{ {3, "dog"} ,{4, "rats"}, {5, "plane"}, {6, "plains"}, {7, "planets"} };
	MyHiddenWord = words[len];
}

bool FBullCowGame::IsGameWon() const{ return bIsGameWon; }


int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 3}, {4, 4}, {5,5}, {6,6}, {7,8} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}





EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if guess isn't an isogram, return error
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram; 
	}
	//if guess isn't all lowercase, return error 
	else if (!IsLowercase(Guess)) {
		return EGuessStatus::Not_Lowercase; 
	}
	//if guess length is wrong, return error
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	//otherwise, return ok
	else {
		return EGuessStatus::OK;
	}
}

//Receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //Assuming the same length as guess

	//loop through all letters in the hidden word
	for (int32 HWChar = 0; HWChar < WordLength; HWChar++) 
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			//if they match
			if (MyHiddenWord[HWChar] == Guess[GChar]) {
				//increment bulls if they're in the same place
				if (HWChar == GChar) {
					BullCowCount.Bulls++;
				}
				//increment cows if they're not
				else {
					BullCowCount.Cows++;
				}
			}
		}

	}

	if (BullCowCount.Bulls == WordLength)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}

	return BullCowCount;
}

FWordLengthConstraints FBullCowGame::GetLengthConstraints() const
{
	FWordLengthConstraints wlc; 
	wlc.Max = MyMaxWordLength;
	wlc.Min = MyMinWordLength;
	return wlc;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	//Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
		return true;
	//Setup our map
	TMap<char, bool> LetterSeen;
	//Go through each character of word
	for (auto Letter : Word) //For all letters of the Word (auto means the compiler will figure out the type for us)
	{
		Letter = tolower(Letter); //Handle mixed case
		//If we've seen it already
		if (LetterSeen[Letter])
			return false; //We do not have an isogram
		//otherwise, add it to the map with a true value
		LetterSeen[Letter] = true;
	}

	return true; //for example when /0 is entered (the escape character)
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
			return false;
	}
	return true;
}
