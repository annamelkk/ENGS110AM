#include <stdio.h>

int main() {
    int arr[10];
    int N, i, found = 0;

    // Step 1: asking user to input 10 integers for the array
    printf("Enter 10 integers  (use space between each number): \n");
    for (i = 0; i < 10; i++) {
        scanf("%d", &arr[i]);
    }

    // Step 2: asking user to choose the integer to be reremoved from array
    printf("Enter the integer to remove: \n ");
    scanf("%d", &N);

    // Step 3: Search for the first occurrence of N
    for (i = 0; i < 10; i++) {
        if (arr[i] == N) {
            // Remove the element by shifting the following elements left
            for (int j = i; j < 9; j++) {
                arr[j] = arr[j + 1];
            }
            arr[9] = 0;  // Set the last element to 0 after shifting
            found = 1;
            break;  // Exit the loop after the first occurrence is removed
        }
    }

    // Step 4: If N was found and removed, print the updated array
    if (found) {
        printf("Array after removing %d:\n", N);
    } else {
        printf("%d not found in the array.\n", N);
    }

    // Print the final array
    for (i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
