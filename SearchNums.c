/*
 * Ex #2: Search Amount Of Random Numbers.
 * ==========================================================
 * Written by: Jacob Bondar.
 *
 * This program simulates a search task between two processes using a
 * random number generator. It checks which numbers we got with the
 * following pattern:
 * - Numbers greater than or equal to 95 increase the 'counter_above'.
 * - Numbers less than 55 increase the 'counter_less'.
 * - Prime numbers.
 *
 * The program forks into two processes: the parent and the child. Each
 * process performs these tests independently and sends a signal to the
 * other process, once a winning condition is met 
 * (either 'counter_above' reaches 10, 'counter_less' reaches 100, 
 * or 50 prime numbers are found).
 *
 * The program uses signals (SIGUSR1 and SIGUSR2) to communicate between
 * the processes. The winner sends a signal to the other process.
 *
 * Input: No input.
 *
 * Output:
 * - The number of counter_above and counter_less of the process that
 *   recieved one of the signals.
 * - A message indicating which process wins, loses, or counts prime
 *   numbers and congrats! or thanks! depends on which process finished
 *   first.
 *
 */

 //-------------- include section --------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>

//-------------- Global section ----------------------------------------
int counter_above = 0;
int counter_less = 0;


//---------prototipes---------------------------------------------------
bool is_prime(int num);
void catch_sigusr(int sig_num);
void checking_fork(pid_t child);
bool checking_counters(pid_t child, int counter_prime);
void  checking_numbers(pid_t other_process);

//-------------- main --------------------------------------------------
int main()
{
	signal(SIGUSR1, catch_sigusr);
	signal(SIGUSR2, catch_sigusr);

	pid_t child = fork();

	checking_fork(child);

	if (child == 0)
	{
		srand(18);
		checking_numbers(getppid());
	}

	if (child != 0)
	{
		srand(17);
		checking_numbers(child);
	}

	exit(EXIT_SUCCESS);
}
//----------------------------------------------------------------------
// The function check if a certain number is prime.
// The funcion recives one number.
// The function return if the number is prime.

bool is_prime(int num)
{
	if (num <= 1)
	{
		return false;
	}

	for (int i = 2; i * i <= num; i++)
	{
		if (num % i == 0)
		{
			return false;
		}
	}

	return true;
}
//--------------------------------------------------------------------

// The function is the signal holder, it prints a sentence, according
//  to the signal.
// The function receives the number of the signal.
// The function returns void.

void catch_sigusr(int sig_num)
{
	if (sig_num == SIGUSR1)
	{
		puts("congrats!");
	}

	else
	{
		puts("thanks!");
	}

	printf("%d %d \n", counter_above, counter_less);
	exit(EXIT_SUCCESS);
}
//----------------------------------------------------------------------

// The function checks if the fork succeeded.
// The function receives the process number.
// The function returns nothing.

void checking_fork(pid_t child)
{
	if (child < 0)
	{
		perror("fork didnt suceded");
		exit(EXIT_FAILURE);
	}
}
//----------------------------------------------------------------------

// The function checks if one of the conditions were met.
// The function receives a proccess id, and a number.
// The function returns, if either one of the conditions met.

bool checking_counters(pid_t other_process, int counter_prime)
{
	if (counter_above == 10)
	{
		puts("I win");
		kill(other_process, SIGUSR1);
		return true;
	}

	else if (counter_less == 100)
	{
		puts("I lose");
		kill(other_process, SIGUSR2);
		return true;
	}

	else if (counter_prime == 50)
	{
		puts("I prime \n");
		return true;
	}

	return false;
}
//----------------------------------------------------------------------

// The function sleeps for maximum time of 1 second, generates a random
//  number between 0 - 100, and then check if the number meets one of
//  the conditions.
// The function recieves proccess number.
// The function return void.

void  checking_numbers(pid_t other_process)
{
	int counter_prime = 0;
	int num = 0;

	while (true)
	{
		sleep(rand() % 2);
		num = rand() % 101;

		if (num >= 95)
		{
			counter_above++;
		}

		if (num < 55)
		{
			counter_less++;
		}

		if (is_prime(num))
		{
			counter_prime++;
		}

		if (checking_counters(other_process, counter_prime))
		{
			exit(EXIT_SUCCESS);
		}
	}
}
