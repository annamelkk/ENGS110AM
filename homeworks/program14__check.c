#include <iostream>

int main() {
    int low = 1, high = 100, guess;
    char response;
    
    std::cout << "Think of a number between 1 and 100, and I will try to guess it!" << std::endl;
    
    while (low <= high) {
        guess = (low + high) / 2;
        std::cout << "Is your number " << guess << "? (Enter 'h' for too high, 'l' for too low, 'c' for correct): ";
        std::cin >> response;
        
        if (response == 'c') {
            std::cout << "I guessed your number!" << std::endl;
            break;
        } else if (response == 'h') {
            high = guess - 1;
        } else if (response == 'l') {
            low = guess + 1;
        } else {
            std::cout << "Invalid input. Please enter 'h', 'l', or 'c'." << std::endl;
        }
    }
    
    return 0;
}
