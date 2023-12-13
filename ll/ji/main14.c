#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define BUFFER_SIZE 1024

extern char **environ;

void display_prompt()
{
	    write(STDOUT_FILENO, "$ ", 2);
}

char *custom_strtok(char *str, const char *delim)
{
	    static char *saveptr = NULL;
	        char *token;
		    char *p;

		        if (str != NULL)
				    {
					            saveptr = str;
						        }
			    
			    if (saveptr == NULL || *saveptr == '\0')
				        {
						        return NULL;
							    }
			        saveptr += strspn(saveptr, delim);
				    if (*saveptr == '\0')
					        {
							        return NULL;
								    }
				        token = saveptr;
					    p = strpbrk(saveptr, delim);
					        if (p != NULL)
							    {
								            *p = '\0';
									            saveptr = p + 1;
										        }
						    else
							        {
									        saveptr += strlen(saveptr);
										    }
						        return (token);
}


ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	        size_t i = 0;
		    int c;
		        if (!*lineptr) {
				        *lineptr = malloc(BUFFER_SIZE);
					        if (!*lineptr) {
							            perror("malloc");
								                exit(EXIT_FAILURE);
										        }
						        *n = BUFFER_SIZE;
							    }


			    while ((c = fgetc(stream)) != EOF && c != '\n') {
				            if (i == *n - 1) {
						                *lineptr = realloc(*lineptr, *n + BUFFER_SIZE);
								            if (!*lineptr) {
										                    perror("realloc");
												                    exit(EXIT_FAILURE);
														                }
									                *n += BUFFER_SIZE;
											        }
					            (*lineptr)[i++] = c;
						        }

			        if (i > 0 && (*lineptr)[i - 1] == '\r') {
					        (*lineptr)[i - 1] = '\0';
						    } else {
							            (*lineptr)[i] = '\0';
								        }

				    return (c == EOF && i == 0) ? -1 : (ssize_t)i;
}


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




int find_command(char *command, char *path)
{
	    char *token;
	        char *full_path = NULL;
		    char *path_copy = strdup(path);
		        int found = 0;

			    token = custom_strtok(path_copy, ":");
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
										            token = custom_strtok(NULL, ":");
											        }
				    free(path_copy);
				        if (full_path != NULL)
						    {
							            strcpy(command, full_path);
								            free(full_path);
									        }
					    return (found);
}







int compare_strings(const void *a, const void *b) {
	    return strcmp(*(const char **)a, *(const char **)b);
}

void handle_env_command() {
	    int count = 0;
	        char **env_copy;
		    int i;
		        int j;
			    int k;

			        while (environ[count] != NULL) {
					        count++;
						    }

				    env_copy = malloc((count + 1) * sizeof(char *));
				        for (i = 0; i < count; i++) {
						        env_copy[i] = strdup(environ[i]);
							    }
					    env_copy[count] = NULL;

					        qsort(env_copy, count, sizeof(char *), compare_strings);

						    for (j = 0; j < count; j++) {
							            printf("%s\n", env_copy[j]);
								        }

						        for (k = 0; k < count; k++) {
								        free(env_copy[k]);
									    }
							    free(env_copy);
}



void handle_exit_command(char **tokens)
{
	     int exit_status;

	         if (strcmp(tokens[0], "exit") == 0)
			     {
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
}

void handle_any_command(char **tokens)
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
	        execute_command(tokens[0], tokens, environ);
}


void process_input(char *input)
{
	  char *token;
	    char *tokens[MAX_ARGUMENTS + 2];
	      int token_count = 0;

	        token = custom_strtok(input, " ");
		  while (token != NULL && token_count < MAX_ARGUMENTS + 1)
			    {
				        tokens[token_count++] = token;
					    token = custom_strtok(NULL, " ");
					      }
		    tokens[token_count] = NULL;
		      if (token_count > 0)
			        {
					    if (strcmp(tokens[0], "env") == 0)
						        {
								      handle_env_command();
								          }
					        else if (strcmp(tokens[0], "exit") == 0)
							    {
								          handle_exit_command(tokens);
									      }
						    else
							        {
									      handle_any_command(tokens);

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
											                read = custom_getline(&input, &len, stdin);
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
						            while ((read = custom_getline(&input, &len, stdin)) != -1)
								            {
										                input[strcspn(input, "\n")] = 0;
												            process_input(input);
													            }
							        }
				    free(input);
				        return (0);
}

