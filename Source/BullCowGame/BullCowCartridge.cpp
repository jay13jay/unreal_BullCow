// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    InitGame(); // set the game up
    Super::BeginPlay();
    WelcomeMsg();

    if(DEBUG == 1){
        DebugMsg();
    }
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    // check if entered word matches HiddenWord
    if (Input == HiddenWord){ // print winning message
        PrintLine(FString::Printf(TEXT("Hidden Word was: %s"), *HiddenWord));
        PrintLine(TEXT("Answer is correct! YOU WON!"));

        // reset the game

        // prompt for restart the game, or exit
    }
    else {
        // check if number of letters matches
        if (HiddenWord.Len() == Input.Len()){
            PrintLine(TEXT("Word Length Matches, But Word Incorrect!"));
            PrintLine(TEXT("Choose another word with the same length"));
        }
        else {
            PrintLine(TEXT("Word length incorrect"));
        }

        // print a fail message, and user input 
        PrintLine(TEXT("Incorrect Answer"));
        PrintLine(TEXT("Word entered: %s"), *Input);

        // deduct a life

    }
    
    PrintLine(TEXT("Please input another command"));

    if(DEBUG == 1){
        DebugMsg();
    }
}

void UBullCowCartridge::InitGame() {
    DEBUG = 1;
    HiddenWord = TEXT("bravo"); // set the winning word
    Lives = HiddenWord.Len(); // set the number of guesses so far
}

void UBullCowCartridge::WelcomeMsg(){
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    PrintLine(TEXT("Word is a %i letter isometric"), HiddenWord.Len());
    PrintLine(TEXT("Please enter a word, and press Enter"));
}

void UBullCowCartridge::DebugMsg(){
    PrintLine("*** DEBUG ***");
    
    // Place all debug messages here
    PrintLine(TEXT("Hidden word is: %s"), *HiddenWord);
    PrintLine(TEXT("Lives remaining: %i"), Lives);
    // End Debug messages

    PrintLine("*** END DEBUG ***");

}