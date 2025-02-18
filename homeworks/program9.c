// program N9
#include <stdio.h>

int main() {
    int number;
    printf("Input your number to check if it is a power of 2: \n");
    scanf("%d", &number);
    
    if (number < 1) {
        printf("Only positive numbers can be powers of 2.\n");
        return 1;  // exit the program early
    }
    // entering while loop; 
    //checking whether the number is even first
    while (number % 2 == 0) {
        number = number / 2;
    }
        
    if (number == 1) {
        printf("Your number is a power of 2!!\n");
    } else {
        printf("Your number is not a power of 2.\n");
    }
    
    return 0;  
}
