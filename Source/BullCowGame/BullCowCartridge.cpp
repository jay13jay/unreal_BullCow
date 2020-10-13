// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay(){ // When the game starts

    Super::BeginPlay();
    SetupGame();

}

void UBullCowCartridge::OnInput(const FString& Input){ // When the player hits enter
    ClearScreen();
    
    // Checking PlayerGuess
    if(bGameOver){
        PrintLine(TEXT("Press Enter to play again"));
        EndGame();
    }
    else{
        ProcessGuess(Input);
        if (Input == HiddenWord){
            PrintLine(TEXT("You have won!"));
            EndGame();
        }
        else if (Input.Len() != HiddenWord.Len()){
            PrintLine(TEXT("The hidden word is %i characters long, try again!"), HiddenWord.Len());
        }
        else if (Input.Len() == HiddenWord.Len()){
            PrintLine(TEXT("Wrong word, but guess was correct length"));

            if(Lives > 0){
                DeductLife();
            }
            else{
                PrintLine(TEXT("You have lost!"));
                EndGame();
            }
        }
        PrintLine(TEXT("Lives remaining: %i"), Lives);
    }

    if(DEBUG == true){
        DebugMsg();
    }

    
    // Check If Isogram
    // Prompt To Guess Again
    // Check Right Number Of Characters
    // Prompt To Guess Again

    // Remove Life

    // Check If Lives > 0
    // If Yes GuessAgain
    // Show Lives Left
    // If No Show GameOver and HiddenWord?
    // Prompt To Play Again, Press Enter To Play Again?
    // Check User Input
    // PlayAgain Or Quit
}

void UBullCowCartridge::SetupGame(){
    DEBUG = false;
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;
    WelcomeMsg();
}

void UBullCowCartridge::WelcomeMsg(){
    // Welcoming The Player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives to guess"), Lives);
    PrintLine(TEXT("Type in your guess and press enter"));

    // Prompt Player For Guess
}

void UBullCowCartridge::ProcessGuess(FString Guess){
    // Process a player guess
}

void UBullCowCartridge::DebugMsg(){
    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);// Debug Line
}

void UBullCowCartridge::DeductLife(){
    --Lives;
    PrintLine(TEXT("Life lost."));
}

void UBullCowCartridge::EndGame(){
    PrintLine(TEXT("Resetting game"));
    SetupGame();
}