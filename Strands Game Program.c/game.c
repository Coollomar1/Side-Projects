/*
Name: Omar Masri
Date: 4/16/24
Project 1: Strands

Code Description: Game.c file. This file opens the data file inputted by the user, and searches for a dict file to open.
If the user inputs a dict file, then an alternative dictionary is used to populate the struct. If not, then the default dictionary is opened.

The play_game function ensures that the user can play the game while only guessing correct words once. User has unlimited
attempts to guess words, and if he guesses all of them, then the game ends. User can quit at any time. Number of correct
words is updated to ensure that user guesses are saved.

*/

#include "game.h"

// REQUIRED
FILE * open_data_file(int argc, char** argv) {

    // File pointer variable to open the data file
    FILE * file;

    // Open the file if the file name is provided in the argv[1] command line
    // Use if else statement to determine if file name is provided
    // If there are more than 1 arguments provided, open the file in argv1
    if (argc > 1 && argv[1] != NULL) { //check

        // Open file if true
        file = fopen(argv[1], "r");
    }
    else {
        
        // If file name isn't in argv[1], prompt user for filename
        char file_name_input[50];

        printf("Provide strand data filename: ");
        scanf("%s", file_name_input);

        // Return the file pointer after prompting user for strand file name
        file = fopen(file_name_input, "r");
    }

    // Return the file pointer
    return file;
}

// REQUIRED
FILE * open_dict_file(int argc, char** argv) {

    // Create file pointer variable
    FILE * fptr;

    // If dictionary file name is provided in argv[2], return file pointer
    // If not, default to open file defined by DICT_PATH
    // If there are more than 2 arguments in the command line, and the 3rd argument isn't null (dict file provided), open the file inputted by user
    if (argc > 2 && argv[2] != NULL) {

        // Open the file if true
        fptr = fopen(argv[2], "r");
    }
    else {
        
        // If there are 2 arguments only provided (dict file not provided), default to opening the file defined
        fptr = fopen(DICT_PATH, "r");
    }
    
    // Return the file pointer
    return fptr;
}

// REQUIRED - DO NOT EDIT
void print_instructions(strand_t * strand) {
    printf("\n  +-- Welcome to Strands! --+\n");
    printf("\nInstructions:\n");
    printf("\tFind all %d %d-letter words\n", strand->numWords, strand->wordLen);
    printf("\tEach word's letters must touch\n");
    printf("\tA letter can be repeated in a word\n");
    printf("\tType a word then press 'Enter'\n");
    printf("\tType 'quit' when done\n");
}

// REQUIRED
void play_game(strand_t * strand) {

    // allocate memory for words_guessed array based on the number of words we populate to the words array
    strand->words_guessed = (char**) malloc(strand->numWords * sizeof(char *));

    // iterate through the number of words
    for (int i = 0; i < strand->numWords; ++i) {

        // allocate memory for the words_guessed array at each index based on the word length
        strand->words_guessed[i] = (char*) malloc((strand->wordLen + 1) * sizeof(char)); // + 1 for null character

    }

    // Input word string for user to guess
    char input_word[50];
    
    // Begin game after populating the strand struct
    // Do while loop to keep playing the game until the user quits
    do {

        // Prompt user to take a turn and take input
        printf("Guess a word or 'quit':\n");
        scanf("%s", input_word);

        // if the user quits, exit loop before printing the error message
        if (strcmp(input_word, "quit") == 0) {

            break; // exit loop

        }

        // Boolean to check if the word has already been guessed
        // Initalize to false so if the word is guessed, we change to true
        bool already_guessed = false;

        // iterate through the correct_words
        for (int i = 0; i < strand->correct_word_counter; ++i) {

            // if the guessed word at each searched index matches the inputted word (if user guesses same word twice), set boolean to true
            if (strcmp(strand->words_guessed[i], input_word) == 0) {

                already_guessed = true;

                // Output the message to notify user
                printf("You have already guessed %s!\n", input_word);

                break; // exit loop
                
            }
        }

        // if the boolean returned is true, that means the word is already guessed. Keep continuing the loop if that is the case
        // This fixed my issues before of not continuing to prompt the user
        if (already_guessed) {
            
            // Update how many correct words the user has found
            printf("You have found %d of %d %d-letter words in the strand so far.\n\n", strand->correct_word_counter, strand->numWords, strand->wordLen);

            continue; // go back to beginning of loop

        }


        // Boolean variable to determine if the word inputted is found in the strand by setting it equal to the result of the is_word_in_strand function
        bool word_in_strand = is_word_in_strand(strand, input_word);

        // If the word is found in the strand, the boolean function returns true and the counter increases for correct words
        // ensure that the word is also the valid number of letters (to pass test case 6.2)
        if (word_in_strand && (strlen(input_word) == strand->wordLen)) {

            // Print success message
            printf("%s is a valid word in the strand!\n", input_word);
            
            // add the guessed word to the words_guessed array (with the index being each correct word)
            strcpy(strand->words_guessed[strand->correct_word_counter], input_word);
            
            // Increment the correct word counter
            strand->correct_word_counter++;

        }

        // If the word isn't found in the strand, boolean is set to false
        else {

            // Print incorrect message
            printf("%s is not a valid word in the strand.\n", input_word);
        }

        // if the user finds all of the words, exit the loop
        if (strand->correct_word_counter == strand->numWords) {

            break; // exit loop (congratulations message will be printed below)
        }

        // Update how many correct words the user has found
        printf("You have found %d of %d %d-letter words in the strand so far.\n\n", strand->correct_word_counter, strand->numWords, strand->wordLen);

    } while ((strcmp(input_word, "quit")) != 0); // Keep iterating through the loop while the user doesn't quit or until he guesses all words

    // If the user quits, output how many words they found with a thank you message
    if (strcmp(input_word, "quit") == 0) {
        printf("You found %d out of %d %d-letter words.\n", strand->correct_word_counter, strand->numWords, strand->wordLen);
        printf("Thanks for playing!\n");
    }

    // if the user guessed all the words, congratulate them for winning
    if (strand->correct_word_counter == strand->numWords) {

        printf("You found all %d %d-letter words!\n", strand->numWords, strand->wordLen);
        
        //printf("Thanks for playing!\n"); (I don't think this matches test cases)

        printf("Great job! Thanks for playing!\n"); // this matches test case. game ends after this

    }

    // free allocated memory for words_guessed array at each index
    for (int i = 0; i < strand->numWords; ++i) {
        free(strand->words_guessed[i]);
    }

    // free entire array
    free(strand->words_guessed);


}




// NO LONGER NEEDED
// function to free the file pointers (will call in main)
/*void free_fptrs(FILE * file, FILE * fptr) {

    // free the data file pointer
    // close the file after finishing program
    if (file != NULL) { // check if open

        fclose(file);

    }

    // free the dict file pointer
    // close file after finishing program
    if (fptr != NULL) { // check if open
        
        fclose(fptr);

    }
} */ // (NO LONGER NEEDED)
