#include <stdio.h>

int main() {
    int N;
    int M;
    
    // asking user to input the size of the array
    printf("enter the number of elements (N):");
    scanf("%d", &N);
    
    int sequence[N];
    
    // asking user to input the elements
    printf("Enter the sequence of %d numbers: \n", N);
    for (int i=0; i<N; i++) {
        scanf("%d", &sequence[i]);
    }
    
        // the position of the element to delete (M)
    printf("Enter the position of the element to delete (M): ");
    scanf("%d", &M);
    
    // M must correspond to the number of elements in the sequence
    if (M < 1 || M > N) {
        printf("Invalid position! M must be between 1 and %d.\n", N);
        return 1; // Exit the program 
    }
    
     // Shift elements to the left starting from the M
    for (int i = M - 1; i < N - 1; i++) {
        sequence[i] = sequence[i + 1];
    }

    // Decrease the size of the sequence
    N--;

    // Output the updated sequence
    printf("Updated sequence after deleting the %d-th element:\n", M);
    for (int i = 0; i < N; i++) {
        printf("%d ", sequence[i]);
    }
    printf("\n");

    return 0;
}