#include <stdio.h>
#include <math.h>
int main() {
	int number;
	printf("print your number to check if it is prime");
	scanf("%d", &number);
	if (number < 2 ) {
		printf("0 and 1 are not prime!");
	};
	if (number == 2){
		printf("2 is the only even prime number");
	};
	if (number % 2 == 0) {
		printf("even numbers greater than 2 are not prime.");
	};

	for (int i=3; i<=sqrt(number); i+=2){
		if (number % i == 0) {
		printf("Your number %d is prime \n", number);
		}
	return 1;
		}
}
