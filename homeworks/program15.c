#include <stdio.h> 

int main() { //initializing the number and min and max values
    int num;
    int min;
    int max;
    
    printf("Enter 10 numbers (use space between each number): \n"); // asking user to print 10 numbers
    scanf("%d", &num);
    max = num;
    min = num; 
    // both min and max are initialized with the first input number
    
    for (int i=1; i<10; i++) { //using for loop, starting from the second number
        scanf("%d", &num);
        if (num < min) {
            min = num;
        }
            if (num > max) {
            max = num;
        }
    }
    
    
    printf("Minimum number: %d\n", min);
    printf("Maximum number: %d\n", max);

    return 0;
    
}