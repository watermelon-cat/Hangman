#include <iostream> // libary for input output, used for things like cin and coiut
#include <string> //library that allows us to use and manipulate strings
#include <cstdlib>// librar for general purpose functions, used for randomizing
#include <ctime> // library for handling time functions, used for randomizing 
#include <algorithm> // library for a variety of functions; here we use it to search arrays
#include<Windows.h>
using namespace std; // this line lets us use standard library objects without a prefix

//global constants and variables
const int MAX_INCORRECT = 6; // maximum wrong guessses allowed
char incorrect[MAX_INCORRECT]; // array to hold incorrect guesses
int numIncorrect = 0; // counter for the number of incorrect guesses made
int misses = 0; // counter for the number of misses

// function decleration
void displayHangman();
void display(string guessedWord);
string processGuess(char guess, string word, string guessedWord);

int main() {
    string wordList[] = { "ivy", "obscure", "programming", "biking", "jazz", "passion", "jinx", "fuzzy" }; // list of words to guess
    srand(time(0)); // seed the random number generator
    string word = wordList[rand() % 8]; // randomly pick a word from the list
    string guessedWord(word.length(), '_'); // create a guessed word filled with underscores
    system("color 30");
    cout << "Welcome to Hangman!\n"; // welcome message

    // game loop runs untill the player runs out of guesses or guesses the word
    while (misses < MAX_INCORRECT && guessedWord != word) {
        display(guessedWord); //display the current state of the game
        cout << "Enter your guess: ";
        char guess;
        cin >> guess; // get the players guess

        string oldGuessedWord = guessedWord; // keep track of the word before the guess
        guessedWord = processGuess(guess, word, guessedWord); // process the guess

        if (guessedWord == oldGuessedWord) {
            cout << "Oops! That letter isn't in there!\n"; // inform the player the guess was wrong
        }
        else {
            cout << "Good guess!\n"; // congradulate the player on a correct guess
        }
    }// end of game loop
    // check if the game ended with a win or loss
    if (guessedWord == word) {
        system("color 67");
        cout << "Congradulations! You guessed the word: " << word << "\n"; // win message
    }
    else {
        cout << "Game Over! The word was: " << word << "\n"; //lose message 
    }

    return 0; // end the program
}// end of main

//function to display the handman drawing based on how many times the player has guessed wrong
void displayHangman() {
    cout << "\n"; //print a newline for spaceing 
    switch (misses) { // check the number of misses and show th appropriate handman stage
    case 0:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "========\n";
        break;
    case 1:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "========\n";
        break;
    case 2:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << "  |   |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "========\n";
        break;
    case 3:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << "  |\\  |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "========\n";
        break;
    case 4:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << " /|\\  |\n";
        cout << "      |\n";
        cout << "      |\n";
        cout << "========\n";
        break;
    case 5:
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << " /|\\  |\n";
        cout << "   \\  |\n";
        cout << "      |\n";
        cout << "========\n";
        break;
    case 6:
        system("color 47");
        cout << "  +---+\n";
        cout << "  |   |\n";
        cout << "  O   |\n";
        cout << " /|\\  |\n";
        cout << " / \\  |\n";
        cout << "      |\n";
        cout << "========\n";
        break;
    }
}
//function to display the current state of the game
void display(string guessedWord) {
    cout << "\n Word: ";
    for (int i = 0; i < guessedWord.length(); i++) {
        cout << guessedWord[i] << ' '; // show each character in the guessed word followed by a space
    }
    cout << "\n Incorrect guesses: ";
    for (int i = 0; i < numIncorrect; i++) {
        cout << incorrect[i] << ' '; // show each incorrect guess followed by a space
    }
    cout << "\n Misses left: " << MAX_INCORRECT - misses << "\n"; // show how many guessses are left
    displayHangman(); // call function to show the handman drawing
}

//function to check the player's guess agaisnt the word 
string processGuess(char guess, string word, string guessedWord) {
    bool isCorrect = false;
    for (int i = 0; i < word.length(); i++) { // loop through each letter in the word
        if (word[i] == guess && guessedWord[i] == '_') { // if guess is correct and hasn't been guessed before
            guessedWord[i] = guess; // update the guessed word with the new letter
            isCorrect = true; // Mark the guess as correct
        }
    }
    //check if the guess was incorrect
    if (!isCorrect) {
        //initializes a variable to indicate if the guess is found in the incorrect guesses
        bool alreadyGuessed = false;

        //iterate through the incorect guesses to see if the guess was already made
        for (int i = 0; i < numIncorrect; i++) {
            if (incorrect[i] == guess) {
                alreadyGuessed = true;
                break; // break the loop if the guess is found
            }
        }

        // if the guess was not found in the incorrect guesses
        if (!alreadyGuessed) {
            incorrect[numIncorrect++] = guess; // add the new incorrect guess
            misses++; // add to the misses counter
        }
    }
    return guessedWord; // return the updated guessed word
}
