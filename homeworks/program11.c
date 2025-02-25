#include <stdio.h>

int main() {
    int N;

    // height of the triangle
    printf("Enter the height of the triangle (N): ");
    scanf("%d", &N);

    // drawinf the first triangle (right angle on the left)
    printf("First Triangle:\n");
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    // drawing the second triangle (right angle on the right)
    printf("\nSecond Triangle:\n");
    for (int i = 1; i <= N; i++) {
        // Print spaces for alignment
        for (int j = 1; j <= N - i; j++) {
            printf(" ");
        }
        // Print stars
        for (int j = 1; j <= i; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}