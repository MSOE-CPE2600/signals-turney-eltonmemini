/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Elton Emini
 * 
 * Brief summary of modifications: added a signal handler for sigsegv
 */


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Signal handler for SIGSEGV - prints a message and exits
 */
void handle_signal() {
    printf("Segmentation error!\n");
    exit(1);
}

int main (int argc, char* argv[]) {
    // Declare a null pointer
    int* i = NULL;

    signal(SIGSEGV, handle_signal);

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);


    // Return to exit the program
    return 0;
}