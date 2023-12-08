#include "main.h"
/**
 * prog_exit - to exit program with no leaks
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
void prog_exit(_arg *arg)
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
	exit(255);
}
