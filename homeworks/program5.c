//program N5

#include <stdio.h>

int main() {
    // naming the variables
    int num;
    double inverse; 
    // ask the user to input their number
    printf("Give me your number: ");
    scanf("%d", &num); // reading the input
    
    if (num == 0) {
        printf("no inverse \n");
    } else {
        inverse = 1.0 / num;
        printf("inverse of %d: %.6f \n", num, inverse);
    }


return 0;
}