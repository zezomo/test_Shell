#include "main.h"
/**
 * line_getter - to help in simple shell
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
ssize_t line_getter(_arg *arg)
{
	ssize_t bytes;
	int buff = 10240;
	size_t i = 0;
	char *temp;

	if (!(&(arg->command)))
		return (-1);
	temp = malloc(buff + 1);
	if (!temp)
	{
		prog_exit(arg);
	}
	if (arg->command)
	{
		free(arg->command);
		arg->command = NULL;
	}
	bytes = read(arg->fd, temp + i, 1);
	while (bytes > 0)
	{
		i++;
		temp = realloc_handler(arg, temp, &buff, 2048, i);
		if (temp[i - 1] == '\n' || temp[i - 1] == ';')
			break;
		bytes = read(arg->fd, temp + i, 1);
	}
	if (bytes < 0 || (!bytes && !i))
	{
		free(temp);
		return (-1);
	}
	if (bytes != 8)
		temp[i] = '\0';
	arg->command = temp;
	return (i);
}
