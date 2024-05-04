#ifndef TRIENODE_H
#define TRIENODE_H

#define ALPHABET_SIZE 26

typedef struct trie_node
{
    char data;
    char* word;
    struct trie_node* children[ALPHABET_SIZE];
} trie_node;

typedef struct
{
    trie_node* root;
    int size;
} trie;

trie_node* trienode_create(char c);
trie* trie_create();
void trie_insert(trie* t, char* word);
int trie_contains(trie* t, char* word);
int trie_contains_prefix(trie* t, char* prefix);
void trie_print(trie* t);
void trie_print_prefix(trie* t, char* prefix);
void trie_free(trie* t);

#endif
