"""
Name: Omar Masri
Date: 10/23/23

Code Description:
This program will give a brief introduction to its usage, then ask two players, player X and player O,
to play Tic-Tac-Toe against each other. The players will be prompted to input row and column numbers
to place their X or O marker on the Tic-Tac-Toe board, which will update accordingly.
When the board is filled (a tie) or a player has gotten three of their markers in a row (horizontally,
vertically, or diagonally) the game will announce the results and ask if you would like to play again.
You must use a 2D array. You must use functions.
Your code's output must exactly match the provided test output files.

"""

#Function that prints the blank board
def print_board(board):
    for row in board:
        print("| " + " | ".join(row) + " |")
        
#Function that checks if the player wins
def check_win(board, player):
    #Check for horizontal win
    for row in board:
        if all([cell == player for cell in row]):
            return True
    #Check for vertical win
    for col in range(3):
        if all([board[row][col] == player for row in range(3)]):
            return True
    #Check for diagonal win
    if all([board[i][i] == player for i in range(3)]) or all([board[i][2-i] == player for i in range(3)]):
        return True
    return False

#Function that checks if the board is full
def is_full(board):
    return all(cell != "_" for row in board for cell in row)

#Function that checks if a spot is full
def spot_full(board, player):
    return(cell == player for row in board for cell in row)

#Function that makes sure the input is validated when the user inputs a row and column number
def is_valid_input(row, col, board):
    return 1 <= row <= 3 and 1 <= col <= 3 and board[row - 1][col - 1] == "_"

#Function for the example board:
def example_board(exboard):
    for row in exboard:
        print("| " + " | ".join(row) + " |")

#Example board:
exboard = [['_', '_', 'X'], ['_', '_', '_'], ['_', '_', '_']]

#Function that prints the welcoming statements for tic tac toe (the introduction)
def print_info():
    print("Let's play Tic-Tac-Toe!")
    print("When prompted, enter desired row and column numbers")
    print("Example: 1 3")
    example_board(exboard)

#Function for the main gameplay of tic tac toe
def play_tic_tac_toe():
    while True:
        #Blank board to allow the function to add X or O in the board
        #THIS IS THE 2D ARRAY
        board = [['_', '_', '_'], ['_', '_', '_'], ['_', '_', '_']]
        players = ["X", "O"]
        player_turn = 0
        print_info()
        print("\nLet's play!\nPlayer X starts!\n")
        #Prints the blank board to start the game
        print_board(board)
        
        while True:
            #Try and except statements to ensure that the player inputs the valid row and column numbers
            #from 1 to 3
            player = players[player_turn]
            print("Enter row and column for player {}".format(player))
            while True:
                try:
                    row, col = map(int, input().split())
                    if is_valid_input(row, col, board):
                        break
                    else:
                        print("Please enter valid row and col numbers from 1 to 3:")
                except ValueError:
                    print("Please enter valid row and col numbers from 1 to 3:")
                    continue
            #If the input is valid, the board updates to the player's mark (X or O)
            if is_valid_input(row, col, board):
                board[row - 1][col - 1] = player
                print_board(board)
                #Checks the function if the player won, and prints the message
                if check_win(board, player):
                    print("\nPlayer {} WINS!\n".format(player))
                    break
                #If board is full, no one wins, and prints that it is a tie
                elif is_full(board):
                    print("\nIt's a TIE!\n")
                    break

                player_turn = 1 - player_turn
            else:
                print("Please enter valid row and col numbers from 1 to 3:\n")
    #Asks the player if they want to play again
    #This loop ensures that the player inputs a valid input ("Y or N")
        while True:
            play_again = input("Do you want to play again? Y or N\n").strip()
            if play_again == "Y":
                break
            elif play_again == "N":
                return False
            else:
                print("Please enter valid input: Y or N")

#Main code loop that allows the code to be executed from this script. (Code isn't imported from a 
#module)
if __name__ == "__main__":
    play_tic_tac_toe()
