#include <stdio.h>
#include <stdlib.h>

int main() {
    // defining the filename pointer  as the source file
    char *filename = "problem1.txt"; // i created a txt file with some text for this porgram
    FILE *file = fopen(filename, "r"); // Open the file in read mode

    // checking whther fopen fails, if so exit with error message
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1; 
    }

    int ch; // variable to store each character read from the file
    int row = 1, col = 0; // tracking the line number (row) and char position (column) 
    printf("Locations of '{' and '}':\n");

    // entering while loop to read one char at a time
    while ((ch = fgetc(file)) != EOF) { // eof marks the end of the file
        col++;  // incrementing coclumns for each char found

        // check if character is an opening '{' or closing '}'
        if (ch == '{' || ch == '}') {
            printf("Character '%c' found at Row: %d, Column: %d\n", ch, row, col);
        }

        // move to the next lines
        if (ch == '\n') {
            row++;  
            col = 0; // reset column count since a new line starts from column 1
        }
    }

    // close the file after reading
    fclose(file);

    return 0; 
}

