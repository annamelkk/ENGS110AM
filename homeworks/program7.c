// program N7
#include <stdio.h>

int main() {
    int number;
    int last_digit;
    int reversed=0;
    printf("enter your number:");
    scanf("%d", &number);
    
    int original_number = number;
    
    if (number<0){
        number=-number;
    }
    
    while (number != 0){
        last_digit=number % 10;
        number = number /10;
        reversed = (reversed*10)+last_digit;
    }
    if (reversed == original_number) {
        printf("Your number %d is palindrome!\n", original_number);
    } else {
        printf("Your number is not palindrome \n");
    }
    
    return 0;
}