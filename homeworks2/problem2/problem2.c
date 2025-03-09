#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024  // Maximum length of a line
#define MAX_COLUMNS 100  // Maximum number of columns in the CSV

void search_csv(const char *filename, int column, const char *search_value);

int main() {
    char filename[100];  
    printf("Enter the CSV file name: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r"); // Open file in read mode
    if (file == NULL) {
        printf("Error: Unable to open file %s\n", filename);
        return 1; // Exit with error
    }

    char line[MAX_LINE];  
    fgets(line, sizeof(line), file);  // Read the header line
    fclose(file);

    printf("CSV Header: %s", line);

    int column;
    printf("Enter the column number (starting from 1): ");
    scanf("%d", &column);

    char search_value[100];  
    printf("Enter the value to search: ");
    scanf("%s", search_value);

    // Call function to search the CSV file
    search_csv(filename, column - 1, search_value); 

    return 0;
}

// Function to search for a value in a given column of a CSV file
void search_csv(const char *filename, int column, const char *search_value) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    char line[MAX_LINE];
    fgets(line, sizeof(line), file);  // Skip the header

    int found = 0;  // Flag to check if any row matched

    while (fgets(line, sizeof(line), file)) {
        char *fields[MAX_COLUMNS];  
        int col_count = 0;

        char *token = strtok(line, ",");  // Split line using ","
        while (token != NULL && col_count < MAX_COLUMNS) {
            fields[col_count++] = token;  
            token = strtok(NULL, ",");
        }

        if (column >= col_count) {
            printf("Error: Column number is out of range.\n");
            break;
        }

        // Remove newline character if present
        fields[column][strcspn(fields[column], "\r\n")] = 0;

        // Compare with search value
        if (strcmp(fields[column], search_value) == 0) {
            found = 1;
            printf("Match found: ");
            for (int i = 0; i < col_count; i++) {
                printf("%s ", fields[i]);
            }
            printf("\n");
        }
    }

    if (!found) {
        printf("No matching rows found.\n");
    }

    fclose(file);
}

