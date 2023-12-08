#include "main.h"
/**
 * _strtok - function is called ny another file called main.c
 * Description: for alx project malloc
 * @sign: an argument
 * @str: an argument
 * Return: 0 on success
 */
char *_strtok(char *str, const char *sign)
{
	char *token;
	static char *final;

if (str)
final = str;
else if (final == NULL)
return (NULL);
token = final;
while (*final != '\0')
{
if (*sign == *final)
{
*final = '\0';
final++;
return (token);
}
final++;
}
final = NULL;
return (token);
}
