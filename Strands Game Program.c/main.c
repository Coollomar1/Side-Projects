/*
Name: Omar Masri
Date: 4/16/24
Project 1: Strands

Code Description: main.c file. Checks to ensure data and dictionary files can be opened. Then creates a strand variable
so that we can allocate memory and populate the struct variables.

This file also prints the instructions, the grid, and lets the user play the game.

It then frees the memory allocated for all the variables.

*/

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "strand.h"

int main(int argc, char** argv) {
    // Open strand data file
    FILE * dataFP = open_data_file(argc, argv);
    if (dataFP == NULL) {
        printf("Failed to open data file\n"); // for debugging
        return 0;
    }

    // Open dictionary file
    FILE * dictFP = open_dict_file(argc, argv);
    if (dictFP == NULL) {
        printf("Failed to open dict file\n"); // debugging
        return 0;  
    }

    // Create strand struct: allocate memory & populate accordingly
    strand_t * strand = create_strand(dataFP, dictFP);
    if (strand == NULL) return 0;

    // Print strand & game instructions
    print_strand_matrix(strand);
    print_instructions(strand);

    // Play the game
    play_game(strand);

    // Free all strand memory
    free_strand(strand);

    // close the file pointers and free memory for them
    //free_fptrs(dataFP, dictFP); (no longer needed)

    return 0;
}
