/*
 * converter.c
 *
 * CS 2211b - Winter 2024
 * Assignment 1
 * Student: Mohammed Abdul-nabi
 *
 * This program takes user inputs and can convert between multiple different units.
 *
 */

#include <stdio.h>

float celsius_fahrenheit();
float kilometer_miles();
float joules_calories();
void printError();

int main()
{
    int user_input;  //Stores what option the user selects

    do
    {
        //Prompts the user with the selection menu
        printf("\n========== Menu ===========================\n"
               "1 Convert between Celsius and Fahrenheit\n"
               "2 Convert between Kilometers and Miles\n"
               "3 Convert between Joules to Calories\n"
               "0 Quit\n"
               "===========================================\n");
        //Reads user input and stores it in user_input
        scanf("%d", &user_input);

        //Decides which function to execute based of user_input
        switch (user_input) {
            case 0:
                return 0;
            //celsius_fahrenheit if user_input 1
            case 1:
                celsius_fahrenheit();
                break;
            //kilometer_miles if user_input 2
            case 2:
                kilometer_miles();
                break;
            //joules_calories if user_input is 3
            case 3:
                joules_calories();
                break;
            //User entered an invalid input
            default:
                printError();

        }
    }
    //Sets exit condition of do for when user_input = 0
    while (1) ;
}

/*
 * Converts in either direction between Celsius and Fahrenheit depending on user input
 */
float celsius_fahrenheit(){
    char input_unit;   //Stores if the original unit C or F
    float input_temp;  //Stores what is the temp the user wants to convert
    float converted_value;      //Stores Converted Temp Value

    const float SCALE = (5.0f/9.0f);     //Factor used as multiplier when converting from C to F.
    const float INV_SCALE =(9.0f/5.0f);  //Inverted factor used as divisor to convert from F to C.
    const float FRZING_POINT = 32;      //Freezing point of water used in both conversions.

    do
    {
        //Prompt user for unit input and store it
        printf("c: Celius_to_ferenheit\nf: Fahrenheit to Celsius\n");
        scanf(" %c", &input_unit);

        //Validate user input.
        if (input_unit != 'c' && input_unit != 'f')
        {
            printError();
            //Re-prompt user for input if invalid
            continue;
        }
    }
    while (input_unit != 'c' && input_unit != 'f');


    //# value of temp that user wants to convert
    printf("Enter Value to Convert: ");
    scanf(" %f", &input_temp);

    //Select formula based on input unit.
    switch (input_unit)
    {
        //if from Celsius to Fahrenheit
        case 'c':
            converted_value = (input_temp * SCALE + FRZING_POINT);
            printf("%.2f Celsius = %.2f Fahrenheit\n", input_temp, converted_value);
            break;

        //if from Fahrenheit to Celsius
        case 'f':
            converted_value = (input_temp - SCALE) / INV_SCALE;
            printf("%.2f Fahrenheit = %.2f Celsius\n", input_temp, converted_value);
            break;

        default:
            printError();
    }
}

/*
 * Converts between kilometers and miles in either direction depending on user input.
 */
float kilometer_miles() {
    char input_unit;        //Stores if the original unit Kilometers or Miles
    double input_distance;  //What is the temp the user wants to convert
    double converted_value;          //Converted Distance Value

    const float SCALE = 1.6f; //Scaling factor used as multiplier/division in conversion


    do
    {
        //Prompt user for unit input and store it
        printf("k: Kilometers to Miles\n"
               "m: Miles to Kilometers\n");
        scanf(" %c", &input_unit);

        //Validate user input.
        if (input_unit != 'k' && input_unit != 'm')
        {
            printError();
            //Re-prompt user for input if invalid
            continue;
        }
    }
    while (input_unit != 'k' && input_unit != 'm');


    //# value of distance that user wants to convert
    printf("Enter Value to Convert: ");
    scanf(" %lf", &input_distance);

    //from kilometeres to miles
    if(input_unit == 'k')
    {
        converted_value = (input_distance / SCALE);
        printf("%.2f Kilometers = %.2f Miles\n", input_distance, converted_value);
    }
    //from miles to kilometers
    else if ( input_unit == 'm')
    {
        converted_value = (input_distance * SCALE);
        printf("%.2f Miles = %.2f Kilometers\n", input_distance, converted_value);
    }
}

/*
 * Converts in either direction joules and calories depending on user input.
 */
float joules_calories(){
    char input_unit;        //Stores if the original unit Joules or Calories
    double input_energy;    //What is the unit the user wants to convert from
    double converted_value; //Converted Energy Value

    do
    {
        //Prompt user for unit input and store it
        printf("j: Joules to Calories\n"
               "c: Calories to Joules\n");
        scanf(" %c", &input_unit);

        // Validate user input
        if (input_unit != 'c' && input_unit != 'j')
        {
            printError();
            //Re-prompt user for input if invalid
            continue;
        }
    }
    while (input_unit != 'j' && input_unit != 'c');


    //# value of energy that user wants to convert
    printf("Enter Value to Convert: ");
    scanf(" %lf", &input_energy);

    //if from Joules to Calories
    if(input_unit == 'j')
    {
        converted_value = (input_energy / 4.184);
        printf("%.2f Joules = %.2f Calories\n", input_energy, converted_value);
    }
    //if from Calories to Joules
    else if ( input_unit == 'c')
    {
        converted_value = (input_energy * 4.184);
        printf("%.2f Calories = %.2f Joules\n", input_energy, converted_value);
    }
}

//This is the error message we will print when the user enters and invalid input.
void printError(){
    printf("Invalid input, Please try again! \n");
}
