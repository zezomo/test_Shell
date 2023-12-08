#include "main.h"
/**
 * initialize_args - to help in simple shell
 * Description: for simple shell task
 * @arg: an argument
 * @argc: an argument
 * @argv: an argument
 * @env: an argument
 * Return: 1 on sucess
*/
void initialize_args(_arg *arg, int argc, char **argv, char **env)
{
	arg->command = NULL;
	arg->env = env;
	arg->pwd = NULL;
	arg->old_path = NULL;
	arg->path = _strdup(arg, _env(env, "PATH", 4));
	arg->pwd = pwd_getter(arg);
	if (arg->pwd)
		arg->old_path = _strdup(arg, &((*arg->pwd)[4]));
	arg->prog_name = argv[0];
	arg->i = 0;
	arg->exit_st = 0;
	arg->fd = 0;
	arg->pid = (int)getpid();
	arg->num_path = token_maker(arg->path, ":");
	if (argc > 1)
	{
		arg->fd = open(argv[1], O_RDONLY);
		if (arg->fd == -1)
		{
			printf("%s: 0: Can't open %s\n", argv[0], argv[1]);
			exit(2);
		}
	}
}
/**
 * pwd_getter - to help in simple shell
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
char **pwd_getter(_arg *arg)
{
int i = 0, flag = 0;
char *pwd = NULL;
while (arg->env[i] != NULL)
{
	flag = _strncmp(arg->env[i], "PWD", 3);
	if (flag == 0)
	{
		pwd = _strdup(arg, arg->env[i]);
		arg->env[i] = pwd;
		return (&(arg->env[i]));
	}
	i++;
}
return (NULL);
}
