/*
Name: Omar Masri
Date: 4/16/24
CPSC 1070 AND 1071
Project 1: Strands

Code Description: Game.c header file. Has all the function prototypes for game.c.

Also has the default dictionary DICT_PATH if a user doesn't input a 3rd argument in the command line 
(which would be an alternative dict file)

*/

#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "strand.h"

// Default dictionary to use
#define DICT_PATH "/usr/share/dict/american-english"

// REQUIRED FUNCTIONS

// Open the file if the file name is provided in the argv[1] command line.
// If there are more than 1 arguments provided, open the file in argv1
// If file name isn't in argv[1], prompt user for filename
// Return the file pointer that points to the inputted file
FILE * open_data_file(int argc, char** argv);


// If dictionary file name is provided in argv[2], return file pointer
// If not, default to open file defined by DICT_PATH
// If there are more than 2 arguments in the command line, and the 3rd argument isn't null (dict file provided), open the file inputted by user
FILE * open_dict_file(int argc, char** argv);

// prints game instructions including the populated numWords variable from the struct and the amount of letters
// in each word. This will be done by reading the file in the strand.c file, and populating the struct members
// appropriately
void print_instructions(strand_t * strand);

// Runs the game. Ensures that user inputs valid words, and doesn't allow for word repeating
// If user inputs quit, game terminates
// If user gets all words, game ends
void play_game(strand_t * strand);


// function to free the file pointers by closing them (will call in main)
//void free_fptrs(FILE * file, FILE * fptr); (no longer needed)


#endif