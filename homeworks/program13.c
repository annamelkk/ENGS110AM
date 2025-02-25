#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Seed the random number generator with the current time, so that everytime the program is run a new number is generated
    srand(time(0));

    // Generate a random number between 1 and 100
    int randomNumber = rand() % 100 + 1;

    int userGuess;
    int numberOfGuesses = 0;

    printf("Guess a number between 1 and 100: ");

    do {
        scanf("%d", &userGuess);
        numberOfGuesses++;

        if (userGuess > randomNumber) {
            printf("Too high! Try again: ");
        } else if (userGuess < randomNumber) {
            printf("Too low! Try again: ");
        } else {
            printf("Congratulations! You guessed the number in %d attempts.\n", numberOfGuesses);
        }
    } while (userGuess != randomNumber); // do the loop while the user guess in not equal to the number

    return 0;
}