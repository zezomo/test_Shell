#include "main.h"
/**
 * exit_func - to exit safely
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
int exit_func(_arg *arg)
{
int length, found = 0;

found = _strcmp(arg->command, "exit");
if (!found)
{
	if (arg->token > 1)
	{
	length = _strlen(arg->command) + 1;
	arg->exit_st = _atoi(arg->command + length);
	}
	if (_atoi(arg->command + length) != -1)
	{
		if (arg->path)
		{
			free(arg->path);
		}
		if (arg->old_path)
		{
			free(arg->old_path);
		}
		if (arg->command)
		{
			free(arg->command);
		}
		if (arg->pwd)
		{
			free(*(arg->pwd));
		}
		exit(arg->exit_st);
	}
	printf("%s: %i: exit: illegal number: %s\n",
	arg->prog_name, arg->i, arg->command + length);
	arg->exit_st = 2;
	return (1);
}
	return (0);
}
/**
 * _cd - to change directory
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
int _cd(_arg *arg)
{
char *str, *com = arg->command;
int found = 0;

found = _strcmp(com, "cd");
if (!found)
{
if (arg->token == 1)
str = _env(arg->env, "HOME", 4);
else
{
com += 3;
if (_strcmp(com, "-"))
str = com;
else
{
str = arg->old_path;
write(1, str, _strlen(str));
_putchar('\n');
}
}
if (chdir(str) == -1)
{
printf("%s: %i: cd: Can't change directory to %s\n",
arg->prog_name, arg->i, str);
arg->exit_st = 2;
}
else
{
free(arg->old_path);
arg->old_path = _strdup(arg, &((*(arg->pwd))[4]));
if (!arg->old_path)
prog_exit(arg);
pwd_ch(arg);
arg->exit_st = 0;
}
return (1);
}
return (0);
}
/**
 * _env2 - to get env variables
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
int _env2(_arg *arg)
{
int i = 0;

if (compare_backward(arg->command, "env"))
{
while (arg->env[i] != NULL)
{
write(1, arg->env[i], _strlen(arg->env[i]));
_putchar('\n');
i++;
}
arg->exit_st = 0;
return (1);
}
return (0);
}
/**
 * _execve - to excute commands
 * Description: for simple shell task
 * @arg: an argument
 * @buffer: an argument
 * Return: 1 on sucess
*/
int _execve(_arg *arg, char *buffer)
{
char **str, *com = arg->command;
int i = 0, flag = 0;
pid_t pid = fork();

if (!pid)
{
flag = compare_backward(arg->command, "pwd");
if (flag)
{
str = malloc(16);
if (!str)
	exit(255);
str[0] = arg->command;
str[1] = NULL;
}
else
{
str = malloc((arg->token + 1) * 8);
if (!str)
	exit(255);
while (i < arg->token)
{
str[i] = com;
com += _strlen(com) + 1;
i++;
}
str[i] = NULL;
}
execve(buffer, str, NULL);
free(str);
exit(arg->exit_st);
}
wait(&(arg->exit_st));
arg->exit_st = WEXITSTATUS(arg->exit_st);
return (arg->exit_st);
}
