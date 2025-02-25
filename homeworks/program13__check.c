#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0)); 
    int target = std::rand() % 100 + 1;
    int guess;
    int attempts = 0;
    
    std::cout <<"Guess the number!" << std::endl;
    
    do {
        std::cout <<"Enter your guess: ";
        std::cin >> guess;
        attempts++;
        
        if (guess > target) {
            std::out << "Too high!." << std::endl;
        } else if (guess < target) {
            std::out << "Too low!." << std::endl;
    } while (guess != target);
    
    std::out <<You guessed the number in" << attempts << "attempts." <<std::endl;
    
    return 0;
}