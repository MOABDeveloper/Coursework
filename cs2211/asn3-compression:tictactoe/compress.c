#include <stdio.h>
#include <ctype.h>

/*
 *compress aims to further compress the user input into
 * the specific character counts.
 * Keeping track of the current character and seeing how many
 * more of the same character there is in the input. Than displaying amount-character
 */
void compress(char buffer[1024], int length)
{
    // Check if the user didn't input anything.
    if (length == 0)
    {
        return;
    }

    int count = 1;                  // Initialize the count of characters
    char currentChar = buffer[0];   // The current character to compare

    // Iterate over the buffer
    for (int i = 1; i < length; ++i)
    {
        //If the current character is the same as the last increment the count.
        if (buffer[i] == currentChar)
        {
            count++;
        }
        // If it's different, print the count and the character, then reset
        else
        {
            printf("%d %c\n", count, currentChar);
            currentChar = buffer[i];
            count = 1;
        }
    }
    // Print the last character count and character
    printf("%d %c\n", count, currentChar);
}
/*
 * read_input will take in the user input and remove any spaces.
 * Than we store the non white space input in the buffer while keeping track
 * of the non white space characters.
 */
int read_input(char buffer[1024])
{
    int input;         // To read each character
    int count = 0;     // To count non-whitespace characters

    //get characters until we reach the end of the file
    while ((input = getchar()) != EOF)
    {
        //if the current input char is not a whitespace
        if (!isspace(input))
        {
            //Store the character in the current buffer and increment count.
            //Cast input to a char type
            buffer[count++] = (char)input;
        }
    }
    // Return the count of non-whitespace characters
    return count;
}

int main() {
    char input_array[1024] = {0}; // Initialize the buffer
    int num_chars;

    num_chars = read_input(input_array);
    compress(input_array, num_chars);
    printf("\nNumber of non-whitespace characters: %d\n", num_chars);


    return 0;
}
