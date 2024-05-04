#include <stdio.h>
int main() 
{
    int count;
    char character;

    //Scan for the output format of compress which is a number followed by a digits, then new line.
    //Check if scanf found BOTH a digit and character to print.
    while (scanf("%d %c\n", &count, &character) == 2)
    {
        while (count > 0)
        {
            // Print the character followed by a space
            printf("%c ", character);
            //decrement the count so we know how many more characters to print
            count--;
        }
    }

    return 0; // Successful termination
}
