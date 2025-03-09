#include <stdio.h>
#include <string.h>

// Function to compress a string in-place
void compressString(char *str) {
    if (str == NULL || *str == '\0') {
        return; // Handle NULL or empty string case
    }

    char *read = str;   // Pointer to read original characters
    char *write = str;  // Pointer to write compressed characters

    while (*read != '\0') {
        char currentChar = *read;  // Store the current character
        int count = 0;             // Initialize the count of current character

        // Count occurrences of the current character
        while (*read == currentChar) {
            count++;
            read++; // Move to the next character
        }

        // Write character
        *write = currentChar;
        write++;

        // Write count as characters (convert number to string)
        char countStr[10]; // Buffer to store the number as a string
        sprintf(countStr, "%d", count); // Convert number to string

        char *countPtr = countStr; // Pointer to traverse countStr
        while (*countPtr) {  // Write each digit of count
            *write = *countPtr;
            write++;
            countPtr++;
        }
    }

    *write = '\0'; // Ensure the new string is null-terminated
}

int main() {
    char str[50] = "aaabbc"; // Input string (buffer size must be enough)
    printf("Original String: %s\n", str);

    compressString(str); // Call function to compress the string

    printf("Compressed String: %s\n", str);
    return 0;
}

