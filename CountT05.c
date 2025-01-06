/*
 * Ex #1: Counting amount of max numbers under 5 seconds.
 * ==========================================================
 * Written by: Jacob Bondar.
 * 
 * This program simulates a counting game where the user has 5
 * seconds to input numbers as many as he can until the alarm is 
 * trigged and sends a signal.
 * This program tracks the maximum number of inputs given threw the 10 
 *  rounds. Each round starts when the users press enter.
 * 
 * input: User enters an enter and then the maximum numbers he can in 
 *  5 seconds.

 * output: The maximum number of inputs given in the whole rounds.
 * 
*/

//-------------- include section ---------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

//-------------- Global section ----------------------------------------
bool stop = false;

//---------prototipes---------------------------------------------------
void catch_signal(int sig);
int calculating_the_max_inserts();

//-------------- main --------------------------------------------------
int main()
{
    struct sigaction action;
    
    action.sa_handler = catch_signal;
    sigfillset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGALRM, &action, NULL);
   
    int max_counter = calculating_the_max_inserts();
    printf("%d\n", max_counter);

    exit(EXIT_SUCCESS);
}

//---------------------------------------------------------------------

// The function changes the global variable 'stop' to true.
// The function recieves the signal number.
// The function return void, but it changes the global varibale.
void catch_signal(int sig)
{
    stop = true;
}

//---------------------------------------------------------------------

// The function runs 10 times, and saves the highest count of input 
//  values by the user.
// The function recieves nothing.
// The function returns the highest count of input values by the user.
int calculating_the_max_inserts()
{
    int counter = 0, max_counter = 0, num;
    char c;

    for (int loop = 0; loop < 10; loop++)
    {
        counter = 0;
        stop = false;
        puts("Hit enter when ready");
        scanf("%c", &c);

        alarm(5);
        while (true)
        {
            scanf("%d", &num);
            if (stop) break;
            counter++;
        }

        if (counter > max_counter) max_counter = counter;
    }
    return max_counter;
}
