//program N10

#include <stdio.h>

int main() {
    int N, M;
    char ch;
    
    printf("Enter number of rows (N): ");
    scanf("%d", &N);
    
    printf("Enter number of columns (M): ");
    scanf("%d", &M);
    
    printf("Enter the character to draw the rectangle: ");
    scanf(" %c", &ch);  // 
    
    // Draw the rectangle
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (i == 1 || i == N) {
                // printing full row of characters on the first and last row
                printf("%c", ch);
            } else {
                // printing character at the beginning and end of the row
                if (j == 1 || j == M) {
                    printf("%c", ch);
                } else {
                    // Print space in between
                    printf(" ");
                }
            }
        }
        printf("\n"); // move to the next line
    }
    
    return 0;
}