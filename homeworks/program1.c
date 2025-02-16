//program N1
#include <stdio.h>

int main() {
    // first i defined my parameters
   double num1, num2, result;
   char op;
   
   // asking user to give number to operate with
   printf ("Test my math genius:" );
   
   // defining the order of characters to be inputted for the user
   if (scanf("%lf %c %lf", &num1, &op, &num2) !=3) {
       printf("nono, im not programmed that way enter num (operation) num \n");
       return 1;
   }
   
   //the calculation 
   switch (op) {
       case '+':
           result= num1 + num2;
           printf("%.1lf %c %.1lf = %.1lf\n", num1, op, num2, result);
        break;
        case '-': 
            result = num1 - num2;
            printf("%.1lf %c %.1lf = %.1lf\n", num1, op, num2, result);
        break;
        case '*':
        result = num1 * num2;
        printf("%.1lf %c %.1lf = %.1lf\n", num1, op, num2, result);
        break;
        case '/':
        if (num2 == 0) {
            printf("YOU CANT DIVIDE BY 0\n");
            } else {
            result = num1 / num2;
            printf("%.3lf %c %.3lf = %.3lf\n", num1,op, num2, result);
            }
        break;
        default:
        return 1;
        }
   
    return 0;
}