#include "FBullCowGame.h"


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "donkey"; //constexpr is too strong

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;

	return;
}



int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString) const
{
	return false;
}

//Receives a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment turn number
	MyCurrentTry++;
	//setup a return structure
	FBullCowCount BullCowCount;

	int32 MyHiddenWordLength = MyHiddenWord.length();
	//loop through all letters in the hidden word
	for (int32 HWChar = 0; HWChar < MyHiddenWordLength; HWChar++) 
	{
		//compare letters against the guess (they have the same length)
		for (int32 GChar = 0; GChar < MyHiddenWordLength; GChar++) 
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

	return BullCowCount;
}
