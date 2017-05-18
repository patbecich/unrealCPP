//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Patrick on 5/17/17.
//  Copyright © 2017 Patrick. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

//#include <stdio.h>
#include <string>

#endif /* FBullCowGame_hpp */

class FBullCowGame {
public:
    FBullCowGame(); // constructor
    
    int GetMaxTries() const;
    int GetCurrentTry() const;
    bool IsGameWon() const;
    
    void Reset(); // TODO make a more rich return value
    bool CheckGuessValidity(std::string); // TODO make a more rich return value
    // provide a method for counting bulls and cows, and increasing turn number
    
private: // dont expose any variables publicly, they stay private
    // see constructor for initialization
    int MyCurrentTry;
    int MyMaxTries;
    bool IsIsogram;
    
};
