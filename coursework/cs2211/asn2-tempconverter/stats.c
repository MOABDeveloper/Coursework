/*
 * converter.c
 *
 * CS 2211b - Winter 2024
 * Assignment 1
 * Student: Mohammed Abdul-nabi
 *
 * This program takes user inputs and returns various stats about them
 *
 */
#include <stdio.h>

int main()
{
    int count = 1;      //Stores how many digits have been entered so far
    int sum = 0;        //Stores all the digits added
    int digit;          //Current Digit
    float average;      //Average of all the digits entered

    const int MAX_ENTRY_ALLOWED =  10; //Stores how many entries is allowed

    printf("Enter a digit (q to quit): "); //prompt user to enter digit

    /*
     * While count is less than 10, take the users input store it in digit,
     * increment the counter and add to the sum.
     *
     * We adjust the MAX_ENTRY_ALLOWED to account for the initial 0 loop.
     */
    while (scanf("%d", &digit) == 1 && count < MAX_ENTRY_ALLOWED)
    {
        printf("Enter a digit (q to quit): ");
        sum += digit;
        count++;
    }

    //If digits where entered
    if (count > 0)
    {
        //Calculate the average
        average = (float)sum / count;

        //Return the sum of the numbers entered
        printf("\nSum : %d\n", sum);
        //Return the qty of numbers entered
        printf("Count : %d\n", count);
        //Return the average
        printf("Average : %.2f\n", average);
    }
    else
    {
        //User did not input any digits.
        printf("\nNo digits entered.\n");
    }

    return 0;
}
