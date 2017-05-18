//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Patrick on 5/17/17.
//  Copyright © 2017 Patrick. All rights reserved.
//

#include "FBullCowGame.hpp"

FBullCowGame::FBullCowGame(){
    Reset();
}

int FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

void FBullCowGame::Reset() {

    constexpr int MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;
    
    MyCurrentTry = 1;
    
    return;
}

bool FBullCowGame::IsGameWon() const {
    
    return false;
}

bool FBullCowGame::CheckGuessValidity(std::string) {
    
    return false;
}
