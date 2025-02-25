#include <stdio.h>

int main() {
    int low = 1, high = 100;
    int computerGuess;
    char userResponse; // char variable becuase the user will type in a letter, not a number 

    printf("Think of a number between 1 and 100. I will guess it!\n");

    while (low <= high) {
        computerGuess = (low + high) / 2; // Binary search approach
        printf("Is your number %d? (Enter 'h' if too high, 'l' if too low, 'c' if correct): ", computerGuess);
        scanf(" %c", &userResponse);

        if (userResponse == 'h') {
            high = computerGuess - 1; // Adjusting the upper bound
        } else if (userResponse == 'l') {
            low = computerGuess + 1; // Adjusting the lower bound
        } else if (userResponse == 'c') {
            printf("I guessed your number in %d attempts!\n", (low + high) / 2);
            break;
        } else {
            printf("Invalid input. Please enter 'h', 'l', or 'c'.\n");
        }
    }

    return 0;
}