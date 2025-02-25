#include <stdio.h>

int main() {
    // defining the original and reversed arrays first
    int N;
    printf("Enter the number of elements: ");
    scanf("%d", &N);
    
    int arr[N];
    int reversed[N];
    int i, j;

    // asking user to input N integers for the array
    printf("Enter %d integers (use space between each number): \n", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }
    
    // for each j element of reversed the i element is assigned in reversed order inputted by the user
    for (i = 0, j = N - 1; i < N; i++, j--) {
        reversed[j] = arr[i];
    }

    // Printing the reversed array
    printf("Reversed array: ");
    for (i = 0; i < N; i++) {
        printf("%d ", reversed[i]);
    }
    printf("\n");

    return 0;
}
