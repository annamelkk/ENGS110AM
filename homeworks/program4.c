// program N4
#include <stdio.h>

int main () {
    int last_digit;
    int number;
    int sum=0;
    printf("Print your number: \n");
    scanf("%d", &number);
    
    // what if the number is neative?
    if (number<0){
        number=-number;
    }
    
    while (number !=0 ) {
    last_digit= number%10; //extracting digiits
    number=number/10; //integer division for the next digit
    sum += last_digit;
    }
    printf("your sum is %d \n", sum);
    return (0);
}