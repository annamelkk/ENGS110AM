#include <stdio.h>

int main() {
    int N;
    
    // Input the height (and base) of the triangle
    printf("Enter the height of the triangle: ");
    scanf("%d", &N);
    
    // Loop through each row of the triangle
    for (int i = 1; i <= N; i++) {
        // Print spaces before the stars
        for (int j = 1; j <= N - i; j++) {
            printf(" ");
        }
        
        // Print stars for the current row
        for (int k = 1; k <= (2 * i - 1); k++) {
            printf("*");
        }
        
        // Move to the next row
        printf("\n");
    }
    
    return 0;
}
