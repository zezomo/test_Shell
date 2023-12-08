#include "main.h"
/**
 * pwd_ch - change pwd
 * Description: for simple shell task
 * @arg: an argument
 * Return: 1 on sucess
*/
void pwd_ch(_arg *arg)
{
	char temp[256];
	char *pwd = malloc(256);

if (!pwd)
prog_exit(arg);
getcwd(temp, 256);
pwd[0] = '\0';
_strcat(pwd, "PWD=");
_strcat(pwd, temp);
free(*(arg->pwd));
*(arg->pwd) = pwd;
}
/**
 * compare_backward - compare in reverse
 * Description: for simple shell task
 * @str1: an argument
 * @str2: an argument
 * Return: 1 on sucess
*/
int compare_backward(char *str1, char *str2)
{
int length1, length2, i = 0;

length2 = (_strlen(str2) - 1);
length1 = (_strlen(str1) - 1);
if (length2 > length1)
return (0);
for (i = length2; i >= 0; i--)
{
if (str1[length1] != str2[i])
return (0);
length1--;
}
return (1);
}
