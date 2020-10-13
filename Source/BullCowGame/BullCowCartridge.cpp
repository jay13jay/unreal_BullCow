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
        PrintLine(TEXT("Lives remaining: %i"), Lives);
    }

    if(DEBUG == true){
        DebugMsg();
    }
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
    if (Guess == HiddenWord){
        PrintLine(TEXT("You have won!"));
        EndGame();
    }

    // Check If Isogram
    if(IsIsogram(Guess)){
        PrintLine(TEXT("Word is an isogram"));
        return;
    }
    else{
        PrintLine(TEXT("NOT an isogram"));
        return;
    }
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

    if (Guess.Len() != HiddenWord.Len()){
        PrintLine(TEXT("The hidden word is %i characters long, try again!"), HiddenWord.Len());
        return;
    }
    
    if (Guess.Len() == HiddenWord.Len()){
        PrintLine(TEXT("Wrong word, but guess was correct length"));
        
        if(Lives > 0){
            DeductLife();
            return;
        }
        else{
            PrintLine(TEXT("You have lost!"));
            EndGame();
            return;
        }
    }
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

bool UBullCowCartridge::IsIsogram(FString Guess){
    // TIP: we do not need to check for 0/1 letter words, since the code below works anyway
    // less code = less things to worry about :)
    std::bitset<256> SeenLetters;
    static_assert(sizeof(std::bitset<256>) == 32, "");

    for (auto Letter : Guess)
    {
        char LowercaseLetter = tolower(Letter);
        if (SeenLetters[LowercaseLetter]) { // if seeen letters contains current letter
            return false; // its not an isogram
        }

        // otherwise add current letter to seen letters
        // TIP: we do not need else here, since return exits the function as well as the for loop
        SeenLetters[LowercaseLetter] = true;
    }

    return true; // no letters seen twice
}