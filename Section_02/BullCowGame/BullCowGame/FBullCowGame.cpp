//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Patrick on 5/17/17.
//  Copyright © 2017 Patrick. All rights reserved.
//

#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame(){
    Reset();
}


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries {{3,4}, {4,7}, {5,10}, {6,15}, {7,20}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
    
    const FString HIDDEN_WORD = "planets";
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameWon = false;
    
    return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess)) {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}

// reveives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess){
    
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    
    // loop through all leters in the hidden word
    int32 WordLength = MyHiddenWord.length();
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
        // compare letters against the guess
        for (int32 GChar = 0; GChar < WordLength; GChar++) {
            // if they match then
            if (Guess[MHWChar] == MyHiddenWord[GChar]){
                // if they're in the same place
                if (MHWChar == GChar){
                    // increment bulls
                    BullCowCount.Bulls++;
                }
                // if not
                else {
                    // increment cows
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if (BullCowCount.Bulls == WordLength) {
        bGameWon = true;
    }
    else {
        bGameWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
    
    if (Word.length() <= 1) { return true; }
    bool Status = true;
    TMap<char, bool> LetterSeen;
    for (auto Letter : Word) {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) {
            Status = false; // not an isogram
        } else {
            LetterSeen[Letter] = true;
        }
    }
    return Status;
}

bool FBullCowGame::IsLowercase(FString Word) const {
    if (Word.length() <= 1) { return true; }
    bool Status = true;
    for (auto Letter : Word) {
        if (!islower(Letter)) {
            Status = false;
        }
    }
    return Status;
}
