/**
 * File: recv_signal.c
 * Modified by: Elton Emini
 * 
 * Brief summary of program: uses sigaction to register a handler for
 *  the SIGUSR1 signal. - After registering, have the program wait in an 
 * infinite loop (see previous examples). The program doesn’t need to print 
 * anything inside the loop. - In the signal handler registered using 
 * sigaction, retrieve the sival_int and print out this value, then return.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/**
 * @brief Signal handler for SIGUSR1 that prints the received integer.
 * * This handler is set up using SA_SIGINFO, so it receives
 * the siginfo_t struct containing the sent value.
 */
void sigusr1_handler(int signum, siginfo_t *info, void *ucontext) {
    int received_value = info->si_value.sival_int;
    
    printf("Received SIGUSR1 from sender PID: %d\n", info->si_pid);
    printf("Received integer value: %d\n", received_value);
}

int main() {
    struct sigaction sa;

    printf("Receiver PID: %d. Waiting for signal...\n", getpid());

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sa.sa_sigaction = sigusr1_handler;
    
    sa.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (1) {
        pause(); // Wait for a signal to arrive
    }

    return 0; // Unreachable
}