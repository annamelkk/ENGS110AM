#include <stdio.h>
#include <time.h>
#include <unistd.h> // for sleep()

/* 
For simple turnstile wihtout FSM without any error detection 2 possible
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

void Transition(enum Event e) {
    static enum State s = Locked;
    static time_t unlock_time = 0;
    
    // checking if the initial state is unlocke
    if (s ==Unlocked && difftime(time(NULL), unlock_time) > 10) {
    s = Locked;
    Lock();
    TimeoutMsg();
    }
    
    
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

	Transition(Coin); //unlock
	sleep(5); // assuming the system has sensors that detected passing
	Transition(Pass);


	Transition(Coin);
	sleep(12); // open for more than 10 seconds, no one passed - time out
	

}

