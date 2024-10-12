/* 
Name: Omar Masri
Date: 3/10/2024
CPSC 1070
Lab 04

Code Description:

Hangman is a word game in which one player comes up with a word which they keep hidden and then someone else tries to guess what that 
word is, one letter at a time. This game is usually played with a drawing of a gallows and everytime the guessing player guesses a letter 
not in the hidden word, part of a stick figure is removed to the drawing

Whenever the guessing player guesses a correct letter, that letter is written down in the appropriate positions. The guesser may also 
guess a word which, if incorrect, will be punished by removing a limb from the stick figure. Once the guessing player has guessed the 
correct word they win, and if they do not guess the correct word before the entire stick figure is gone, they lose.

This program runs a hangman game by randomly selecting a word, printing the gallows to the screen, and prompting the user.
For every incorrect letter, print incorrect message and update the gallows. If gallows figure disappears completely, user loses.
If user guesses correct letters or word completely, game ends and user wins.
At the end, user is prompted to play again.
*/


#include "hangman.h"

using namespace std;

// Main function
int main() {
    runGame(); // Call the run game function

    return 0;
}

string* readDictionary(int &len) {

    // String to provide access to open the file provided by the SOC
    string american_english = "/usr/share/dict/american-english";

    // Create an input file that takes in the "american_english" string variable we created
    ifstream file(american_english);

    // Check if the file isn't open and print error message
    if (!file.is_open()) {
        cout << "Could not open file: " << american_english << endl;
    }

    // Dictionary string to write the contents of the file to
    string dictionary;

    // Lowercase letter counter and Alphabetic letters counter (so no special characters are included in the updated dictionary)
    int lower_alpha_count = 0;


    // Reads contents from file to dictionary
    while (file >> dictionary) {

        // Create boolean variable to check for lowercase and alphabetic words
        bool lower_alphabetic_bool = true;

        // Iterate through each letter in the dictionary
        // Use size_t (or auto) to to represent the object size of i when comparing it to dictionary.size
        for (size_t i = 0; i < dictionary.size(); ++i) {

            // Check if word isn't lowercase or alphabetic
            if (!islower(dictionary.at(i)) || !isalpha(dictionary.at(i))) {
                lower_alphabetic_bool = false;
        }
        }
        
        // Check if the boolean is true, and increase the counter if it is true
        if (lower_alphabetic_bool) {
            
            // Increase the count for lowercase alphabetic letters
            lower_alpha_count += 1;
        }
        }

    
    // Create new array of words that contain all lowercase letters
    // Must allocate memory (can use new instead of malloc thanks to c++)
    string* lowerword = new string[lower_alpha_count]; //lowerword variable that is of pointer string and creates a new string array that takes the lowercase-alphabetic count words as the size of the array

    // Close the file after creating the newly allocated memory for the lowerword string
    file.close();

    // Open file again to read the file and this time write the lowercase letters to the newly allocated lowerword string
    file.open(american_english);

    // j variable to append each lowercase alphabetic word in the index to the newly created array "lowerword"
    int j = 0;
    
    // Read the file again but this time store the lowercase words in the new array we just created
    while (file >> dictionary) {

        // Create boolean variable to check for lowercase and alphabetic words
        bool lower_alphabetic_bool = true;

        // Iterate through each letter in the dictionary
        // Use size_t (or auto) to to represent the object size of i when comparing it to dictionary.size
        for (size_t i = 0; i < dictionary.size(); ++i) {
            
            // Check if word isn't lowercase or alphabetic
            if (!islower(dictionary.at(i)) || !isalpha(dictionary.at(i))) {
                lower_alphabetic_bool = false;
        }
        }

        // Check if boolean is true
        if (lower_alphabetic_bool) {
            
            // Add the word in the dictionary to the i'th element in the new array
            lowerword[j] = dictionary;
            j += 1; // Append j
        }
    }

    // Close the file
    file.close();

    // This updates the length parameter passed by in the function to the number of lowercase-alphabetic words (instead of the number of words in the dictionary)
    len = lower_alpha_count;

    // Return the newly created array
    return lowerword;

}

string generateAnswer(string * dictionary, int len) {
    // Random function with time parameter both inputted in the header file
    // Allows the random number generator to be seeded with the current time
    srand(time(NULL));

    // Create a variable for the random words that will choose from the list of strings (randomly)
    int random;

    // Assign the variable to choose a random index from the dictionary (with the corresponding word)
    // The random word is chosen from the index 0 to the last index of the new len in new dictionary array (called in function paramater)
    random = rand() % len;



    // End the function by returning the randomly selected word
    return dictionary[random];
}

void runGame(void) {
    // Input variable
    char input;

    // Boolean to see if game is won or lost
    bool game_end = false;

    // Initialize the stage (number of incorrect guesses) to 0 so gallows can be correctly printed
    int stage = 0;

    // Initialize the variable that will give us the known Letters inputted by user
    string known_letters;

    // Initialize variables called by the makeGuess functions
    string * dictionary;
    int len;
    char type = ' '; // Initialize type to empty string since it will cause the makeGuess function to be overloaded; it will not be used further than this in the function

    // Initialize the variable that will give us the correct answer
    string correct_answer;

    // Call readDictionary function to get new array of lowercase words using the variable we defined above
    dictionary = readDictionary(len);

    // Generate the answer and store in variable we created after reading in the lowercase dictionary
    correct_answer = generateAnswer(dictionary, len);


    // character to ask user if he wants to play again
    char playagain;

    // Do-while loop to ensure the game keeps going if user inputs yes
    // If user inputs 'n', game ends
    do {

        // Reset the known_letters string at the beginning of each game by passing it as empty string
        known_letters = "";

        // Reset stage to 0 for each new game
        stage = 0;

        // Reset game_end to false for each new game
        game_end = false;

        // While loop to ensure that the game continues to run until the user gets more than 5 mistakes (in which the hangman character will die)
        // Game also runs until user correctly guesses word
        while (stage <= 5 && !game_end) {

            cout << "*** Welcome to Hangman ***" << endl << endl;

            // Call print gallows function to print the current hangman figure after number of incorrect guesses
            printGallows(stage);

            // Newline for formatting
            cout << endl;

            // Call printCorrectLetters function with empty char passed to guess to print all the underscores in the beginning (since user hasn't guessed anything yet)
            printCorrectLetters(' ', correct_answer, known_letters);

            // Keep asking the user for word or character input
            cout << endl;
            cout << "Would you like to guess a word or character (w or c): ";
            cin >> input;


            // Switch statement to call word function or character function
            switch (input) {
                case 'w': {

                    // Call makeGuess function without char type for word input to a string variable named guess
                    string guess = makeGuess(dictionary, len);

                    // Check the guessed word to the answer by calling the boolean function check Guess and assign it to boolean variable
                    bool check = checkGuess(guess, correct_answer);

                     // Check if the boolean is true or not
                    if (check == true) {

                        // Print correct guess message
                        cout << "That guess is correct!" << endl << endl;

                        cout << "You won!" << endl << endl;
                        game_end = true;
                        }
                    else {
                        // If the guess is incorrect, output incorrect message
                        cout << "That guess is incorrect!" << endl << endl;

                        // Increase the number of incorrect guesses so the stage can be updated
                        stage += 1;
                    }

                // Exit switch statement
                break;
                }

                case 'c': {
                    // Call makeGuess function with char type for character input
                    char guess_char = makeGuess(dictionary, len, type);

                    // Check the guessed character to the answer by calling the boolean function check Guess and assign it to boolean variable
                    bool check_char = checkGuess(guess_char, correct_answer);

                    // Check if the boolean is true or not
                    if (check_char == true) {

                        // Print correct guess message
                        cout << "That guess is correct!" << endl << endl;

                        // Update the known letters if the guess is correct using a for loop that is less than the answer size
                        // Use size_t (or auto) to to represent the object size of i when comparing it to correct_answer.size
                        for (size_t i = 0; i < correct_answer.size(); ++i) {

                            // Check if the correct answer at index i is equal to the guessed character
                            if (correct_answer[i] == guess_char) {
                                
                                // If it is true, add the character to known_letters string
                                known_letters += guess_char;
                            }
                        }

                        // If the size of the known letters is equal to the size of the correct answer, the user wins
                        if (known_letters.size() == correct_answer.size()) {
                            cout << "You won!" << endl;
                            game_end = true;
                        }
                    }
                    else {
                        // If the guess is incorrect, output incorrect message
                        cout << "That guess is incorrect!" << endl << endl;

                        // Increase the number of incorrect guesses so the stage can be updated
                        stage += 1;
                    }
            break; // switch break
            }

            default:
                // Default statement if user inputs something that isn't in the cases above
                cout << "Invalid input, please try again!" << endl;
                cout << endl;
                break;
            }
        }

        // If user exceeds incorrect guesses, print you lost message
        if (stage > 5) {
        cout << "You lost!" << endl << endl;
        }

        // Ask the user if they want to play again, then restart the game
        cout << "Thank you for playing! Would you like to play again (y or n): ";
        cin >> playagain;

    } while (playagain == 'y');
    

}


void printGallows(int stage) {

    // Switch statement to adjust the hangman figure based on the number of incorrect guesses
    // SPACING IS IMPORTANT, THAT'S WHY I KEPT GETTING IT WRONG IN THE AUTOGRADER
    switch (stage) {

        // 0 incorrect guesses prints current hangman figure
        case 0:
            // ASCII art for the hangman gallows to be printed
            cout << " \\0/" << endl;
            cout << "  |" << endl;
            cout << " / \\" << endl;
            break;
    

        // 1 incorrect guess removes the right leg
        case 1:
            cout << " \\0/" << endl;
            cout << "  |" << endl;
            cout << " /" << endl;
            break;
        
        // 2 incorrect guesses removes both legs
        case 2:
            cout << " \\0/" << endl;
            cout << "  |" << endl;
            break;
        
        // 3 incorrect guesses removes both legs and the right arm
        case 3:
            cout << " \\0" << endl;
            cout << "  |" << endl;
            break;

        // 4 incorrect guesses removes both arms and legs
        case 4:
            cout << "  0" << endl;
            cout << "  |" << endl;
            break;
        
        // 5 incorrect guesses removes both arms both legs and the torso
        case 5:
            cout << "  0" << endl;
            break;

        // Any other number of guesses breaks out of this switch statement (since the user lost)
        default:
            break;

    }
}

char makeGuess(string * dictionary, int len, char type) {
    // User input character variable
    char inputchar;

    // boolean for input validation
    bool valid_inp = false;

    // while loop that ensures the input is lowercase
    while (!valid_inp) {

        cout << "Please enter a guess: ";
        // Take in the input from the user for char guess
        cin >> inputchar;

        // Keep iterating if input is not a lowercase character
        if (!islower(inputchar)) {
            cout << "Invalid input, please try again!" << endl;
            }

        else {
            valid_inp = true; // If input is valid, let user keep playing
        }
    }

    // Return the character the user guesses
    return inputchar;
}

string makeGuess(string * dictionary, int len) {
    // User input string variable
    string inputword;

    // boolean to ensure input is valid
    bool input_validation = false;

    // If guess is not in the dictionary, while loop keeps iterating through to ensure user provides acceptable input
    while (!input_validation) {
        cout << "Please enter a guess: ";
        // Take in the input from the user for word guess
        cin >> inputword;

        // Use the find function to see if the string input is in the dictionary, otherwise keep reprompting the user
        /* The find function takes in the dictionary as the starting value for the range, the dictionary plus the length of the lowercase array
        as the ending iterator for the range, and the inputword value as the word that is being searched between the beginning and ending ranges*/
        // If after searching for the value and the operator is found, then the inputted word != (doesn't equal) the iterator returned by dictionary + len
        // If the value returned after finding input word is equal (==) to the dictionary + len, then the dictionary value was not found
        if (find(dictionary, dictionary + len, inputword) != dictionary + len) { // Ensures input is in the dictionary
            input_validation = true;
        }
        else {

            // If word isn't in dictionary, reprompt user
            cout << "Invalid input, please try again!" << endl;
        }
    }

    // return the word the user guesses
    return inputword;
}

bool checkGuess(char guess, string answer) {

    // Iterate through the answer length in the function parameter
    // Use size_t (or auto) to to represent the object size of i when comparing it to answer.size
    for (size_t i = 0; i < answer.size(); ++i) {
        // If the character is equal to the answer at the i'th index, return true
        if (guess == answer[i]) {
            return true;
        }
    }

    // If the character isn't in the answer, return false
    return false;
}

bool checkGuess(string guess, string answer) {

    // Check if the word guessed is equal to the answer, return true
    if (guess == answer) {

        return true;
    }

    // If word isn't answer, return false
    else {
        return false;
    }
}

void printCorrectLetters(char guess, string answer, string knownLetters) {

    // Print out underscores at beginning of game
    // Pass an empty string for the guess
    /* Checks if the known Letters string size is empty, and if it is, print all underscores that will print at beginning of
    game, or if the user never gets the right characters */
    if (knownLetters.size() == 0) {
        
        // Prints out the underscores based on the size of the answer using for loop
        // Use size_t (or auto) to to represent the object size of i when comparing it to answer.size
        for (size_t i = 0; i < answer.size(); ++i) {

            // Output the number of underscores based on the generated answer
            cout << "_";
        }
    }

    // Checks if the known Letters size is not empty, which means the letter should replace the underscore
    if (knownLetters.size() != 0) {

        // Print out the letter based on the size of the answer, and keep the underscores for the remainder of the word
        // Use size_t (or auto) to to represent the object size of i when comparing it to answer.size
        for (size_t i = 0; i < answer.size(); ++i) {

            // Check if the find function doesn't return a string at no position (string::npos) which is included in the find function
            // If it does return a string at no position, then "_" characters will be printed for every character of the word (since the guess is incorrect)
            // If it doesn't return string at no position, then the correct character is updated and the unknown characters are still underscores
            if (knownLetters.find(answer.at(i)) != string::npos) {

                // Output the character found in knownLetters and replace the underscore
                // Print all the known letters in the string to the terminal
                cout << answer.at(i);

            }
            else {

                // For spaces that aren't guessed correctly, output the underscores based on the answer size
                cout << "_";
            }
        }
    }


    // Print a newline at the end
    cout << endl;
}