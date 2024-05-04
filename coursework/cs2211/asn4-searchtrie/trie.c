/*********************************************************************************
    trie.c
    Assignment 4
    Mohammed Abdulnabi
    251010251
    
    Building a data structure similar to a tree that is used for the storage and
    retrieval of strings. 

*********************************************************************************/
#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Allocates memory for a new trie node and sets all the feilds inside the node 
* to the default values and the values the parameters passed in by the user. 
*/
trie_node* trienode_create(char data)
{
    //Dynamically allocate memory
    trie_node* node = (trie_node*)malloc(sizeof(trie_node));

    if (node != NULL) 
    {
        node->data = data;  //Set the data to the input
        node->word = NULL;  //Set all word to null
        //Set all the children to null 
        for (int i = 0; i < ALPHABET_SIZE; i++) 
        {
            node->children[i] = NULL;
        }
    }
    //Return a the pointer to the newly created a node. 
    return node;    
}

/*
*   Allcoates memeory for the whole trie and sets the default values for the root node of the trie.
*   These are root = $ and size = 0;
*/
trie* trie_create()
{
    //Allocate memory for new trie.
    trie* t = (trie*)malloc(sizeof(trie));
    //Store $ in the root field.
    t->root =trienode_create('$');
    //Initialize the size of the trie to zero.
    t->size = 0;
    return t;
}

/*
*   Adds the word passed in by the user into the trie, adding any letters/nodes not already 
*   present in the tree along the way.
*/
void trie_insert(trie* t, char* word)
{
    trie_node* current_node = t->root;  //Pointer to current node.
    char* char_pointer = &word[0];      //Pounter to current character.

    //Loop until the end of the loop
    while(*char_pointer != '\0')
    {
        //Index of current character.
        int index = *char_pointer - 'a';
        //If the current node does not contain the letter we are on.
        if (current_node->children[index] == NULL)
        {
            //Create a new child node to hold the current letter.
            current_node->children[index] = trienode_create(*char_pointer);
        }

        //If the current node does contain the letter we are on. 
        current_node = current_node ->children[index];  //Enter the child node for that letter.
        char_pointer++;                                 //Go to the next letter in the word. 
    }
    //If the word is not already stored. 
    if(current_node->word == NULL)
    {
        //Store the word parameter in the word field of current node.
        current_node->word = strdup(word);
        //Increase the size of the trie by one.
        t->size += 1;
    }
}

/*
*   Traverses the trie based on the given word parameter. Once the end of the word 
*   is reached the we simply return the wether or not the word parameter in the final node
*   is nulL. If it is null that means that the word is not in the trie and vice versa. 
*/
int trie_contains(trie* t, char* word)
{
    trie_node* current_node = t->root;  //Pointer to current node.
    char* char_pointer = &word[0];      //Pounter to current character(address of first letter of word)

    while(*char_pointer != '\0')
    {
        int index = *char_pointer - 'a';    //Index of current character.

        //If the current node does not contain the letter we are on.
        if (current_node->children[index] == NULL)
        {
            return 0;
        }

        //If the current node does contain the letter we are on. 
        current_node = current_node ->children[index];  //Enter the child node for that letter.
        char_pointer++;                                 //Go to the next letter in the word. 
    }

    //When we have reached the end of the word, we check the word stored in the last node and return if it is there or not
    return current_node->word != NULL;
}

/*
*   Traverses the trie based on the given prefix parameter. If we are able to reach the end of the 
*   prefix without finding a NULL node that means the word exists in the trie. 
*/
int trie_contains_prefix(trie* t, char* prefix)
{
    trie_node* current_node = t->root;  //Pointer to the current node in the trie 
    char* char_pointer = &prefix[0];    //First letter of the prefix

    while (*char_pointer != '\0')
    {
        int index = *char_pointer - 'a'; //Current index in prefix 
        
        if (current_node->children[index] == NULL)
        {
            return 0;
        }

        //If the current node does contain the letter we are on. 
        current_node = current_node ->children[index];  //Enter the child node for that letter.
        char_pointer++;   
    }
    return 1;   //If we completed the for loop successfully, than the word is found.
}

/*
*   Recursive function to print all words in the trie starting from a given node
*/
void trienode_print(trie_node* node)
{
    if (node->word != NULL)         //If the current node is the end of the word
    {
        printf("%s\n", node->word); //Print that word node. 
    }

    //Iterates over all the children in the node
    for (int i = 0; i < ALPHABET_SIZE; i++) 
    {
        //If the current node is not a word than we call print again. 
        if (node->children[i] != NULL)
        {
            trienode_print(node->children[i]);
        }
    }
}

/*
*   Function that prints all the words in the trie starting from the root node.
*/
void trie_print(trie* t)
{
    if (t == NULL || t->root == NULL) {return;} // Check for null trie or root
    trienode_print(t->root);
}

/*
*   Print all words in a given trie that start with the prefix parameter. 
*/
void trie_print_prefix(trie* t, char* prefix)
{
    trie_node* current_node = t->root;  //Pointer to the current node in the trie 
    char* char_pointer = &prefix[0];    //First letter of the prefix

    while (*char_pointer != '\0')
    {
        int index = *char_pointer - 'a'; //Current index in prefix 
        
        //If a matching child node is not found, we return. 
        if (current_node->children[index] == NULL)
        {
            return;
        }

        //If the current node does contain the letter we are on. 
        current_node = current_node ->children[index];  //Enter the child node for that letter.
        char_pointer++;   
    }

    trienode_print(current_node);
}
/*
*   Recursive function to free a trie from a given node and its children 
*/
void trienode_free(trie_node* node) 
{
    if (node == NULL) { return; }               //Base case 

    for (int i = 0; i < ALPHABET_SIZE; i++)     // Iterate through all children
    { 
        if (node->children[i] != NULL)          //if the children are not NULL
        { 
            trienode_free(node->children[i]);   //Recusively free all the children nodes.
        }
    }
    //If the current node has a word, than we free it
    if (node->word != NULL)                     
    {
        free(node->word);
    }

    // Free the node passed in.
    free(node);
}

/*
*   Function to free the entire trie starting from the root node
*/
void trie_free(trie* t) 
{
    if (t == NULL) { return; } 

    trienode_free(t->root); // Free all nodes starting from the root
    free(t); // Finally, free the trie structure itself
}

