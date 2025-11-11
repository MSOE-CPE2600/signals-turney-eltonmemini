/**
 * File: signal_sigaction.c
 * Modified by: Elton Emini
 * * Brief summary of program: uses sigaction to register a handler for the SIGUSR1 signal. 
 * - After registering, have the program wait in an infinite loop 
 * - The signal handler prints the PID of the process that sent the signal.
 *
 * gcc signal_sigaction.c -o signal_sigaction
 */

#include <stdio.h>     
#include <signal.h>    
#include <unistd.h>    
#include <stdlib.h>    

/*
 * @brief Signal handler for SIGUSR1 that uses the siginfo_t structure.
 */
void sigusr1_handler(int signum, siginfo_t *info, void *context) {
    printf("\nReceived signal %d (SIGUSR1) from sender with PID: %d\n", signum, info->si_pid);
}

int main() {
    struct sigaction sa;

    sa.sa_sigaction = sigusr1_handler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Error registering sigaction");
        exit(EXIT_FAILURE);
    }

    // Print this process's PID so the user knows where to send the signal
    printf("Program running. My PID is: %d\n", getpid());
    printf("Waiting for SIGUSR1...\n");

    while (1) {
        pause();
    }

    return 0; 
}