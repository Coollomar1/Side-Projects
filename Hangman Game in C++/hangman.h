/* 
Name: Omar Masri
Date: 3/10/2024
CPSC 1070
Lab 04 Part C

Code Description:
Header file that imports all of the function prototypes and libraries used in the C++ main file.
*/

#ifndef HANGMAN_H // Header guards
#define HANGMAN_H

#include <iostream>
#include <fstream> // For dealing with files
#include <string> // For use of strings and string manipulation
#include <ctime> // Time function necessary when using the rand function
#include <cstdlib> // Allows for use of the rand function
#include <algorithm> // For the use of the find function

using namespace std; // This is so that every function declaration is defined with std:: (I kept getting string does not name type error)

/* Reads the american-english file from the SOC servers, creates a new array of words with ONLY lowercase characters and
alphabetic characters, and updates the length of the dictionary to the new array we allocated memory for so that the words are limited
to lowercase-alphabetic words */
string* readDictionary(int &len);


/* Uses imported random function from cstdlib and sets it to time from ctime library 
to randomly pick word from array we created and assign that word to be the correct answer that the user is trying to guess */
// The random variable chooses a random word from the updated length of the dictionary (new array we created)
string generateAnswer(string * dictionary, int len);

// Called in main to run the game
// Calls all functions as necessary to run game (using variety of loops and switch statements)
// Prompts user at end to play again
void runGame(void);

// Displays ascii art of hangman to terminal
// Each incorrect guess is taken in and updates the hangman figure accordingly
void printGallows(int stage);

//Prompts the user for their character guess
// Ensures that guess is in lowercase, and prints error message until user inputs in lowercase
// Returns the letter the user guesses
char makeGuess(string * dictionary, int len, char type);

// Prompts the user for their next guess if they want to guess a word
// Makes sure that the word guessed is in the dictionary, and continues to prompt until user inputs acceptable word
// Returns the string the user guesses to the main game
string makeGuess(string * dictionary, int len);

// Boolean to check if the character guessed is correct or not
// Returns true or false depending on the answer
bool checkGuess(char guess, string answer);

// Boolean to check if the word guessed is correct or not
// Returns true or false depending on the answer
bool checkGuess(string guess, string answer);

// Prints known letters to the terminal
// If letter unknown, prints "_" before/after each unknown letter
// Beginning of game, prints all underscore characters (since user hasn't guessed yet)
// Empty string is passed after each game reset to reset the underscores
// Correct letters replace the "_" character
void printCorrectLetters(char guess, string answer, string knownLetters);



#endif
