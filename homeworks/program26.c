#include <stdio.h>

// Function to convert a string to uppercase
void uppercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // converting to uppercase
        }
    }
}

// Function to convert a string to lowercase
void lowercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32; // converting to lowercase
        }
    }
}

int main() {
    char word[100]; // word containing maximum 100 characters

    // Input the word/string
    printf("Enter a word/string: ");
    scanf("%s", word);

    // Convert to uppercase
    uppercase(word);
    printf("Uppercase: %s\n", word);

    // Convert to lowercase
    lowercase(word);
    printf("Lowercase: %s\n", word);

    return 0;
}