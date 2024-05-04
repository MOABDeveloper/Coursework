/*********************************************************************************
*    lookup.c
*    Assignment 4
*    Mohammed Abdulnabi
*    251010251
*    
*    Allow the user to pass in certian command line arguments to search and create
*    a trie. 
*********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "trie.h"

void usage()
{
    printf("Usage: lookup [OPTION] [ARGUMENT]\n");
    printf("Options:\n");
    printf("  p <prefix>   Print all words with the given prefix\n");
    printf("  c <prefix>   Check if the prefix is in the trie\n");
    printf("  w <word>     Check if the word is in the trie\n");
    printf("  (no option)  Print all words in the trie\n");
}

int main(int argc, char* argv[])
{
    trie* user_trie = trie_create();        //Creates a trie with the user input. 

    const int BUFFER_SIZE = 256;            //Size read by fgets
    char input[BUFFER_SIZE];                //Stores the string from fgets

    while(fgets(input,BUFFER_SIZE,stdin))   //Loops for all lines of the file
    {
        size_t len = strlen(input);         //The world length of the string
        if(input[strlen(input)-1] == '\n')  //If the last character is a newline
        {
            input[len - 1] = '\0';          //remove last character from input
        }
        trie_insert(user_trie,input);       //Takes the input read and inserts it into the trie
    }

    if(argc == 1)                           //Only one argument is entered (./lookup)
    {
        trie_print(user_trie);              //Print the entire trie. 
    }
    else if(argc == 3)
    {
        if(!strcmp(argv[1],"p"))            //Prints all words with the PREFIX given        
        {
            trie_print_prefix(user_trie,argv[2]);
        }
        else if(!strcmp(argv[1],"c"))       //Checks if a given PREFIX is in the trie
        {
            printf("Prefix %s: %d\n",argv[2],trie_contains_prefix(user_trie,argv[2]));
        }
        else if(!strcmp(argv[1],"w"))       //Checks if a given WORD is in the trie
        {
            printf("Word %s: %d\n",argv[2],trie_contains(user_trie,argv[2]));
        }
        else                                //The user as entered an invalid [OPTION]
        {
            usage();
        }
    }
    else                                    //One or more of parameters are invalid
    {
        usage();
    }
    trie_free(user_trie); // Free memory
    return 0;
}
