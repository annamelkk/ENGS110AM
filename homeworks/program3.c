//program N3

#include <stdio.h>

int main() {
    // naming the variable
    double num;
    double sum=0; // starting the sum with zero
    // ask the user to input their number
    printf("Give me your number: ");
    scanf("%lf", &num); // reading the input
    
    //case when the number is not in range
    if ( num<1 || num> 1000) {
    printf("Your number is not in supported range, enter a number between 1 and 1000. \n");
    return 1;
    }

    for (int i=1; i<=num; i++)
         {
            if (i % 3 == 0 || i % 5 == 0 ) // condition for divisibility
            sum+=i; // adding i to sum
        }
printf("here is your sum for numbers divisible by 3 or 5, until %.0f: %.0f\n", num, sum);
return 0;
}