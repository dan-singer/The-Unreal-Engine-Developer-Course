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

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if guess isn't an isogram, return error
	if (false) {
		return EGuessStatus::Not_Isogram;
	}
	//if guess isn't all lowercase, return error
	else if (false) {
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

	return BullCowCount;
}
