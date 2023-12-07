#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt(void)
{
    write(STDOUT_FILENO, "$ /n", 2);
}

void execute_command(const char *command)
{
	pid_t pid; 
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		execlp(command, command, NULL);
		perror("execlp");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

int main(int argc, char **argv)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	if (argc == 1 && isatty(STDIN_FILENO))
	{
		while (1) {
			display_prompt();
			read = getline(&input, &len, stdin);

			if (read == -1)
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}

			input[strcspn(input, "\n")] = 0;

			execute_command(input);
		}
	}
	else
	{
		while ((read = getline(&input, &len, stdin)) != -1)
		{
			input[strcspn(input, "\n")] = 0;
			execute_command(input);
		}
	}
	free(input);
	return (0);
}

