#include <stdio.h>

int main() {
    // defining the array 
    int N;
    printf("Enter the number of elements: ");
    scanf("%d", &N);
    
    int arr[N];
    int i;
    int isAscending = 1;
    int isDescending = 1;

    // asking user to input N integers for the array
    printf("Enter %d integers (use space between each number): \n", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // boolean flags are set to false whenever a violation of order is detected
    for (i = 1; i < N; i++) {
        if (arr[i] < arr[i - 1]) {
            isAscending = 0;
        }
        if (arr[i] > arr[i - 1]) {
            isDescending = 0;
        }
    }

    // Output result
    if (isAscending) {
        printf("Yes, ascending.\n");
    } else if (isDescending) {
        printf("Yes, descending.\n");
    } else {
        printf("No.\n");
    }

    return 0;
}
