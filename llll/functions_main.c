#include "main.h"
/**
 * new_line - to make new command
 * Description: for simple shell task
 * @signal: an argument
 * Return: 1 on sucess
*/
void new_line(int signal)
{
	if (signal == SIGINT)
	{
		_putchar('\n');
		_putchar('$');
		_putchar(' ');
	}
}
/**
 * command_getter - to get commands
 * Description: for simple shell task
 * @arg: an argument
 * @point: an argument
 * @dot: an argument
 * Return: 1 on sucess
*/
int command_getter(_arg *arg, int point, int *dot)
{
	ssize_t bytes;

	bytes = line_getter(arg);
	if (bytes == -1)
	{
		input_exit(arg, point);
	}
	if (*dot)
		arg->i--;
	if (arg->command[bytes - 1] == '\n')
	{
		arg->command[bytes - 1] = '\0';
	}
	if (arg->command[bytes - 1] == ';')
	{
		arg->command[bytes - 1] = '\0';
		*dot = 1;
		return (0);
	}
	*dot = 0;
	return (1);
}
/**
 * input_exit - to exit input
 * Description: for simple shell task
 * @arg: an argument
 * @point: an argument
 * Return: 1 on sucess
*/
void input_exit(_arg *arg, int point)
{
	if (isatty(STDIN_FILENO) && point && !arg->fd)
	_putchar('\n');
	close(arg->fd);
	if (arg->command)
	{
		free(arg->command);
	}
	if (arg->path)
	{
		free(arg->path);
	}
	if (arg->pwd)
	{
		free(*(arg->pwd));
	}
	if (arg->old_path)
	{
		free(arg->old_path);
	}
	exit(arg->exit_st);
}
/**
 * token_maker - to make tokens
 * Description: for simple shell task
 * @command: an argument
 * @sign: an argument
 * Return: 1 on sucess
*/
int token_maker(char *command, char *sign)
{
	char *token_string = NULL;
	int counter = 0;

	token_string = _strtok(command, sign);

	for (counter = 0; token_string != NULL; counter++)
	{
		token_string = _strtok(NULL, sign);
	}
	return (counter);
}
/**
 * command_maker - to make commands
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
int command_maker(_arg *arg)
{
char *path = arg->path;
int x = 0, flag;

if (exit_func(arg) || _cd(arg))
	return (arg->exit_st);
if (arg->command[0] == '/')
{
	flag = access(arg->command, X_OK);
	if (flag == 0)
	{
		if (!_env2(arg))
			return (_execve(arg, arg->command));
		return (0);
	}
	printf("%s: %i: %s: not found\n", arg->prog_name, arg->i, arg->command);
}
else
{
	if (!_strcmp(arg->command, "env") && _env2(arg))
		return (0);
	while (x < arg->num_path)
	{
		char temp[512] = "";

		_strcat(temp, path);
		_strcat(temp, "/");
		_strcat(temp, arg->command);
		if (access(temp, X_OK) == 0)
			return (_execve(arg, temp));
		path += _strlen(path) + 1;
		x++;
	}
	printf("%s: %i: %s: can't be found\n", arg->prog_name, arg->i, arg->command);
}
arg->exit_st = 127;
return (arg->exit_st);
}
