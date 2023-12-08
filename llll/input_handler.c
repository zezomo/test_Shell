#include "main.h"
/**
 * input_helper - to help in simple shell
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
int input_helper(_arg *arg)
{
char *temp, *sign, *st, *h = _strchr(arg->command, '#');
int len_tmp, len_st, buff = 10240;

if (h && ((h != arg->command && *(h - 1) == ' ') || h == arg->command))
	*h = '\0';
temp = malloc(10240);
if (!temp)
	prog_exit(arg);
sign = _strchr(arg->command, '$');
st = arg->command;
temp[0] = '\0';
len_tmp = _strlen(temp);
while (sign != NULL)
{
	temp = realloc_handler(arg, temp, &buff, 1024, len_tmp + sign - st);
	_strncat(temp, st, (sign - st));
	sign_handler(temp, &sign, arg);
	st = sign;
	sign = _strchr(st, '$');
}
len_tmp = _strlen(temp);
len_st = _strlen(st);
temp = realloc_handler(arg, temp, &buff, 128, len_tmp + len_st);
_strcat(temp, st);
spacing(&temp, arg);
dotaizing(&temp, arg);
free(arg->command);
arg->command = temp;
if (temp[0] == '\0')
	return (1);
else
	return (0);
}
/**
 * sign_handler - to help in simple shell
 * Description: for simple shell task
 * @temp: an argument
 * @sign: an argument
 * @arg: an argument
 * Return: 1 on sucess
*/
void sign_handler(char *temp, char **sign, _arg *arg)
{
char number[10], *env;
int i = 0;

(*sign)++;
if ((*sign)[0] == '?' || (*sign)[0] == '$')
{
if ((*sign)[0] == '?')
atos(number, arg->exit_st);
else
atos(number, arg->pid);
_strcat(temp, number);
(*sign)++;
}
else
{
while ((*sign)[i] && (*sign)[i] != ' '
&& (*sign)[i] != '#' && (*sign)[i] != '$' && (*sign)[i] != '/')
i++;
if (i)
{
env = _env(arg->env, *sign, i);
if (env)
_strcat(temp, env);
*sign += i;
}
else
_strcat(temp, "$");
}
}
/**
 * _env - to help in simple shell
 * Description: for simple shell task
 * @enviroment: an argument
 * @env: an argument
 * @length: an argument
 * Return: 1 on sucess
*/
char *_env(char **enviroment, char *env, int length)
{
	int i = 0, flag;

	while (enviroment[i] != NULL)
	{
		flag = _strncmp(enviroment[i], env, length);
		if (flag == 0)
			return (&enviroment[i][length + 1]);
		i++;
	}
	return (NULL);
}
/**
 * spacing - to help in simple shell
 * Description: for simple shell task
 * @command: an argument
 * @arg: an argument
 * Return: 1 on sucess
*/
void spacing(char **command, _arg *arg)
{
int x = 0, y = 0, len_comm;
char *temp = NULL;

len_comm = _strlen(*command);
temp = malloc(len_comm + 1);
if (temp == NULL)
{
free(*command);
prog_exit(arg);
}
while ((*command)[x] && (*command)[x] == ' ')
x++;
while ((*command)[x])
{
if ((*command)[x] == ' ')
{
temp[y] = ' ';
y++;
while ((*command)[x] == ' ')
x++;
}
else
{
temp[y] = (*command)[x];
x++;
y++;
}
}
if (y && temp[y - 1] == ' ')
	y--;
temp[y] = '\0';
free(*command);
*command = temp;
}
/**
 * dotaizing - to help in simple shell
 * Description: for simple shell task
 * @command: an argument
 * @arg: an argument
 * Return: 1 on sucess
*/
void dotaizing(char **command, _arg *arg)
{
int i = 0, length;
char *temp, *cpy = *command;

if (cpy[0] == '.')
{
temp = malloc(512);
if (!temp)
{
free(command);
prog_exit(arg);
}
temp[0] = '\0';
_strcat(temp, &((*(arg->pwd))[4]));
length = _strlen(temp);
while (cpy[i] != ' ' && cpy[i])
{
if (cpy[i] == '.' && cpy[i + 1] == '.')
{
for (; length > 0 && temp[length - 1] != '/'; length--)
temp[length - 1] = '\0';
temp[(length--) - 1] = '\0';
i++;
}
else if (cpy[i] != '/' && cpy[i] != '.')
{
temp[length++] = '/';
while (cpy[i] && cpy[i] != '/' && cpy[i] != ' ')
temp[length++] = cpy[i++];
i--;
}
i++;
}
temp[length] = '\0';
if (access(temp, X_OK) == 0)
{
_strcat(temp, &cpy[i]);
free(*command);
*command = temp;
}
}
}
