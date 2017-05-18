//
//  main.cpp
//  BullCowGame
//
//  Created by Patrick on 5/10/17.
//  Copyright © 2017 Patrick. All rights reserved.
//

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

//using namespace std; -- avoid using this if possible

void PrintIntro();
void PlayGame();
std::string GetGuess();
void PrintBack(std::string);
bool AskToPlayAgain();


FBullCowGame BCGame; // instantiate a new game


// the entry point to the game
int main(int argc, const char * argv[]) {
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        // TODO add game summary
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    return 0;
    //exit the application
}

void PrintIntro(){
    // introduce the game
    constexpr int WORD_LENGTH = 9;
    std::cout << "This is Patrick's BullCow game" << std::endl;
    std::cout << "Can you guess the " << WORD_LENGTH;
    std::cout << " letter isogram I'm thinking of?" << std::endl;
    return;
}

void PlayGame(){
    BCGame.Reset();
    // loop for the number of turns asking for guesses
    int MaxTries = BCGame.GetMaxTries();
    std::cout << "You have " << MaxTries << " tries" << std::endl;
    
    for(int count = 0; count < MaxTries; count++){
        std::string guess = GetGuess(); // TODO make loop checking valid guesses
        
        // submit valid guess to game
        // print number of bulls and cows
        PrintBack(guess);
        std::cout << std::endl;
    }
    
    // add game summary
    return;
}
    
std::string GetGuess(){
    // get a guess from the player
    std::string Guess = "";
    int CurrentTry = BCGame.GetCurrentTry();
    std::cout << "Try " << CurrentTry << ", Enter your guess: " << std::flush;
    std::getline(std::cin, Guess);
    return Guess;
}

void PrintBack(std::string Guess){
    // repeat the guess back to them
    std::cout << "Your guess was: " << Guess << std::endl;
    return;
}

bool AskToPlayAgain(){
    std::cout << "Do you want to play again? (y/n)";
    std::string Response = "";
    std::getline(std::cin, Response);
    
    return (Response[0] == 'y') || (Response [0] == 'Y');
}

