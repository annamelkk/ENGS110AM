#include <stdio.h>
#include <stdlib.h>

int main() {
    // Define the filename as the source file
    char *filename = "problem1.txt";  // __FILE__ is a predefined macro that stores the filename of the current source file
    FILE *file = fopen(filename, "r"); // Open the file in read mode

    // Check if file opened successfully
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1; // Exit the program with an error code
    }

    int ch;                // Variable to store each character read from the file
    int row = 1, col = 0;  // Track row (line number) and column (character position)
    
    printf("Locations of '{' and '}':\n");

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF) {
        col++;  // Increment column count for each character read

        // Check if character is an opening '{' or closing '}'
        if (ch == '{' || ch == '}') {
            printf("Character '%c' found at Row: %d, Column: %d\n", ch, row, col);
        }

        // Handle new lines
        if (ch == '\n') {
            row++; // Move to the next line
            col = 0; // Reset column count
        }
    }

    // Close the file after reading
    fclose(file);

    return 0; // Indicate successful execution
}

