/*
Name: Omar Masri
Date: 4/16/24
Project 1: Strands

Code Description: Strand.c header file with the strand struct and function prototypes. I added some members to the
strand struct to check for certain conditions (such as correct words or the words guessed)

I also added helper functions to search the grid, filter the dictionary, populate the words array, and check all adjacent
cells as well as previous cells.

All prototypes I no longer need are at the bottom.

I spent a total of 100 hours on this project lol

*/

#ifndef STRAND_H
#define STRAND_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // added to be able to use malloc and free
#include <string.h> // added to be able to do string functions (strcpy for example)

// REQUIRED STRUCT - DO NOT REMOVE STRUCT MEMBERS
typedef struct strand
{
    char** words;
    char ** words_guessed; // ADDED: To check if the word has already been guessed and add to array
    //char ** dictionary; // added (UPDATE: No longer need)
    char** letters;
    int rows, cols;
    int numWords;
    int wordLen;
    int correct_word_counter; // ADDED: To count the number of correct words

} strand_t;

// REQUIRED FUNCTIONS

// Basically returns the pointer variable and populates the struct members based on the inputted files
// Also allocates memory as needed for the struct member variables
strand_t * create_strand(FILE * dataFP, FILE * dictFP); // creates the strand pointer variable and returns it. reads the data and dict files to get inputted row, column, and wordLen info

// checks if the word is valid by checking the helper boolean function (search_correct_words_updated) below
bool is_word_in_strand(strand_t * strand, char * word);

// Prints the grid based on row and column size as well as letters from the file
void print_strand_matrix(strand_t * strand);

// frees all memory allocated for struct members (as well as helper arrays we created)
// also free memory for the dict and data files by closing them
void free_strand(strand_t * strand);


// Helper function to allocate memory for the 2d array of letters based on rows and cols size
char ** letters_array(int rows, int columns);


// helper function to create the words from the grid while checking it to the dictionary file
// populates word struct member
void words_dictionary(strand_t * strands, FILE * dictFP);


// helper function to find the words of inputting length
// calls the recursive function we created with the index of 0 so that the recursive function can keep iterating until it matches word_length
void search_correct_words_index_0(strand_t * strands);


// helper function to find the i-letter words that are both lowercase and alphabetic from the dictionary file
// searches the grid and populates the words based on the letters in the adjacent cells
// use boolean matrix logic to ensure if a cell is adjacent and marked, and you can go back to original cells after going to adjacent cell
bool search_correct_words_updated(strand_t *strand, int row, int col, char *word, int index, bool ** marked_cell);




//bool word_from_file(char * word, char ** letters, int rows, int columns, int curr_row, int curr_col, int index); (UPDATE: NO LONGER NEEDED)

//bool word_former(char * word, char ** letters, int rows, int columns); (UPDATE: NO LONGER NEEDED)

//bool search_correct_words(strand_t * strands, int row, int column, char * word, int length_word, bool ** visited_cell); (UPDATE: NO LONGER NEEDED)

#endif
