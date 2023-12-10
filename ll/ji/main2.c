#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void display_prompt() {
	    if (write(STDOUT_FILENO, "$ ", 2) == -1) {
		            perror("write");
			            exit(EXIT_FAILURE);
				        }
}

void execute_command(char *command, char **arguments) {
	    pid_t pid;

	        pid = fork();

		    if (pid == -1) {
			            perror("fork");
				            exit(EXIT_FAILURE);
					        } else if (pid == 0) {
							        execvp(command, arguments);
								        perror("execvp");
									        exit(EXIT_FAILURE);
										    } else {
											            if (waitpid(pid, NULL, 0) == -1) {
													                perror("waitpid");
															            exit(EXIT_FAILURE);
																            }
												        }
}

void copy_and_execute(char *source, char *destination, char **arguments) {
	    pid_t pid;

	        pid = fork();

		    if (pid == -1) {
			            perror("fork");
				            exit(EXIT_FAILURE);
					        } else if (pid == 0) {
							        if (execlp("cp", "cp", source, destination, NULL) == -1) {
									            perror("execlp");
										                exit(EXIT_FAILURE);
												        }
								    } else {
									            if (waitpid(pid, NULL, 0) == -1) {
											                perror("waitpid");
													            exit(EXIT_FAILURE);
														            }
										            execute_command(destination, arguments);
											        }
}

int main(int argc, char **argv) {

	    char *input = NULL;
	        size_t len = 0;
		    ssize_t read;
		        char *token;
			    char *tokens[MAX_ARGUMENTS + 2];
			        int token_count = 0;

				    (void)argv;

				        if (argc == 1 && isatty(STDIN_FILENO)) {
						        while (1) {
								            display_prompt();

									                read = getline(&input, &len, stdin);

											            if (read == -1) {
													                    if (write(STDOUT_FILENO, "\n", 1) == -1) {
																                        perror("write");
																			                    exit(EXIT_FAILURE);
																					                    }
															                    break;
																	                }

												                input[strcspn(input, "\n")] = 0;
														            token = strtok(input, " ");
															                while (token != NULL && token_count < MAX_ARGUMENTS + 1) {
																		                tokens[token_count++] = token;
																				                token = strtok(NULL, " ");
																						            }

																	            tokens[token_count] = NULL;

																		                if (token_count > 0) {
																					                if (strcmp(tokens[0], "cp") == 0 && token_count >= 3) {
																								                    copy_and_execute(tokens[1], tokens[2], tokens + 3);
																										                    } else {
																													                        execute_command(tokens[0], tokens);
																																                }
																							            }
																				        }
							    } else {
								            char *token;
									            char *tokens[MAX_ARGUMENTS + 2];
										            int token_count = 0;

											            while ((read = getline(&input, &len, stdin)) != -1) {
													                input[strcspn(input, "\n")] = 0;

															            token = strtok(input, " ");
																                while (token != NULL && token_count < MAX_ARGUMENTS + 1) {
																			                tokens[token_count++] = token;
																					                token = strtok(NULL, " ");
																							            }

																		            tokens[token_count] = NULL;

																			                if (token_count > 0) {
																						                if (strcmp(tokens[0], "cp") == 0 && token_count >= 3) {
																									                    copy_and_execute(tokens[1], tokens[2], tokens + 3);
																											                    } else {
																														                        execute_command(tokens[0], tokens);
																																	                }
																								            }
																					        }
												        }

					    free(input);

					        return 0;
}

