
//notes 
// for this program we must replace each sequence of repeated characters
// with the character itself AND the count of its occurences

#include <stdio.h>
#include <string.h>

void compress(char *str) {
    if (str == NULL || *str == '\0') {
        return; // Handle NULL or empty string case
    }

    char *read = str;   // traverses the original string
    char *write = str;  // writes the compressed characters back into the SAME string

    while (*read != '\0') { // start reading
        char currentChar = *read;  
        int count = 0;    // initialize the count of current character

        // Count occurrences of the current character
        while (*read == currentChar) {
            count++; // adding count
            read++; // move to the next character
        }

        // writing the character back into the string
        *write = currentChar;
        write++;

        // write count as characters (convert number to string)
        char countStr[11]; // Buffer to store the number as a string
        sprintf(countStr, "%d", count); // converting integer count to string

        char *countPtr = countStr; // pointer to traverse countStr
        while (*countPtr) {  // copy countstr to write
            *write = *countPtr;
            write++;
            countPtr++;
        }
    }

    *write = '\0'; // ensure the new string is null-terminated
}

int main() {
    char str[50] = "aaabbc"; // Input string (buffer size must be enough)
    printf("Original String: %s\n", str);

    compress(str); // Call function to compress the string

    printf("Compressed String: %s\n", str);
    return 0;
}

