#include <stdio.h>

// Function to reverse a string in-place
void reverseString(char *str) {
    if (str == NULL) {
        return; // Handle null pointer (invalid input)
    }

    char *start = str;  // Pointer to the beginning of the string
    char *end = str;    // Pointer to the end of the string

    // Move 'end' pointer to the last character (before null terminator)
    while (*end != '\0') {
        end++;
    }
    end--; // Move back one step to point to the last character of the string

    // Swap characters from start and end moving toward the middle
    while (start < end) {
        char temp = *start; // Store the character at 'start'
        *start = *end;      // Copy the character at 'end' to 'start'
        *end = temp;        // Copy 'temp' (original 'start' value) to 'end'

        // Move pointers toward the center
        start++;
        end--;
    }
}

int main() {
    char str[] = "Hello, World!"; // Define a modifiable string
    printf("Original String: %s\n", str);

    reverseString(str); // Call function to reverse the string

    printf("Reversed String: %s\n", str);
    return 0;
}

