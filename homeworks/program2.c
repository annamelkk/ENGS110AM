//program N2

#include <stdio.h>

int main() {
    // naming the grade variable
    double num;
while (1) {
    // ask the user to input their grade
    printf("Give me your grade: ");
    scanf("%lf", &num); // reading the input
if (num == -1) {
    printf("exiting the program... \n" );
    break;
}
    
if (num<0 || num > 100) {
    printf("there is no such grade.\n");
    continue;
}

    // funtction to determine the letter
    if (num >= 0 && num <= 59) {
        printf("you got F :(\n");
    } else if (num >= 60 && num <= 69) {
        printf("yout grade is D\n");
    } else if (num >= 70 && num <= 79) {
        printf("yout grade is C\n");
    } else if (num >= 80 && num <= 89) {
        printf("yout grade is B\n");
    } else if (num >= 90 && num <= 100) {
        printf("WOW your grade is A !\n");
    }
}
    return 0;
}