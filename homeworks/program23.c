#include <stdio.h>

// using bubblesort algorithm for simpler code
void bubbleSort(int arr[], int N, int ascending) {
    int i, j, temp;
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - i - 1; j++) {
            // Compare adjacent elements based on the order specified
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1])) {
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int N, i, order;
    
    // Asking user to input the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &N);
    
    int arr[N];

    // Asking user to input N integers for the array
    printf("Enter %d integers (use space between each number): \n", N);
    for (i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // Asking user for sorting order: 1 for ascending, 0 for descending
    printf("Enter 1 to sort in ascending order, 0 for descending order: ");
    scanf("%d", &order);

    // Sort the array based on user input
    bubbleSort(arr, N, order);

    // Output the sorted array
    printf("Sorted array: ");
    for (i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
