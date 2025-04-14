#include <stdio.h>
#include <time.h>
#include <unistd.h> // for sleep()

/* 
For simple turnstile FSM  without any error detection 2 possible states
    are enough to describe the machine

By default the starting state is Locked, when a coin is inserted the turnstile unlocks, and the Thankyou() function is called, when the user passes the turnstile the system is locked again
*/

enum State {Locked, Unlocked}; // the two states
enum Event {Pass, Coin}; // actions for swtching the state


void Unlock() { printf("Turnstile unlocked.\n"); }
void Lock() { printf("Turnstile locked.\n"); }
void ThankYou() { printf("Thank you for the coin.\n"); }
void Alarm() { printf("ALARM! Cannot pass, still locked.\n"); }
void TimeoutMsg() {printf("Time out! Automatically locking. \n"); }





// funtion to check if the turnstile has been left unlocked for too long
void CheckTimeout(enum State* s, time_t* unlock_time)
{
	if (*s == Unlocked && difftime(time(NULL), *unlock_time) > 10) 
	{
		*s = Locked;
		Lock();
		TimeoutMsg();
	}
}

// FSM transition logic
void Transition(enum Event e) {
    static enum State s = Locked;
    static time_t unlock_time = 0;


    
    CheckTimeout(&s, &unlock_time);
    
    switch (s) {
        case Locked:
            switch (e) {
                case Coin:
                    s = Unlocked;
                    Unlock();
                    ThankYou();
		    unlock_time = time(NULL); // start the timeout clock
                    break;
                case Pass:
                    Alarm();
                    break;
            }
            break;

        case Unlocked:
            switch (e) {
                case Pass:
                    s = Locked;
                    Lock();
                    break;
                case Coin:
                    ThankYou(); // already unlocked
                    break;
            }
            break;
    }
}

// Test function

int main() {
    char input;
    printf("Turnstile FSM Simulation Started.\n");

    while (1) {
        printf("\nEnter event (c = coin, p = pass, q = quit): ");
        scanf(" %c", &input);

        if (input == 'q') break;
        else if (input == 'c') {
		Transition(Coin);
		sleep(5); // delay to simulate real-time behavior
		printf("Time Passed, locking!");
			   }
        else if (input == 'p') { 
	
		Transition(Pass);
	
	}
	else printf("Invalid input. Please enter 'c', 'p', or 'q'.\n");

    }

    printf("Simulation ended.\n");
    return 0;
}
