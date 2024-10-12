/*
Name: Omar Masri
Date: 4/16/24
Project 1: Strands

Code Description: Strand.c file. Uses the prototypes included in the strand.h file. This is where we populate the struct
member variables, check if the word is valid by filtering the dictionary, and recursively search the grid to populate
the words array.

Created many helper functions to filter dictionary, search grid, and validate the words.

ALL OF THE FUNCTIONS I ATTEMPTED BUT NO LONGER WORK ARE AT THE BOTTOM OF THIS FILE (AFTER THE free_strand FUNCTION)
THERE ARE A LOT OF FAILED FUNCTIONS

I SPENT 100 HOURS ON THIS PROJECT!!!!

*/

#include "strand.h"
#include <ctype.h> // to use islower and isalpha functions

// REQUIRED
strand_t * create_strand(FILE * dataFP, FILE * dictFP) {
    

    // Allocate memory for the strand struct by creating pointer variable to the strand_t struct
    strand_t * strands = (strand_t*) malloc(sizeof(strand_t));
    
    //printf("Reading data file...\n"); (Debug print)
    
    // Read the dataFP file to read the desired row x column size
    fscanf(dataFP, "%d %d", &strands->rows, &strands->cols); // strands struct points to the rows, and columns provided from dataFP
    
    //printf("Rows: %d, Cols: %d\n", strands->rows, strands->cols); (Debug print)
    

    // Read the size of the words that the user want's to play with
    fscanf(dataFP, "%d", &strands->wordLen); // Strand struct points to word length from the struct to read from the dataFP file
    
    //printf("Word length: %d\n", strands->wordLen); (Debug print)

    
    // Allocate memory for words array based on the number of correct words as the size
    // Use struct pointer variable to point to the words member and numWords member in struct_t struct
    strands->words = (char**) malloc(strands->numWords * sizeof(char*));

    
    // Allocate memory for the letters array based on rows as the size
    // Call the helper function we created and point the strand struct variable to the rows and columns
    strands->letters = letters_array(strands->rows, strands->cols);


    // Next, read all the letters from the dataFP file to the row x column array
    // Iterate through the array based on rows, then columns
    for (int i = 0; i < strands->rows; ++i) {
        
        for (int j = 0; j < strands->cols; ++j) {
            
            fscanf(dataFP, " %c", &strands->letters[i][j]); // Reads each letter from the dataFP file and populates it to the letters array in the struct based on the i'th row then the j'th column (2D array fashion)

        }
    }

    //printf("Calling words_dictionary function...\n"); (Debug print)
    
    // Call the words_dictionary function to populate the word array based on the grid
    words_dictionary(strands, dictFP);
    
   // printf("Finished calling words_dictionary function.\n"); (Debug print)
    
    // Call search_correct_words_index_0 to pass the wordLength into the function, and then that function will call the recursive function
    // This function will dynamically search the grid to populate the array using recursion
    search_correct_words_index_0(strands);


    // close the dataFP file to free the memory for it
    fclose(dataFP);

    // close the dictFP file to free memory for it
    fclose(dictFP);

    // Return the pointer variable
    return strands;
}

// Helper function to allocate memory for the 2d array of letters based on rows and cols size
char ** letters_array(int rows, int columns) {

    // Create pointer variable for the array of rows based on row size and allocate memory
    char ** letters = (char**) malloc(rows * sizeof(char*));


    // Iterate through the newly allocated row array to allocate memory for columns array
    for (int i = 0; i < rows; ++i) {

        // Assign pointer variable at the i'th row to the allocated memory based on columns as the size
        letters[i] = (char*) malloc(columns * sizeof(char)); // allocates memory for each column based on the current row

    }

    // Return the new row by column array
    return letters;
}


// helper function to ensure that the word is lowercase and has no special characters
bool word_valid(char * word) {

    // iterate through the word list provided to ensure that word is lowercase
    for (int i = 0; word[i] != '\0'; ++i) { // do word[i] != \0 to keep going until a null character is read

        // if the word isn't lowercase, return false for the boolean, otherwise the word is valid
        if (!islower(word[i])) {
            return false;
        }
    }

    // iterate through word list to ensure that there are no special characters
    for (int i = 0; word[i] != '\0'; ++i) {

        // if the word isn't alphabetic, return false
        if (!isalpha(word[i])) {
            return false;
        }
    }


    // return true if the word is lowercase and alphabetic
    return true;
}

// helper function to show me which words are populated to the struct (since I was having a lot of trouble with this)
void printWords(strand_t * strands) {
    printf("Words stored in struct:\n");
    for (int i = 0; i < strands->numWords; i++) {
        printf("%s\n", strands->words[i]);
    }
}

// helper function to find the words of inputting length
// calls the recursive function we created with the index of 0 so that the recursive function can keep iterating until it matches word_length
void search_correct_words_index_0(strand_t * strands) {

    // allocate memory for the marked_cell parameter passed in the recursive function
    bool ** marked_cell= (bool**) malloc(strands->rows * sizeof(bool*));
    
    // iterate through the rows to allocate memory for each cell in the boolean
    for (int i = 0; i < strands->rows; ++i) {
        
        // allocate memory for each cell based on column size (since loop iterates through rows)
        marked_cell[i] = (bool*) malloc(strands->cols * sizeof(bool));

        // go through each column to initialize each element of the visited boolean to false
        for (int j = 0; j < strands->cols; ++j) {

            marked_cell[i][j] = false; // each cell at i'th row and j'th column will be false (recursive function will change this when finding the words)
        }
    }


    // iterate through each word in the strands->words array
    for (int i = 0; i < strands->numWords; ++i) {

        // set a word character variable to be the word at each index
        char * word = strands->words[i];

        // set a variable equal to the first letter of the word at each index in the strands->words array to ensure that the word we are searching for
        //will be the valid word from the dictionary (otherwise the dictionary array will just populate all i letter words, not simply the words from the grid) 
       char letter_one = word[0];

        // iterate over rows in the cells
        for (int i = 0; i < strands->rows; ++i) {

            // iterate over the columns in the cells
            for (int j = 0; j < strands->cols; ++j) {

                // if the letter at the i'th row and j'th column is equal to the first letter, then recursively call the function we created above
                if (strands->letters[i][j] == letter_one) {

                    // I was going to use Breadth First Search, but I opted for Depth First Search instead
                    // I used Depth First Search to use less memory and is more recursive since it starts at the selected node and explores out as far as possible without backtracking
                    // It only explores neighboring nodes if the cells have all been searched, and no results have been found (which is why it uses less memory)
                    // Since I already used up a lot of memory with this project, I thought this would be better to reduce runtime and prevent crashing
                    search_correct_words_updated(strands, i, j, word, 0, marked_cell); // set to 0 to start at beginning of word
                }
            }
        }
    }
    
    // free the memory for the marked cell array
    for (int i = 0; i < strands->rows; ++i) {

        free(marked_cell[i]); // free each index

    }
    // free the whole boolean array
    free(marked_cell);
}


// helper function to find the i-letter words that are both lowercase and alphabetic from the dictionary file
// searches the grid and populates the words based on the letters in the adjacent cells
// use boolean matrix logic to ensure if a cell is adjacent and marked, and you can go back to original cells after going to adjacent cell
bool search_correct_words_updated(strand_t *strands, int row, int column, char * word, int length_word, bool ** marked_cell) {
    
    // Base case: If the entire word at the given length has been found, return true
    if (word[length_word] == '\0') {
        
        return true; // exits recursive function

    }

    // Check if the current cell is inside the grid boundaries
    // row >= strands-> rows checks if the row is outside the bottom boundary of grid
    // row < 0 checks if row is outside top boundary of grid
    // column >= strands->cols checks if outside the right boundary of grid
    // column < 0 checks if outside left boundary of grid
    if (row >= strands-> rows || column >= strands->cols || row < 0 || column < 0) {
        
        return false; // exit function since out of bounds

    }

    // Check if the current cell does not match the next letter in the word
    if (strands->letters[row][column] != word[length_word]) { // retreives the character at the cell position (row, column) and checks if the word at the length_word index is the same
        
        return false; // exit function since this is not part of the word being searched for, and backtrack to search for other letters in a different word

    }

    // Mark the boolean to true to indicate the current cell has been visited
    marked_cell[row][column] = true;

    // Recursively search in all the neighboring cells
    // -1 is the cell above current cell, 0 is the current row, and 1 is the cell below (in the first loop for rows)
    // in the second loop for columns, -1 is the left cell, 0 is the current column, and 1 is the right cell
    // 8 possible directions
    // Up-Left: (-1, -1), Up: (-1, 0), Up-Right: (-1, 1), Left: (0, -1), Right: (0, 1), Down-Left: (1, -1), Down: (1, 0), Down-Right: (1, 1)
    for (int i = -1; i <= 1; i++) {

        for (int j = -1; j <= 1; j++) {

            // If the function is searching at the current cell, continue through the loop
            // This statement fixed my code because I would be searching the grid and it would choose the same letter twice from the same cell
            // By skipping the current cell, it only adds the letter once and searches the neighboring cell
            // For example, "tooth" would be populated to my struct but it would be from the same cell, so this statement allows the loop to only populate the letter once
            if (i == 0 && j == 0) {

                continue; // go back through the loop to increment i and j

            }

            // Recursive call to the function to keep searching the neighbor cells
            // add the indices to the row and column to determine the neighbor cells to explore
            // add 1 to the length_word parameter to move to the next letter in the word
            if (search_correct_words_updated(strands, row + i, column + j, word, length_word + 1, marked_cell)) {
                
                return true; // signifies that the word has been found

            }
        }
    }

    // Set the boolean to false to mark the current cell as not visited, which allows for backtracking to occur and the process to start over
    marked_cell[row][column] = false;

    // If the word is not found starting from this cell, return false
    return false;

    // free the memory for the marked cell array
    for (int i = 0; i < strands->rows; ++i) {

        free(marked_cell[i]); // free each index

    }
    // free the whole boolean array
    free(marked_cell);
}

// I DO NOT NEED THIS ANYMORE SINCE I FIXED THE SAME CELL LETTER SEARCH ISSUE!!!
// helper function to ensure that the letters in the word don't repeat (like the same cell is being searched twice. For example: tooth)
/*bool letters_repeat(char * word) {

    // iterate through the word list provided to ensure that word is not duplicating letters
    for (int i = 0; word[i] != '\0'; ++i) { // do word[i] != \0 to keep going until a null character is read

        // if the word is duplicating letters, return false
        if (word[i] == word[i + 1]) {
            return false;
        }
    }


    // return true if the word isn't duplicating letters
    return true;
} */


// helper function to create the words from the grid while checking it to the dictionary file
void words_dictionary(strand_t * strands, FILE * dictFP) {

    // printf("Reading dictionary file...\n"); (Debug print)


    // word array variable
    char word[50]; // assume 50 as max word length
    
    //printf("Allocating memory for words array...\n"); (Debug print)

    //printf("reading dict file...\n"); (debug)


    // initialize numwords to 0 to increment it in the loop
    strands->numWords = 0;


    // populate word array
    while (fscanf(dictFP, "%s", word) != EOF) { // read dictionary until end of file
        
        //printf("Read word from dictionary: %s\n", word); (debug)

        // check if word is lowercase and alphabetic by calling helper function
        // also make sure the word is the desired length
        // also check if letters duplicate and if the word is valid (is_word_in_strand)
        if (word_valid(word) && strlen(word) == strands->wordLen && is_word_in_strand(strands, word)) {
            // set boolean of valid word to true to check if word only contains letters available in letter list
            bool words_valid = true;

            // iterate through each word until null character (to go to next word)
            for (int i = 0; word[i] != '\0'; ++i) {

                // create a boolean to see if the letter is found and set it to false
                bool found_letter = false;

                // iterate through rows then columns
                for (int row = 0; row < strands->rows; ++row) {

                    for (int column = 0; column < strands->cols; ++column) {

                        // after iterating through each row and column, if the letters at the row and column equal the word, then the letters are found
                        if (strands->letters[row][column] == word[i]) {

                            // set boolean to true
                            found_letter = true;

                            break; // exit inner column loop since letters are found
                        }
                    }
                    // if the letters are found, exit outer row loop
                    if (found_letter) {

                        break;

                    }
                }

                // if the letters aren't found, set the valid word boolean to false
                if (!found_letter) {

                    words_valid = false;

                    break; // exit entire for loop
                }
            }

        // if the word is valid, add it to word array
        if (words_valid) {

            // reallocate memory for words member to update for each valid word
            strands->words = (char**) realloc(strands->words, (strands->numWords + 1) * sizeof(char*));
            
            // allocate memory for word array at the word_at_i index by passing the numWords as the parameter
            strands->words[strands->numWords] = (char*) malloc((strlen(word) + 1) * sizeof(char)); // add 1 for null character
            
            // copy the word into the newly allocated memory slot
            strcpy(strands->words[strands->numWords], word);

            // increment counter
            strands->numWords++;

            //printf("Valid word: %s\n", word); (Debug print. Helped me a lot to see what was being populated)
            
        }
    }
    }

    //printf("Finished populating dictionary array \n"); (Debug print)
    //printf("Number of words populated: %d\n", strands->numWords); (debug)
    
}

// REQUIRED
bool is_word_in_strand(strand_t * strand, char * word) {
    
    //printf("Entered word: %s\n", word); (THIS WAS TO DEBUG)

    // allocate memory for the marked_cell parameter passed in the recursive function
    bool ** marked_cell = (bool**) malloc(strand->rows * sizeof(bool*));
    
    // iterate through the rows to allocate memory for each cell in the boolean
    for (int i = 0; i < strand->rows; ++i) {
        
        // allocate memory for each cell based on column size (since loop iterates through rows)
        marked_cell[i] = (bool*) malloc(strand->cols * sizeof(bool));

        // go through each column to initialize each element of the visited boolean to false
        for (int j = 0; j < strand->cols; ++j) {

            marked_cell[i][j] = false; // each cell at i'th row and j'th column will be false (recursive function will change this when finding the words)
        }
    }

    // set a boolean to determine if the word is found (set to false)
    bool word_found = false;

    // iterate through the rows
    for (int i = 0; i < strand->rows; ++i) {

        // iterate through the columns
        for (int j = 0; j < strand->cols; ++j) {

            // check if the boolean recursive function is true
            if (search_correct_words_updated(strand, i, j, word, 0, marked_cell)) { // set the length_word index to 0

                // set boolean to true
                word_found = true;

                // exit loop
                break;
            }
        }

        // if the word is found, exit function
        if (word_found) {

            break;

        }
    }

    // free the memory for the marked cell array
    for (int i = 0; i < strand->rows; ++i) {

        free(marked_cell[i]); // free each index

    }
    // free the whole boolean array
    free(marked_cell);

    // return true if the word is found
    return word_found;
}

// REQUIRED
void print_strand_matrix(strand_t * strand) {

    printf("\n"); // newline at top
    
    printf("        "); // for spacing (8 spaces to format following sample gameplay case in the document)

    // if the rows are less than the columns, stop when last row is reached
    if (strand->rows < strand->cols) {

        // iterate through the rows to print the top barrier
        for (int i = 0; i < strand->cols; ++i) {

            // if a 7x9, for example, then stop at the 9'th column (to not print a 7x7 if we were iterating by rows)
            if (strand->cols == i) {

                    break; // exit at the column limit

                }

            printf("+---"); // For formatting barrier on top
        }
    }
    


    // if the columns are less than the rows, stop when last column is reached
    else if (strand->cols < strand->rows) {

        // iterate through the rows to print the top barrier
        for (int i = 0; i < strand->rows; ++i) {

            // if an 8x6, for example, then stop at the 6'th column (to not print an 8x8)
            if (strand->cols == i) {

                    break; // exit at the column limit

                }

            printf("+---"); // For formatting barrier on top
        }
    }

    // if rows and columns are equal, print normally
    else {

           // iterate through the rows to print the top barrier
        for (int i = 0; i < strand->rows; ++i) {

            printf("+---"); // For formatting barrier on top
        
        }
    }

    printf("+"); // at the last index, print the + character
    
    printf("\n"); // newline to print the remaining characters

    // Iterate through each row and print the letters stored in the strand struct
    for (int i = 0; i < strand->rows; ++i) {

        printf("        |"); // For formatting the barriers around the strand (8 spaces to format correctly)

        // Iterate through the column (since this is a 2D array)
        for (int j = 0; j < strand->cols; ++j) {
           
            // Print the letters in the 2D array from the struct
            printf(" %c |", strand->letters[i][j]);
        }

        // For formatting to the next line after finishing the i'th row
        printf("\n");

        printf("        "); // spacing again for each row (8 spaces)


        // if the rows are less than the columns, stop when last row is reached
        if (strand->rows < strand->cols) {

            // iterate through the columns to print the barriers under and above the letters
            for (int i = 0; i < strand->cols; ++i) {
                
                // if column limit is reached, exit the loop (so we don't print 8x8 when we desire an 8x6)
                if (strand->cols == i) {

                    break; // exit loop

                }
                
                printf("+---"); // For formatting in between letters on bottom and top

            }
        }
        


        // if the columns are less than the rows, stop when last column is reached
        else if (strand->cols < strand->rows) {

            // iterate through the rows to print the barriers under and above the letters
            for (int i = 0; i < strand->rows; ++i) {
                
                // if column limit is reached, exit the loop (so we don't print 8x8 when we desire an 8x6)
                if (strand->cols == i) {

                    break; // exit loop

                }
                
                printf("+---"); // For formatting in between letters on bottom and top

            }
        }

        // if rows and columns are equal, print normally
        else {

            // iterate through the rows to print the top and bottom barriers
            for (int i = 0; i < strand->rows; ++i) {

                printf("+---"); // For formatting barrier on top and bottom between letters
            
            }
        }

            // at last index, print the + character then insert newline to continue printing the characters
            printf("+\n");
    }
}

// REQUIRED
void free_strand(strand_t * strand) {
    
    // Free each letter at the i'th index based on the number of rows populated to the strand struct
    for (int i = 0; i < strand->rows; ++i) {
        free(strand->letters[i]);
    }

    // Free entire letters member in the struct
    free(strand->letters);
    

    // Free each word at the i'th index based on the number of words populated to the struct
    for (int i = 0; i < strand->numWords; ++i) {
        free(strand->words[i]); // free the word at the i'th index of numWords
    
    }

    // Free the entire words member in the struct
    free(strand->words);

    // Free the entire strand struct pointer variable
    free(strand);
    
}



// NO LONGER NEEDED! Tried to first use the _words.txt file as the way to determine the correct words, soon learned
// I had to recursively search the grid to generate words
// helper function to get the number of words that match the _words.txt file
// take in the row, column, word, word length, playing grid, max_word_len, and MAX_CELL_SIZE as parameters
/*void get_number_words(int row, int column, int word_len, char ** playing_grid, int input_rows, int input_columns, char ** words) { // set the 2D array row and column to the maximum cell size


    // base case, if the length of the word is equal to the 8 words in the 3x3, exit the function
    if (input_rows == 3 && input_columns == 3 && word_len == 8) {
        return;
    }
    // if equal to the 2x2, exit
    else if (input_rows == 2 && input_columns == 2 && word_len == 12) {
        return;
    }
    // if equal to the 8x6, exit
    else if (input_rows == 8 && input_columns == 6 && word_len == 192) {
        return;
    }
    // if equal to 5x5, return
    else if (input_rows == 5 && input_columns == 5 && word_len == 18) {
        return;
    }
    

  // iterate over all of the possible directions in the grid
    for (int i = -1; i <= 1; ++i) { // there are 8 possible directions (up down left right and 4 diagonal across), so set the maximum to be 8
        for (int j = -1; j <=1; ++j) {

            if (i == 0 && j == 0) {
                continue;
            }

            // These will dynamically examine all adjacent cells in the grid
            int new_row = row + i; // the new row will be equal to the original row + the row at the index

            int new_column = column + j; // same method used for the column

            // make sure the next cell being checked is inside the cell boundaries
            if (new_row >= 0 && new_column >= 0 && new_row < input_rows && new_column < input_columns) { // check if the new row and column are >= to 0 (to ensure they are inside the grid) and less than the maximum cell size so it doesn't go outside of the grid

                // Create temporary variable to store word being formed from the letters
                char * temporary_word = (char*) malloc((word_len + 1) * sizeof(char)); // add 1 for null character

                // set the temporary word variable to empty string
                strcpy(temporary_word, "");

                // Append each letter to the temporary word variable by using strcat (since we can't just directly concatenate the strings)
                // concatenate the playing grid at the position using new_row and new_column to the temporary word variable
                //strcat(temporary_word, &playing_grid[new_row][new_column]); // use & for pointer variable

                

                // allocate memory for the word in the words array at the word_at_i index
                words[word_at_i] = (char*) malloc((word_len + 1) * sizeof(char)); // add 1 to word len for null character

                // copy the temporary word contents to the words[word_at_i] array we just created memory for
                strcpy(words[word_at_i], temporary_word);

                // use recursion to call the function again in order to move to the next position in the grid
                get_number_words(new_row, new_column, word_len + 1, playing_grid, input_rows, input_columns, words); // add 1 to word_len to get the next character

                word_at_i++; // add 1 to the word index counter
            }


        }
    }
} */



// UPDATE: THIS FUNCTION IS NO LONGER NEEDED. This was my first attempt at the recursive search algorithm method
// This method wasn't as efficient as it didn't actually try to formulate words, and would only give me 5 letters of nonsense
// I didn't have a boolean in here to mark the cell as visited
// helper function to create the words based on ONLY THE LETTERS in the .txt file (this is so much harder)
/*bool word_from_file(char * word, char ** letters, int rows, int columns, int curr_row, int curr_col, int index) {

    // if the passed index is equal to the length of the word, then the word is valid in the file
    if (index == strlen(word)) {
        return true; // return true if the word is found
    }


    // check the boundaries of the grid
    // if current row/col is less than the index or greater than the passed parameter, return false since this is out of the limits of the grid
    if (curr_row < 0 || curr_row >= rows || curr_col < 0 || curr_col >= columns) {
        return false;
    }

    // check if current letter matches letter at the current index of the word
    if (letters[curr_row][curr_col] != word[index]) {
        return false;
    }

    // store the current cell into a temp variable and mark the cell with a # character to mark it as visited
    char temp_cell = letters[curr_row][curr_col];
    letters[curr_row][curr_col] = '#';

    // recursively call the function to check the grid in all directions (up down left right (horizontal, vertical, diagonally whichever direction it may be))
    // set equal to boolean variable
    // check each one at the right cell (row + 1), left cell (row - 1), up cell (col + 1), or down cell (col - 1)
    bool word_is_found = word_from_file(word, letters, rows, columns, curr_row + 1, curr_col, index + 1) ||
                        word_from_file(word, letters, rows, columns, curr_row - 1, curr_col, index + 1) ||
                        word_from_file(word, letters, rows, columns, curr_row, curr_col + 1, index + 1) ||
                        word_from_file(word, letters, rows, columns, curr_row, curr_col - 1, index + 1);
    
    // set the grid back to the temporary cell
    letters[curr_row][curr_col] = temp_cell;

    // return the boolean if the recursions are true
    return word_is_found;
} */


// UPDATE: NO LONGER NEEDED! This was my first attempt at the function that would call the recursive functions
// based on the number of rows and columns (keep iterating to get every word). I didn't use this function because
// I didn't have the boolean to mark visited cells
// helper function to formulate the word based on the letters in the .txt file
/*bool word_former(char * word, char ** letters, int rows, int columns) {

    printf("Forming word: %s\n", word); // debug

    // iterate through the rows
    for (int i = 0; i < rows; ++i) {

        // iterate through the columns
        for (int j = 0; j < columns; ++j) {

            // call helper function to check if the word is from the file
            if (word_from_file(word, letters, rows, columns, i, j, 0)) {

                // return true if word is from the file
                return true;
            }
        }
    }

    // return false if word isn't from file
    return false;
} */


   // UPDATE: THIS PORTION OF CODE IS NO LONGER USEFUL TO MY FUNCTION: is_word_in_strand
   // This was mainly to debug, and it also incorrectly incremented the counter in this funcion instead of the
   // words_dictionary function
    
    // For loop to iterate through the number of words stored in strand struct
    /*for (int i = 0; i < strand->numWords; ++i) {
         // Ensure that the word is not null
        if (strand->words[i] == NULL) {
            printf("Word at index %d is null!\n", i);
            continue;
        }

        printf("Comparing with: %s\n", strand->words[i]); // debugging

        // if the length of the word at the i'th index is equal to the word (basically if the word is the word), then continue
        if (strlen(strand->words[i]) == strlen(word)) {

            // Compare the i'th word to the word inputted from the user, and if it equals 0, then the strings are equal
            if (strcmp(strand->words[i], word) == 0) {

                // If the word is found in the strand, call the recursive function
                // If the boolean search_correct_words function returns true, then increment the word counter to adjust for found words
                if (search_correct_words(strand, 0, 0, word, 1, marked_cell)) { // start the row at 0, column at 0, and the word_length at 1 for the first letter
                
                    // Increment numWords counter to adjust for found word
                    strand->numWords++;

                    return true; // set the boolean to true
                }
            }
        }
    }

    printf("No match found for: %s\n", word); // debug
    return false; // if they aren't the same, set boolean to false
    UPDATE: NO LONGER NEEDED! */



    // UPDATE: THIS PORTION OF CODE IS NO LONGER NEEDED FOR MY FUNCTION (words_dictionary)
    // I was trying to count the dictionary words from the dict file from a helper function.
    // Not using this anymore because I realized we can't use 3x3_5_words.txt file.

    // call helper function to count number of valid words
    //int counter = count_dictionary_words(dictFP);
   //printf("Number of valid words in dictionary file: %d\n", counter); // Debug print
    
    // word counter variable
    //int num_words = 0;

    // allocate memory for words array by taking the length of the word including null character to make space in memory
    //strands->words = (char**) malloc((strlen(word) + 1) * sizeof(char*)); // + 1 for null character




// UPDATE: NO LONGER NEEDED. I was trying to populate the words array with this function, but incorrectly populated
// the words to only store lowercase and alphabetic words.
// When I ran it, almost 60,000+ words word populated, so I didn't need this function.

// helper function to counter number of words in dictionary file
 /*int count_dictionary_words(FILE * dictFP) {
    // counter variable
    int counter = 0;
    char words[50]; // word array to store words in

    // count words until the end of the file is reached
    while (fscanf(dictFP, "%s", words) != EOF) {

        // use helper function to only count lowercase and alphabetic words
        if (word_valid(words)) {

            // increase word counter
            counter++;
        }
    }

    // use fseek found on geeksforgeeks.org to set the file pointer to the beginning of the dict file
    fseek(dictFP, 0, SEEK_SET); // use seekset at byte 0 to start at the beginning of the file
    printf("Finished counting words in dict file.\n");

    // return the counter
    return counter;
} */


// UPDATE: NO LONGER NEEDED. This was my original attempt at recursively searching the grid.
// I'm not using it anymore because this function populated words that were not adjacent to the cells.
// That means if a letter was at cell UP-LEFT (-1, -1) and another letter was at cell DOWN-RIGHT (1, 1), then this function would attempt to make a word from both of those letters without going through adjacent cells
// It was correctly forming words from the grid, but it wasn't going to each adjacent cell, or even back to a previous cell.
// It was simply just picking a letter and adding it to the word.

// helper function to find the 5-letter words that are both lowercase and alphabetic from the dictionary file
/*bool search_correct_words(strand_t * strands, int row, int column, char * word, int length_word, bool ** visited_cell) {

    
    //printf("Searching word: %s, Length: %d\n", word, length_word); // Debug print


    // Base Case: If the entire word at the given length has been found, compare to null character to indicate full word
    // Make sure word array has enough space to store the word
    if (word[length_word] == '\0') { // - 1 to get rid of null char (since C is annoying)
        
        // If the word length exceeds the allocated space, print an error message and return
        //printf("Error: Word length exceeds allocated space.\n");
        
        return true; // if word is found, boolean function returns true
    }

    // Copy the letter from the grid to the word array
    //word[length_word] = strands->letters[row][column];
    //word[length_word + 1] = '\0'; // for null character

    // set the boolean to true before entering loop
    visited_cell[row][column] = true;

    // for debugging, check if the word formed matches the words we populated in the strands->words array
    for (int i = 0; i < strands->numWords; ++i) {

        // if the word we generated in this function is equal to the word at the i'th index of the words array, print success message
        if (strcmp(word, strands->words[i] )== 0) {

            printf("Word: %s... Found at position: %d, %d...\n", word, row, column); // output the word found and where exactly it was found so I can test this
            break; // exit loop since word found
        }
    }

    // Define directions for row to move
    // 8 possible directions
    // These should be declared as arrays since they store the directions of the grid
    // Up-Left: (-1, -1), Up: (-1, 0), Up-Right: (-1, 1), Left: (0, -1), Right: (0, 1), Down-Left: (1, -1), Down: (1, 0), Down-Right: (1, 1)
    int row_direction[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    int column_direction[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    // Iterate through the grid in all 8 directions
    for (int i = 0; i < 8; ++i) { // 8 is the limit of the directions (listed above each direction)

        // define a new row and column that adds the parameter row and columns to the position in the grid
        int new_row = row + row_direction[i]; // the new row is at the i'th cell

        int new_column = column + column_direction[i]; // the new column is at the i'th cell

        // ensure that the position is in the boundaries of the grid
        // the rows and column should be greater than or equal to zero (the starting cell) and should be less than the rows and columns in the strand struct 
        (to ensure that the recursive function doesn't try to access data outside the grid) 
        if (new_row < strands->rows && new_column < strands->cols && new_row >= 0 && new_column >= 0) {

            // check that the cell is not visited by calling the boolean
            if (!visited_cell[new_row][new_column]) {

                // recursively call the function to search each cell, and add 1 to the length_word each time (so that base case will be met if word length is valid)
                search_correct_words(strands, new_row, new_column, word, length_word + 1, visited_cell); // new row and column parameters passed each time to update the cell search, and word_length is incremented until word_length is valid
            }
        }
    }

    // mark boolean as false to restart it as unvisited (since we are recursively calling function)
    visited_cell[row][column] = false;

    // If word isn't found, return false (so we can implement this in the is_word_in_strand function)
    return false;
} */



// UPDATE: NO LONGER NEEDED for my create_strand function. In this code, I was trying to take the row x column file and set the number of words to
// the provided _words.txt file. However, I soon realized that I had to recursively search the grid to formulate words
// SO this part of my function is no longer valid.

    /*// Calculate the number of words to be found based on the grid size
    if (strands->rows == 2 && strands->cols == 2) {
        strands->numWords = 12; // if 2x2, the words should amount to 12
    }
    else if (strands->rows == 3 && strands->cols == 3) {
        strands->numWords = 8; // if 3x3, words should be 8 total
    }
    else if (strands->rows == 5 && strands->cols == 5) {
        strands->numWords = 18; // if 5x5, numwords should be 18
    }
    else if (strands->rows == 8 && strands->cols == 6) {
        strands->numWords = 192; // if 8x6, 192 words total
    } */
