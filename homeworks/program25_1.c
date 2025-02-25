#include <stdio.h>

int main() {
    int N, M, K;

    // asking user to input the array size
    printf("Enter the number of elements (N): ");
    scanf("%d", &N);

    int sequence[N + 1]; // creating space for N + 1 elements

    // asking user to define the sequence
    printf("Enter the sequence of %d numbers:\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &sequence[i]);
    }

    // the position and number to be inserted
    printf("Enter the position of the element to add (M): ");
    scanf("%d", &M);
    printf("Enter the number to insert (K): ");
    scanf("%d", &K);

    // Validate M (must be between 1 and N + 1)
    if (M < 1 || M > N + 1) {
        printf("Invalid position! M must be between 1 and %d.\n", N + 1);
        return 1; // Exit the program 
    }

    // Shift elements to the right starting from the M-th position
    for (int i = N; i >= M; i--) {
        sequence[i] = sequence[i - 1];
    }

    // insert k at the M-th position
    sequence[M - 1] = K;

    // increasing the size since a new element is added
    N++;

    // Output the updated sequence
    printf("Updated sequence after inserting %d at position %d:\n", K, M);
    for (int i = 0; i < N; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}