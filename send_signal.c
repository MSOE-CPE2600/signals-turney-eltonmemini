/**
 * File: send_signal.c
 * Modified by: Elton Emini
 * 
 * Brief summary of program: sends SIGUSR1 along with a random integer 
 * (see https://man7.org/linux/man-pages/man3/srand.3.html) to the 
 * process using sigqueue. Print this number in the sending program 
 * before sending SIGUSR1.
 */

 #include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h> 

int main(int argc, char *argv[]) {
    pid_t receiver_pid;
    int value_to_send;
    union sigval sv;

    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]); 
        exit(EXIT_FAILURE);
    }

    receiver_pid = (pid_t)atoi(argv[1]);

    if (receiver_pid <= 0) {
        fprintf(stderr, "Invalid PID: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Generate and print random number 
    
    srand(time(NULL));

    value_to_send = rand();

    // Print the number before sending it 
    printf("Sending value %d to PID %d...\n", value_to_send, receiver_pid);

    // Send the signal and data 

    sv.sival_int = value_to_send;

    if (sigqueue(receiver_pid, SIGUSR1, sv) == -1) {
        perror("sigqueue");
        fprintf(stderr, "Failed to send signal. Is PID %d correct and running?\n", receiver_pid);
        exit(EXIT_FAILURE);
    }

    printf("Signal sent successfully.\n");
    return 0;
}