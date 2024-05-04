#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*
 * print_board function is used to display a 2d representation of the tic-tac-toe board.
 * We will use this in the game and update each "square" in order to keep track of current position.
 *
 * Standard tic-tac-toe is played in 3x3 so no need to worry about varying sizes.
 */
void print_board(char board[3][3])
{
    //Initialize the format of the top bottom row separators
    char horizontal_separator[] = "    ------------";

    //print the column numbers
    printf("     0   1   2\n");
    //Loop through the x-axis rows.
    for(int x =0; x<3; x++)
    {
        //Print the row numbers and separators
        printf("%s\n %d ",horizontal_separator, x);
        //Loop through the y-axis rows.
        for(int y=0; y<3; y++)
        {
            //print each character in its blocks
            printf("| %c ", board[x][y]);
        }
        //print the final block on the far right.
        printf("| \n");
    }
    //final bottom separator.
    printf("%s\n", horizontal_separator);
}

/*
 * prompt_move asks the user to input x and y coordinates for where they would like to place there
 * marker on the tic-tac-toe board. By default, the player marker is x
 */
void prompt_move(char board[3][3])
{
    int valid_input = 0;          // To read each character
    int row;
    int col;

    while (!valid_input || getchar() != '\n')
    {
        // Ask the user to input their move, if 2 integers are not inputed we have an error
        printf("Enter your move (row col): ");
        if (scanf("%d %d", &row, &col) != 2)
        {
            printf("Error: Please enter two integers separated by a space.\n");
            //Clear input buffer for the next input attempt by the user.
            while ((getchar()) != '\n');
        }
        //if the inputs are outof bounds
        else if (row < 0 || row > 2 || col < 0 || col > 2)
        {
            printf("Error: Row and column must be between 0 and 2.\n");
        }
        //if the inputed position already has a player there
        else if (board[row][col] != ' ')
        {
            printf("Error: Position %d %d is already occupied.\n", row, col);
        }
        //we have a valid input.
        else
        {
            valid_input = 1;        // Change the variable to read valid
            board[row][col] = 'X';  // And place the 'X' on the board
        }
    }
}

/*
 * check_win is used to check if at the time it is called there is a winner, meaning 3 straight places, for
 * each player.
 */
bool check_win(char board[3][3])
{
    // Check rows
    for (int i = 0; i < 3; ++i)
    {
        //If all indexes from 0-2 in each row are equal, then the symbol in those indexes is the winner
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            printf("%c wins!\n", board[i][0]);
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; ++j)
    {
        //If all indexes from 0-2 in each col are equal, then the symbol in those indexes is the winner
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[0][j] == board[2][j])
        {
            //print the board than the symbol of the winner
            print_board(board);
            printf("%c wins!\n", board[0][j]);
            return true;
        }
    }

    // Check diagonal 1, staring from the top left (0,0) to the bottom right (2,2)
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        //print the board than the symbol of the winner
        print_board(board);
        printf("%c wins!\n", board[0][0]);
        return true;
    }
    // Check diagonal 2, staring from the top right (0,2) to the bottom left (2,0)
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        //print the board than the symbol of the winner
        print_board(board);
        printf("%c wins!\n", board[0][2]);
        return true;
    }

    // No win found
    return false;
}

/*
 * computer_move will simulate another player playing against the user. Here we randomly generate X and Y coordinates
 * checking for validity of the generated location
 */
void computer_move(char board[3][3])
{
    int row = rand() % 3;       //Random guess between 0-3 for row
    int col = rand() % 3;       //Random guess between 0-3 for col

    //If the location guessed is not empty, recursively call computer_move.
    if(board[row][col] != ' ')
    {
        computer_move(board);
    }
    //When the randomly generated coordinates are valid, place O there.
    else
    {
        board[row][col] ='O';
    }

}

int main()
{
    // Use the current time as the seed for
    // the random number generator
    srand((unsigned int)time(NULL));

    //This is the tic-tac-toe board
    char board[3][3] =
            {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
            };

    //Initial print empty board
    print_board(board);

    //Loop turns starting with player until a winner is found
    while (!check_win(board))
    {
        prompt_move(board);
        if(check_win(board))
        {
            break;
        }

        computer_move(board);
        if(check_win(board))
        {
            break;
        }
        print_board(board);
    }

    return 0;
}
