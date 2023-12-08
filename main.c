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

int main(int argc, char **argv) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

    if (argc == 1 && isatty(STDIN_FILENO)) {
        // Interactive mode
        while (1) {
            display_prompt();

            read = getline(&input, &len, stdin);

            if (read == -1) {
                write(STDOUT_FILENO, "\n", 1);
                break;
            }

            input[strcspn(input, "\n")] = 0;

            // Tokenize the input into command and arguments
            char *token;
            char *tokens[MAX_ARGUMENTS + 2];  // +2 to account for command and NULL terminator
            int token_count = 0;

            token = strtok(input, " ");
            while (token != NULL && token_count < MAX_ARGUMENTS + 1) {
                tokens[token_count++] = token;
                token = strtok(NULL, " ");
            }

            tokens[token_count] = NULL;  // NULL terminate the array of arguments

            if (token_count > 0) {
                // Execute the command with arguments
                execute_command(tokens[0], tokens);
            }
        }
    } else {
        // Non-interactive mode
        while ((read = getline(&input, &len, stdin)) != -1) {
            input[strcspn(input, "\n")] = 0;

            // Tokenize the input into command and arguments
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
                // Execute the command with arguments
                execute_command(tokens[0], tokens);
            }
        }
    }

    free(input);

    return 0;
}

