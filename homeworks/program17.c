// program N17
#include <stdio.h>

void decimalToBinary(int num, int bits) {
    if (num < 0) {
        // handling the cae of negative numbers
        num = (1 << bits) + num;  // bitewise left shift to get the negative number into its 2's complement representation
    }

    // Print binary representation
    for (int i = bits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1;  // shift the bit to the right and mask it to get either 0 or 1
        printf("%d", bit);
    }
    printf("\n");
}

int main() {
    int num, bits = 4;  // Fixed number of bits (4 bits)

    printf("Enter a number: ");
    scanf("%d", &num);

    printf("Binary representation of %d in %d bits: ", num, bits);
    decimalToBinary(num, bits);

    return 0;
}
