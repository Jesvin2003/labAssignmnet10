#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definition of Trie Node
struct Trie {
    int count;              // Number of occurrences of a word
    struct Trie *next[26];  // Links to the next 26 nodes
};

// Inserts a word into the trie
void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pTrie = *ppTrie;   // Pointer to the current Trie Node
    if (!pTrie) {                   // If the Trie Node is null
        pTrie = (struct Trie*)calloc(1, sizeof(struct Trie));  // Allocate memory for it
        *ppTrie = pTrie;            // Set the pointer to the new Trie Node
    }
    for (int i = 0; i < strlen(word); i++) {      // Loop through each character in the word
        int index = word[i] - 'a';                // Get the index of the character (0-25)
        if (!pTrie->next[index]) {                // If the link to the next node is null
            pTrie->next[index] = (struct Trie*)calloc(1, sizeof(struct Trie));   // Allocate memory for it
        }
        pTrie = pTrie->next[index];    // Move to the next node
    }
    pTrie->count++;    // Increment the count of the word
}

// Returns the number of occurrences of a word in the trie
int numberOfOccurances(struct Trie *pTrie, char *word) {
    if (!pTrie) return 0;   // If the Trie Node is null, return 0
    for (int i = 0; i < strlen(word); i++) {      // Loop through each character in the word
        int index = word[i] - 'a';                // Get the index of the character (0-25)
        if (!pTrie->next[index]) {                // If the link to the next node is null
            return 0;                             // The word is not in the trie, so return 0
        }
        pTrie = pTrie->next[index];    // Move to the next node
    }
    return pTrie->count;   // Return the count of the word
}

// Deallocates memory used by the trie
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (!pTrie) return NULL;   // If the Trie Node is null, return null
    for (int i = 0; i < 26; i++) {                  // Loop through each link to the next node
        pTrie->next[i] = deallocateTrie(pTrie->next[i]);  // Recursively deallocate memory used by the next node
    }
    free(pTrie);    // Free memory used by the current Trie Node
    return NULL;    // Return null
}

int main(void)
{
    struct Trie *trie = NULL;  // Initialize the trie data structure
    char *pWords[] = {"ucf", "no", "note", "corg"};  // Remove "notaword" as it is not a valid word
    int numWords = sizeof(pWords) / sizeof(char*);
    for (int i = 0; i < numWords; i++) {
        insert(&trie, pWords[i]);  // Insert each word into the trie
    }
    for (int i = 0; i < numWords; i++) {
        printf("%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));  // Print the number of occurrences of each word in the trie
    }
    trie = deallocateTrie(trie);  // Deallocate memory used by the trie
    if (trie != NULL) {
        printf("There is an error in this program\n");
    }
    return 0;
}