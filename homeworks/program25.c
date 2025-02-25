#include <stdio.h>

int main() {
    int N, K;

    //  // asking user to input the array size
    printf("Enter the number of elements (N): ");
    scanf("%d", &N);

    int sequence[N + 1]; // creating space for N + 1 elements

    //asking user to define the sequence
    printf("Enter the sequence of %d numbers:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &sequence[i]);
    }

    // number to be insterted
    printf("Enter the number to insert at the beginning (K): ");
    scanf("%d", &K);

    // shift all elements one position to the right
    for (int i = N; i > 0; i--) {
        sequence[i] = sequence[i - 1];
    }

    // insert K at the beginning
    sequence[0] = K;

    // increasing the size since a new element is added
    N++;

    // Output the updated sequence
    printf("Updated sequence after inserting %d at the beginning:\n", K);
    for (int i = 0; i < N; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}