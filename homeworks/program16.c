#include <stdio.h>

int main() {
    int num;
    int occurrences[10] = {0}; // array to count occurrences of numbers 1-10

    printf("Enter numbers between 1 and 10 (enter -1 to stop):\n");
    
    while (1) {
        scanf("%d", &num);
        if (num == -1) {
            break; // exiting when -1 is entered as stated
        }
        if (num >= 1 && num <= 10) {
            occurrences[num - 1]++; // Increment count for the entered number
        } else {
            printf("Invalid input, please enter a number between 1 and 10.\n");
        }
    }
    
    printf("Number of occurrences of each number:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d: %d times\n", i + 1, occurrences[i]);
    }
    
    return 0;
}