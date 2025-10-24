/*--------------------------------------------------------
UNIX Shell Project
job_control module

Sistemas Operativos
Grados I. Informatica, Computadores & Software
Dept. Arquitectura de Computadores - UMA

Some code adapted from "Fundamentos de Sistemas Operativos", Silberschatz et al.
--------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "job_control.h"

// -----------------------------------------------------------------------
//  get_command() reads in the next command line, separating it into distinct tokens
//  using whitespace as delimiters. setup() sets the args parameter as a 
//  null-terminated string.
// -----------------------------------------------------------------------

void get_command(char *inputBuffer, int size, char *args[], int *background)
{
    int length; /* # of characters in the command line */
    int i;      /* loop index for accessing inputBuffer array */
    int start;  /* index where beginning of next command parameter is */
    int ct = 0; /* index of where to place the next parameter into args[] */

    *background=0;

    /* read what the user enters on the command line */
    length = read(STDIN_FILENO, inputBuffer, size);  

    start = -1;
    if (length == 0) {
        printf("\nBye\n");
        exit(0);            /* ^d was entered, end of user command stream */
    } 
    if (length < 0) {
        perror("error reading the command");
        exit(-1);           /* terminate with error code of -1 */
    }
    /* examine every character in the inputBuffer */
    for (i = 0; i < length; i++) { 
        switch (inputBuffer[i]) {
        case ' ':
        case '\t':               /* argument separators */
            if(start != -1) {
                args[ct] = &inputBuffer[start];    /* set up pointer */
                ct++;
            }
            inputBuffer[i] = '\0'; /* add a null char; make a C string */
            start = -1;
            break;
        case '\n':                 /* should be the final char examined */
            if (start != -1) {
                args[ct] = &inputBuffer[start];     
                ct++;
            }
            inputBuffer[i] = '\0';
            args[ct] = NULL; /* no more arguments to this command */
            break;
        default :             /* some other character */
            if (inputBuffer[i] == '&') { // background indicator
                *background  = 1;
                if (start != -1) {
                    args[ct] = &inputBuffer[start];     
                    ct++;
                }
                inputBuffer[i] = '\0';
                args[ct] = NULL; /* no more arguments to this command */
                i = length; // make sure the for loop ends now
            }
            else if (start == -1) {
                start = i;  // start of new argument
            }
        }  // end switch
    }  // end for   
    args[ct] = NULL; /* just in case the input line was > MAXLINE */
} 

// -----------------------------------------------------------------------
// cambia la accion de las seÃ±ales relacionadas con el terminal
void terminal_signals(void (*func) (int))
{
    signal(SIGINT,  func); // crtl+c interrupt tecleado en el terminal
    signal(SIGQUIT, func); // ctrl+\ quit tecleado en el terminal
    signal(SIGTSTP, func); // crtl+z Stop tecleado en el terminal
    signal(SIGTTIN, func); // proceso en segundo plano quiere leer del terminal 
    signal(SIGTTOU, func); // proceso en segundo plano quiere escribir en el terminal
}		

// -----------------------------------------------------------------------
void mask_signal(int signal, int block)
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, signal);
    sigprocmask(block, &mask, NULL); // block: SIG_BLOCK/SIG_UNBLOCK
}

