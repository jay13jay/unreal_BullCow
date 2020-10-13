// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay(){ // When the game starts
    Super::BeginPlay();
    SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input){ // When the player hits enter
    ClearScreen();
    if(DEBUG == true){
        DebugMsg();
    }
    
    // Checking PlayerGuess
    if(bGameOver){
        PrintLine(TEXT("Press Enter to play again"));
        EndGame();
        return;
    }
    else{
        ClearScreen();
        ProcessGuess(Input);
        return;
    }
}

void UBullCowCartridge::SetupGame(){
    DEBUG = false;
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;
    WelcomeMsg();

    int32 i = 0;
    while (i < 5) {
        PrintLine(TEXT("While Counter: %i"), i);
        i++;
    }

    for (int32 x = 0; x < 5; x++){
        PrintLine(TEXT("For Counter: %i"), x);
    }
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
        PrintLine(TEXT("Press enter to continue"));
        bGameOver = true;
        return;
    }

    // Check If Isogram
    if(!IsIsogram(Guess)){
        PrintLine(TEXT("Word is NOT an isogram, Try Again!"));
        return;
    }
    
    // Check Right Number Of Characters
    if (Guess.Len() != HiddenWord.Len()){
        PrintLine(TEXT("The hidden word is %i characters long, try again!"), HiddenWord.Len());
        return;
    }

    // Remove Life
    if (Guess.Len() == HiddenWord.Len()){
        PrintLine(TEXT("Wrong word, but guess was correct length"));

        // Check If Lives > 0    
        if(Lives > 0){
            DeductLife();
            return;
        }
        else{
            PrintLine(TEXT("You have lost!"));
            PrintLine(TEXT("Hidden Word was: %s"), *HiddenWord);
            PrintLine(TEXT("Press enter to play again!"));
            bGameOver = true;
            return;
        }
    }
}

void UBullCowCartridge::DebugMsg(){
    PrintLine(TEXT("The hidden word is: %s."), *HiddenWord);// Debug Line
}

void UBullCowCartridge::DeductLife(){
    --Lives;
    PrintLine(TEXT("Life lost! # left: %i"), Lives);
}

void UBullCowCartridge::EndGame(){
    PrintLine(TEXT("Resetting game"));
    ClearScreen();
    SetupGame();
    return;
}

bool UBullCowCartridge::IsIsogram(FString Guess) const{
    // TIP: we do not need to check for 0/1 letter words, since the code below works anyway
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