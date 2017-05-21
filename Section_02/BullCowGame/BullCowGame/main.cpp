//
//  main.cpp
//  BullCowGame
//
//  Created by Patrick on 5/10/17.
//  Copyright © 2017 Patrick. All rights reserved.
//

/* This is the console executable, that makes use of the BullCow class
 This acts as the view in a MVC pattern, and is responsible for user interaction. For game logic see the 
 FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

//using namespace std; -- avoid using this if possible

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintBack(FText);
bool AskToPlayAgain();
void PrintGameSummary();


FBullCowGame BCGame; // instantiate a new game


// the entry point to the game
int main(int argc, const char * argv[]) {
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    return 0;
    //exit the application
}

void PrintIntro(){
    // introduce the game
    std::cout << "\n\nThis is Patrick's BullCow game" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?" << std::endl;
    return;
}

void PlayGame(){
    BCGame.Reset();
    // loop for the number of turns asking for guesses while the game is not won
    int32 MaxTries = BCGame.GetMaxTries();
    std::cout << "You have " << MaxTries << " tries" << std::endl;
    
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
        FText guess = GetValidGuess();
        
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
        PrintBack(guess);
        std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
        std::cout << "Cows = " << BullCowCount.Cows << std::endl;
    }
    
    PrintGameSummary();
    return;
}
    
FText GetValidGuess(){
    EGuessStatus Status = EGuessStatus::Invalid;
    FText Guess = "";
    do {
        int32 CurrentTry = BCGame.GetCurrentTry();
        std::cout << std::endl;
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ", Enter your guess: " << std::flush;
        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter your word in all lowercase" << std::endl;
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter an isogram" << std::endl;
                break;
            default:
                break;
        }
        
    } while (Status != EGuessStatus::OK);
    return Guess;
}

void PrintBack(FText Guess){
    // repeat the guess back to them
    std::cout << "Your guess was: " << Guess << std::endl;
    return;
}

bool AskToPlayAgain(){
    std::cout << "Do you want to play again? (y/n)";
    FText Response = "";
    std::getline(std::cin, Response);
    
    return (Response[0] == 'y') || (Response [0] == 'Y');
}

void PrintGameSummary() {
    bool GameStatus = BCGame.IsGameWon();
    std::cout << std::endl;
    if (GameStatus) {
        std::cout << "Congratulations, you have won!" << std::endl;
        }
    else {
        std::cout << "You lose!" << std::endl;
    }
    return;
}



