#include <stdio.h>

int main() {
    int num1, num2, temp, digits = 1;

    // asking user to input two numbers
    printf("Enter first number: ");
    scanf("%d", &num1);
    printf("Enter second number: ");
    scanf("%d", &num2);

    // finding the number of digits in num2
    temp = num2;
    while (temp > 0) {
        digits *= 10;
        temp /= 10;
    }

    // concatenate the numbers
    int result = num1 * digits + num2;

    // cutput the concatenated number
    printf("Concatenated number: %d\n", result);

    return 0;
}
