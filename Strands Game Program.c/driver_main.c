/*
Name: Omar Masri
Date: 4/16/24
CPSC 1070 AND 1071
Project 1: Strands

Code Description: driver_main.c file to test various cases. Ensures that this code runs efficiently and has no bugs

Required to pass autograder tests

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "strand.h"


// STRAND: print out known elements for Test Suite 4
void print_strand_known(strand_t * strand) {
    printf("Strand struct values:\n");
    printf("\tRow: \t\t%d\n", strand->rows);
    printf("\tCol: \t\t%d\n", strand->cols);
    printf("\tWordLen: \t%d\n", strand->wordLen);
    printf("\tLetters: \t");
    for (int i = 0; i < (strand->rows); i++) {
        for (int j = 0; j < (strand->cols); j++) {
            printf("%c ", strand->letters[i][j]);
        }
    }
}

int main(int argc, char** argv) {
    int test;
    //printf("Which test case are you running?");
    scanf("%d", &test);

    // Open strand data file
    FILE * dataFP = open_data_file(argc, argv);
    if (dataFP == NULL) {
        printf("Error opening strand data file with FILE * open_data_file(int argc, char** argv);");
        return 0;
    }

    // ----- Tests 2.1 & 2.2 -----
    if (test == 21 || test == 22) {
        return 0;
    }

    // Open dictionary file
    FILE * dictFP = open_dict_file(argc, argv);
    if (dictFP == NULL) {
        printf("Error opening dictionary data file with FILE * open_dict_file(int argc, char** argv);");
        return 0;
    }

    // ---- Test 2.3 ----
    if (test == 23) {
        return 0;
    }

    // ---- Test 2.4 ----
    if (test == 24) {
        char word[50];
        fscanf(dictFP, "%s", word);
        if (strcmp(word, "test") == 0) printf("true");
        else printf("false");

        return 0;
    }

    // Create strand struct: allocate memory & populate accordingly
    strand_t * strand = create_strand(dataFP, dictFP);
    if (strand == NULL) {
        printf("Error creating strand struct with strand_t * create_strand(FILE * dataFP, FILE * dictFP);");
        return 0;
    }

    // ----- Test Suite 3 -----
    if (test == 31) {
        print_instructions(strand);
        return 0;
    } else if (test == 32) {
        print_strand_matrix(strand);
        return 0;
    }

    // ----- Test Suite 4 -----
    if (test == 4) {
        print_strand_known(strand);
        return 0;
    } 
    
    // ----- Test Suite 5 -----
    if (test == 51) {
        printf("%d\n", strand->numWords);
        for (int i = 0; i < strand->numWords; i++) {
            printf("%s\n", strand->words[i]);
        }
        return 0;
    } else if (test == 52) {
        char test_word[strand->wordLen];
        scanf("%s", test_word);
        if (is_word_in_strand(strand, test_word)) {
            printf("true");
        } else {
            printf("false");
        }
        return 0;
    }

    // ----- Test Suite 6 -----
    if (test == 6) {
        print_strand_matrix(strand);
        print_instructions(strand);
        play_game(strand);
        return 0;
    }

    if (test == 7) {
        free_strand(strand);
        return 0;
    }

    if (test == 8) {
        return 0;
    }

    return 0;
}