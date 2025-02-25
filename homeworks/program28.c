#include <stdio.h>

// Function to check if one string is a substring of another
int isSubstring(const char *str, const char *sub) {
    int i, j;

    // iterating through the main string
    for (i = 0; str[i] != '\0'; i++) {
        // checking for a match in the substring
        for (j = 0; sub[j] != '\0'; j++) {
            if (str[i + j] != sub[j]) {
                break; // Mismatch, so breaking the inner loop
            }
        }
        if (sub[j] == '\0') {
            return 1; // Substring found
        }
    }

    return 0; // Substring not found
}

int main() {
    char str[100], sub[100];

    // Input the main string and the substring
    printf("Enter the main string: ");
    scanf("%s", str);
    printf("Enter the substring: ");
    scanf("%s", sub);

    // Check if the substring is present in the main string
    if (isSubstring(str, sub)) {
        printf("'%s' is a substring of '%s'.\n", sub, str);
    } else {
        printf("'%s' is NOT a substring of '%s'.\n", sub, str);
    }

    return 0;
}