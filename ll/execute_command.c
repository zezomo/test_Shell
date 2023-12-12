#include "projectshell.h"

/**
 *  * execute_command - this is a function believe me
 *   * @command: did you really will read this
 *    * @arguments: did you really will read this
 *     * Return: return pointer of string
 *     */
void execute_command(char *command, char **arguments, char **envp)
{
	    pid_t pid;
	        int status;
		    int exit_status;

		        pid = fork();

			    if (pid == -1)
				        {
						        perror("fork");
							    }
			        else if (pid == 0)
					    {
						            if (strcmp(command, "exit") == 0)
								            {
										                exit(EXIT_SUCCESS);
												        }
							            else
									            {
											                if (execve(command, arguments, envp) == -1)
														            {
																                    perror("execve");
																		                    exit(EXIT_FAILURE);
																				                }
													        }
								        }
				    else
					        {
							        waitpid(pid, &status, 0);
								        if (WIFEXITED(status))
										        {
												            exit_status = WEXITSTATUS(status);
													                if (exit_status != 0)
																            {
																		                    exit(exit_status);
																				                }
															        }
									    }
}
/**
 *  * display_prompt - this is a function believe me
 *   *
 *    * Return: return pointer of string
 *    */
void display_prompt(void)
{
	    write(STDOUT_FILENO, "$ ", 2);
}
