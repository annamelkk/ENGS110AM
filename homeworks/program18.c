#include <stdio.h>
#include <string.h>
#include <math.h>

int binaryToDecimal(char binary[]) {
    int decimal = 0;
    int length = strlen(binary);


    // Process each character of the binary string
    for (int i = 0; i < length; i++) {
        // Convert each character to integer and multiply by the corresponding power of 2
        if (binary[i] == '1') {
            decimal += pow(2, length - i - 1);  // Equivalent to (2^(length-i-1))
        } else if (binary[i] != '0') {
            // If any character other than '0' or '1' is printed, it's invalid
            printf("Invalid binary number! The input contains non-binary digits.\n");
            return -1;  // Return -1 to indicate an error
        }
    }

    return decimal;
}

int main() {
    char binary[65];  // Array to store binary input (up to 64 bits)

    printf("Enter a binary number: ");
    scanf("%s", binary);

    // Convert binary to decimal
    int decimal = binaryToDecimal(binary);

    printf("Decimal equivalent: %d\n", decimal);

    return 0;
}
