#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt()
{
	char prompt[] = "#cisfun$ ";
	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

int main()
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;

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

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			execlp(input, input, NULL);
			perror("execlp");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
	free(input);

	return (0);
}

