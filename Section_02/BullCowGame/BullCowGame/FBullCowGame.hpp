//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Patrick on 5/17/17.
//  Copyright © 2017 Patrick. All rights reserved.
//

#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp
#endif /* FBullCowGame_hpp */

//#include <stdio.h>
#include <string>

using FString = std::string;
using int32 = int;

// all values initialized to zero
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    Invalid,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

enum class EResetStatus {
    No_Hidden_Word,
    OK
};
class FBullCowGame {
public:
    FBullCowGame(); // constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset();
    // counts bulls and cows, increases try number, assuming valid guess
    FBullCowCount SubmitValidGuess(FString);
    
private: // dont expose any variables publicly, they stay private
    // see constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameWon;
    
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
    
};
