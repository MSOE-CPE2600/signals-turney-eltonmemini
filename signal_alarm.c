/**
 * File: signal_alarm.c
 * Modified by: Elton Emini
 * 
 * Brief summary of program:
 */

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

void alarm_handler() {
    printf("Alarm Signal Received\n");
    exit(1);
}


int main()
{
    signal(SIGALRM, alarm_handler);
    alarm(5);
    while(1)
    {
        printf("Sleeping\n");
        sleep(1);
    }
    return 0;
}