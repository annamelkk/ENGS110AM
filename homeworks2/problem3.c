// some notes i have for this program
// for c string is essentially an array of characters and its end is marked by \0
// we manipulate arrays using pointers

#include <stdio.h>

// the function takes a pointer to a character as input
void reverse(char *str) {
    if (str == NULL) {
        return; //  invalid input
    }

    char *start = str;  // pointer to the beginning of the string
    char *end = str;    // pointer to the end of the string (initially to the same place as start)

    // moving 'end' pointer until the null charatcter (\0) and then stepping back one position to point at last charcter 
    while (*end != '\0') {
        end++;
    }
    end--; // move back one step to point to the last character of the string

    // while start is before end the roop will run
    while (start < end) {
        char temp = *start; // defining a temporary dump variable to store start
        *start = *end;      // copy the character at 'end' to 'start'
        *end = temp;        // copy 'temp' (original 'start' value) to 'end'

        // Move pointers toward the center
        start++;
        end--;
    }
}

int main() {
    char str[] = "hello! !olleh tricky!"; //defining the string 
    printf("Original String: %s\n", str);

    reverse(str); // call function to reverse the string

    printf("Reversed String: %s\n", str);
    return 0;
}

