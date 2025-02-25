#include <stdio.h>

int main() {
    // defining the array and initializing the sum with 0
    int N;
    printf("Enter the number of elements: ");
    scanf("%d", &N);
    
    int arr[N];
    int sum = 0;
    int i;

    // asking user to input N integers for the array
    printf("Enter %d integers (use space between each number): \n", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
        sum += arr[i]; // incrementing the sum with each number
    }

    printf("Sum of the array: %d ", sum);

    printf("\n");

    return 0;
}
