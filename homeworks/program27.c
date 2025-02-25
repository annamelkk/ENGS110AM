#include <stdio.h>

// Function to check if two strings are anagrams
int anagrams(const char *word1, const char *word2) {
    int count1[26] = {0}; // using two arrays to count the freq of each char in the two words
    int count2[26] = {0}; 

    // Calculate frequency of each character the first word
    for (int i = 0; word1[i] != '\0'; i++) {
        if (word1[i] >= 'a' && word1[i] <= 'z') {
            count1[word1[i] - 'a']++;
        } else if (word1[i] >= 'A' && word1[i] <= 'Z') {
            count1[word1[i] - 'A']++;
        }
    }

    // Calculate frequency of each character in the second word
    for (int i = 0; word2[i] != '\0'; i++) {
        if (word2[i] >= 'a' && word2[i] <= 'z') {
            count2[word2[i] - 'a']++;
        } else if (word2[i] >= 'A' && word2[i] <= 'Z') {
            count2[word2[i] - 'A']++;
        }
    }

    // Compare frequency counts
    for (int i = 0; i < 26; i++) {
        if (count1[i] != count2[i]) {
            return 0; // if the frequencies of the charaters are not the same then the words are not anagrams
        }
    }

    return 1; // words are anagrams
}

int main() {
    char word1[100], word2[100];

    // Input two words/strings
    printf("Enter the first word: ");
    scanf("%s", word1);
    printf("Enter the second word: ");
    scanf("%s", word2);

    // Check if they are anagrams
    if (anagrams(word1, word2)) {
        printf("'%s' and '%s' are anagrams.\n", word1, word2);
    } else {
        printf("'%s' and '%s' are NOT anagrams.\n", word1, word2);
    }


    return 0;
}