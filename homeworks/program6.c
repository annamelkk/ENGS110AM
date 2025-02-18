#include <stdio.h>
#include <math.h> //including math library to use the square root function

int main() {
    int number; //declaring the variable
    printf("Enter a number to check if it is prime: ");
    scanf("%d", &number);

    if (number < 2) {
        printf("0 and 1 are not prime!\n");
        return 1;
    }

    if (number == 2) {
        printf("2 is the only even prime number.\n");
        return 0;
    }

    if (number % 2 == 0) {
        printf("Even numbers greater than 2 are not prime.\n");
        return 1;
    }

    for (int i = 3; i <= sqrt(number); i += 2) {
        if (number % i == 0) {
            printf("Your number %d is not prime.\n", number);
            return 1; // exiting the program as soon as a divisor is found
        }
    }

    // if the loop completes then the number is prime
    printf("Your number %d is prime.\n", number);
    return 0;
}