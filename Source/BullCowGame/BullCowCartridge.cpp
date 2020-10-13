// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay(){ // When the game starts
    Super::BeginPlay();

    // Load wordlist from directory
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

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
    DEBUG = true;
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;
    WelcomeMsg();
    PrintLine(TEXT("There are %i words in the list"), Words.Num());
    PrintLine(TEXT("Wordlist: "), Words.Num());
    for(int32 Index = 0; Index < Words.Num(); Index++) {
        PrintLine(TEXT("\t %s"), *Words[Index]);
    }

    // PrintLine(TEXT("Length of wordlist: %i"), Words.Num());
    // PrintLine(Words[0]);

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
        return;
    }
    // if(!IsIsogram2(Guess)){
    //     return;
    // }
    
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

bool UBullCowCartridge::IsIsogram(FString Word) const{
    // TIP: we do not need to check for 0/1 letter words, since the code below works anyway
    std::bitset<256> SeenLetters;
    static_assert(sizeof(std::bitset<256>) == 32, "");

    for (auto Letter : Word)
    {
        char LowercaseLetter = tolower(Letter);
        if (SeenLetters[LowercaseLetter]) { // if seeen letters contains current letter
            PrintLine(TEXT("Letter Match Found! NOT an Isogram"));
            return false; // its not an isogram
        }

        // otherwise add current letter to seen letters
        // TIP: we do not need else here, since return exits the function as well as the for loop
        SeenLetters[LowercaseLetter] = true;
    }
    PrintLine(TEXT("All letters checked, word IS an isogram"));
    return true; // no letters seen twice
}

bool UBullCowCartridge::IsIsogram2(FString Word) const{
    // check isogram
    for(int32 Index = 0; Index < Word.Len(); Index++){
        for (int32 Check = Index+1; Check < Word.Len(); Check++){
            if(Word[Index] == Word[Check]){
                PrintLine(TEXT("Checking Letter %i against %i"), Index, Check);
                PrintLine(TEXT("Letter Match Found! NOT an Isogram"));
                return false;
            }
        }
    }
    PrintLine(TEXT("All letters checked, word IS an isogram"));
    return true;
}