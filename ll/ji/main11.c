#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

char *get_v(char *namev)
{
	    char **v;
	        int len_of_variable;

		    if (namev == NULL || namev[0] == '\0')
			            return NULL;
		        len_of_variable = (int)strlen(namev);

			    for (v = environ; *v != NULL; v++)
				        {
						        if (strncmp(*v, namev, len_of_variable) == 0)
								        {
										            if ((*v)[len_of_variable] == '=')
												                    return (*v + len_of_variable + 1);
											            }
							    }
			        return NULL;
}

void P_env(void)
{
	    int i, j;

	        for (i = 0; environ[i] != NULL; i++)
			    {
				            for (j = 0; environ[i][j] != '\0'; j++)
						                write(1, &environ[i][j], 1);
					            write(1, "\n", 1);
						        }
}

void execute_command(char *command, char **arguments)
{
	    pid_t pid;
	        int status;

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
											            execvp(command, arguments);
												                perror("execvp");
														            exit(EXIT_FAILURE);
															            }
								    }
			        else
					    {
						            waitpid(pid, &status, 0);

							            if (WIFEXITED(status))
									            {
											                int exit_status = WEXITSTATUS(status);
													            if (exit_status != 0)
															                {
																		                exit(exit_status);
																				            }
														            }
								        }
}

void display_prompt()
{
	    write(STDOUT_FILENO, "($)\n", 4);
}

int find_command(char *command, char *path)
{
	    char *token;
	        char *full_path = NULL;
		    char *path_copy = strdup(path);
		        int found = 0;

			    token = strtok(path_copy, ":");
			        while (token != NULL)
					    {
						            full_path = malloc(strlen(token) + strlen(command) + 2);
							            sprintf(full_path, "%s/%s", token, command);
								            if (access(full_path, X_OK) == 0)
										            {
												                found = 1;
														            break;
															            }
									            free(full_path);
										            token = strtok(NULL, ":");
											        }
				    free(path_copy);
				        if (full_path != NULL)
						    {
							            strcpy(command, full_path);
								            free(full_path);
									        }

					    return (found);
}

void handle_exit_command(char **tokens)
{
	    int exit_status;

	        if (tokens[1] != NULL)
			    {
				            exit_status = atoi(tokens[1]);
					            exit(exit_status);
						        }
		    else
			        {
					        exit(0);
						    }
}

void handle_non_exit_command(char **tokens)
{
	    char *command = tokens[0];
	        char *path;

		    if (access(command, X_OK) != 0)
			        {
					        path = getenv("PATH");
						        if (path != NULL && find_command(command, path))
								        {
										            tokens[0] = command;
											            }
							        else
									        {
											            fprintf(stderr, "%s: command not found\n", command);
												                return;
														        }
								    }

		        execute_command(tokens[0], tokens);
}

void process_input(char *input)
{
	    char *token;
	        char *tokens[MAX_ARGUMENTS + 2];
		    int token_count = 0;
		        char *command;

			    token = strtok(input, " ");
			        while (token != NULL && token_count < MAX_ARGUMENTS + 1)
					    {
						            tokens[token_count++] = token;
							            token = strtok(NULL, " ");
								        }

				    tokens[token_count] = NULL;

				        if (token_count > 0)
						    {
							            command = tokens[0];

								            if (strcmp(command, "env") == 0)
										            {
												                P_env();
														        }
									            else if (strcmp(command, "exit") == 0)
											            {
													                handle_exit_command(tokens);
															        }
										            else
												            {
														                handle_non_exit_command(tokens);
																        }
											        }
}

int main(int argc, char **argv)
{
	    char *input = NULL;
	        size_t len = 0;
		    ssize_t read;
		        (void)argv;

			    if (argc == 1 && isatty(STDIN_FILENO))
				        {
						        while (1)
								        {
										            display_prompt();
											                read = getline(&input, &len, stdin);
													            if (read == -1)
															                {
																		                write(STDOUT_FILENO, "\n", 1);
																				                break;
																						            }
														                input[strcspn(input, "\n")] = 0;
																            process_input(input);
																	            }
							    }
			        else
					    {
						            while ((read = getline(&input, &len, stdin)) != -1)
								            {
										                input[strcspn(input, "\n")] = 0;
												            process_input(input);
													            }
							        }
				    free(input);
				        return (0);
}

