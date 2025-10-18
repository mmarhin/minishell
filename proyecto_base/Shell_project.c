#include "job_control.h"   // remember to compile with module job_control.c 
#include "parse_redir.h"




#define MAX_LINE 256 /* 256 chars per line, per command, should be enough. */

// -----------------------------------------------------------------------
//                            MAIN          
// -----------------------------------------------------------------------

//
//				Manejador para sigchld
//


void manejador_chld (int num)
{
	int pid;

	int wstatus;

	
	while(1)
	{
		pid = waitpid(-1, &wstatus, WNOHANG | WUNTRACED | WCONTINUED); // wait no bloqueante, solo recoge los hijos que están pendientes de recoger

		if (pid == -1)
		{
			return;
		}
		if (pid == 0)
		{
			return;
		}
	}
}


int main(void)
{
	

	char inputBuffer[MAX_LINE]; /* buffer to hold the command entered */
	int background = 0;             /* equals 1 if a command is followed by '&' */
	char *args[MAX_LINE/2];     /* command line (of 256) has max of 128 arguments */
	// probably useful variables:
	int pid_fork, pid_wait; /* pid for created and waited process */
	int status;             /* status returned by wait */
	enum status status_res; /* status processed by analyze_status() */
	int info;  /* info processed by analyze_status() */

	
	signal(SIGINT,  SIG_IGN); // crtl+c interrupt tecleado en el terminal
    signal(SIGQUIT, SIG_IGN); // ctrl+\ quit tecleado en el terminal
    signal(SIGTSTP, SIG_IGN); // crtl+z Stop tecleado en el terminal
    signal(SIGTTIN, SIG_IGN); // proceso en segundo plano quiere leer del terminal 
    signal(SIGTTOU, SIG_IGN); // proceso en segundo plano quiere escribir en el terminal

	signal(SIGCHLD, manejador_chld);


	while (1)   /* Program terminates normally inside get_command() after ^D is typed*/
	{		
		printf("COMMAND->");
		fflush(stdout);
		get_command(inputBuffer, MAX_LINE, args, &background);  /* get next command */
		
		char *file_in, *file_out;
		parse_redirections(args, &file_in, &file_out);


		if(args[0]==NULL)
		{
			continue;   // if empty command
		}
		
		if (strcmp(args[0], "cd") == 0)
		{
			if (args[1] == NULL)
				chdir("/");
			else if (chdir(args[1]) != 0)
				printf("No se puede cambiar al directorio %s\n", args[1]);
			continue;
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			exit(0);
		}
		else
		{
			pid_fork = fork();
		
			if (pid_fork < 0)
			{
				perror("Fork ha fallado");
				exit (EXIT_FAILURE);
			}

			if (pid_fork == 0)
			{
				signal(SIGINT,  SIG_DFL); // crtl+c interrupt tecleado en el terminal
				signal(SIGQUIT, SIG_DFL); // ctrl+\ quit tecleado en el terminal
				signal(SIGTSTP, SIG_DFL); // crtl+z Stop tecleado en el terminal
				signal(SIGTTIN, SIG_DFL); // proceso en segundo plano quiere leer del terminal 
				signal(SIGTTOU, SIG_DFL); // proceso en segundo plano quiere escribir en el terminal
				
				pid_fork = getpid();
				pid_t group = pid_fork; 
				if(setpgid(pid_fork, group) != 0)
				{
					perror("No se ha establecido correctamente el grupo");
					exit(EXIT_FAILURE);
				}
				if (background == 0)
				{
					if (tcsetpgrp(STDIN_FILENO, getpid()) == -1) //getpgrp
					{
						perror("Error cediendo terminal");
						exit(EXIT_FAILURE);
					}
				}

				if (file_in != NULL)
				{
					int fd = open(file_in, O_RDONLY);
					if (fd == -1)
					{
						perror("No se ha podido abrir el fichero");
						continue;
					}
					if (dup2(fd, STDIN_FILENO)==-1)
					{
						perror("No se puede redirigir la entrada");
						continue;
					}
					close(fd);
				}

				if (file_out)
				{
					int fd = open(file_out, O_CREAT|O_WRONLY|O_TRUNC,  0644);
					if (fd == -1)
					{
						perror("No se ha podido crear el fichero");
						continue;
					}
					if (dup2(fd, STDOUT_FILENO)==-1)
					{
						perror("No se puede redirigir la entrada");
						continue;
					}
					close(fd);
				}


				execvp(args[0], args);
				perror(args[0]);
				exit (EXIT_FAILURE);
			}
			if (pid_fork > 0)
			{
				if (background == 0)
				{
					if (tcsetpgrp(STDIN_FILENO, pid_fork) == -1)
					{
						perror("Error cediendo terminal");
						continue;
					}
					pid_wait = waitpid(pid_fork, &status, WUNTRACED);
					
					if (pid_wait < 0)
					{
						perror("Fallo en wait");
						continue;
					}

					if (tcsetpgrp(STDIN_FILENO, getpid()) == -1)
					{
						perror("Error recuperando terminal");
						continue;
					}
				}else
				{
					printf("Background job running... pid: %d, command: %s\n", pid_fork, args[0]);
					mask_signal(SIGCHLD, SIG_BLOCK);
					mask_signal(SIGCHLD, SIG_UNBLOCK);
				}
			}
		}
	}
}