# Signals_Use_Linux

File: ex2a.c 

Ex #1: Counting amount of max numbers under 5 seconds.
==========================================================
Written by: Jacob Bondar.

This program simulates a counting game where the user has 5
 seconds to input numbers as many as he can until the alarm is 
 trigged and sends a signal.
This program tracks the maximum number of inputs given threw the 10 
 rounds. Each round starts when the users press enter.

Compile: gcc -Wall ex2a.c –o ex2a
Run: ./ex2a

Input: User enters an enter and then the maximum numbers he can in 
 	5 seconds.
 
Output: The maximum number of inputs given in the whole rounds.


File: ex2b.c 
Ex #2: Search Amount Of Random Numbers.
==========================================================
Written by: Jacob Bondar.

This program simulates a search task between two processes using a
 random number generator. It checks which numbers we got with the
 following pattern:
 - Numbers greater than or equal to 95 increase the 'counter_above'.
 - Numbers less than 55 increase the 'counter_less'.
 - Prime numbers.

The program forks into two processes: the parent and the child. Each
 process performs these tests independently and sends a signal to the
 other process, once a winning condition is met 
 (either 'counter_above' reaches 10, 'counter_less' reaches 100, 
 or 50 prime numbers are found).


Race conditions: There is a race between the dad and the son. Either the
 child finished before the dad, and sends dad to the signal handler or the
 other way around. There is a possibility that the two processes send each 
 other to the signal handler simultaneously.
possible outputs: I lose
		  thanks!
		  0 0
		  =======
		  I lose
		  thanks!
		  9 100
		  =======
		  I lose
		  =======
		  I win
		  congrats!
		  6 76

 
The program uses signals (SIGUSR1 and SIGUSR2) to communicate between
 the processes. The winner sends a signal to the other process.

Compile: gcc -Wall ex2b.c –o ex2b
Run: ./ex2b

Input: No input.
 
Output: - The number of counter_above and counter_less of the process that
 		recieved one of the signals.
 	- A message indicating which process wins, loses, or counts prime
 		numbers and congrats! or thanks! depends on which process 
		finished first.
