#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void display_prompt() {
	    write(STDOUT_FILENO, "($)\n", 4);
}

void execute_command(char *command, char **arguments) {
	    pid_t pid = fork();

	        if (pid == -1) {
			        perror("fork");
				    } else if (pid == 0) {
					            execvp(command, arguments);
						            perror("execvp");
							            exit(EXIT_FAILURE);
								        } else {
										        waitpid(pid, NULL, 0);
											    }
}

void handle_input(char *input) {
	    char *token;
	        char *tokens[MAX_ARGUMENTS + 2];
		    int token_count = 0;

		        token = strtok(input, " ");
			    while (token != NULL && token_count < MAX_ARGUMENTS + 1) {
				            tokens[token_count++] = token;
					            token = strtok(NULL, " ");
						        }

			        tokens[token_count] = NULL;

				    if (token_count > 0) {
					            if (strcmp(tokens[0], "exit") == 0) {
							                free(input);
									            exit(0);
										            }

						            execute_command(tokens[0], tokens);
							        }
}

void interactive_mode() {
	    char *input = NULL;
	        size_t len = 0;
		    ssize_t read;

		        while (1) {
				        display_prompt();

					        read = getline(&input, &len, stdin);

						        if (read == -1) {
								            write(STDOUT_FILENO, "\n", 1);
									                break;
											        }

							        input[strcspn(input, "\n")] = 0;
								        handle_input(input);
									    }

			    free(input);
}

void non_interactive_mode() {
	    char *input = NULL;
	        size_t len = 0;
		    ssize_t read;

		        while ((read = getline(&input, &len, stdin)) != -1) {
				        input[strcspn(input, "\n")] = 0;
					        handle_input(input);
						    }

			    free(input);
}

int main(int argc, char **argv) {
	(void)argv;
	    if (argc == 1 && isatty(STDIN_FILENO)) {
		            interactive_mode();
			        } else {
					        non_interactive_mode();
						    }

	        return 0;
}

