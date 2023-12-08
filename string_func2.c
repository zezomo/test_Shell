#include "main.h"
/**
 * atos - fucntion that is mintioned in another code
 * Description: for simple shell task
 * @str: an argument
 * @number: an argument
 * Return: Always 0.
 */
void atos(char *str, int number)
{
	int i, length, n = 0;

	n = number;
	if (!n)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	for (length = 0; n != 0; length++)
	{
		length++;
		n /= 10;
	}
	for (i = 0; i < length; i++)
	{
		str[length - (i + 1)] = number % 10 + '0';
		number /= 10;
	}
	str[length] = '\0';
}
/**
 * _strncmp - fucntion that is mintioned in another code
 * Description: for simple shell task
 * @str1: an argument
 * @str2: an argument
 * @n: an argument
 * Return: Always 0.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
while (n-- && (*str1 != '\0' || *str2 != '\0'))
{
if (*str2 != *str1)
return (*str1 - *str2);
str1++;
str2++;
}
return (0);
}
/**
 * _atoi - fucntion that is mintioned in another code
 * Description: for simple shell task
 * @s: an argument
 * Return: Always 0.
 */
int _atoi(char *s)
{
unsigned int number = 0;
int sign = 1;

do {
if (*s == '-')
sign *= -1;
else if (*s >= '0' && *s <= '9')
number = (number * 10) + (*s - '0');
else if (number > 0)
break;
} while (*s++);

return (number *sign);
}
/**
 * _strdup - function is called ny another file called main.c
 * Description: for alx project malloc
 * @arg: an argument
 * @str: 'size' is int recieved from another function
 * Return: 0 on success
 */
char *_strdup(_arg *arg, char *str)
{
int i, length;
char *temp;

if (!str)
	return (NULL);
length = _strlen(str);
temp = malloc(length + 1);
if (!temp)
prog_exit(arg);
for (i = 0; i <= length; i++)
{
	temp[i] = str[i];
}
return (temp);
}
