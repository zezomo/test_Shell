#include "main.h"
/**
 * _strcmp - compares strings
 * Description: for alx project simple shell
 * @s1: '*s1' is a pointer
 * @s2: '*s2' is a pointer
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
while (*s1 && *s2)
{
if (*s1 != *s2)
{
return (*s1 - *s2);
}
s1++;
s2++;
}
if (*s1 == *s2)
return (0);
else
return (*s1 - *s2);
}
/**
 * _strlen - calulate the length of string
 * Description: for alx project simple shell
 * @s: '*s' is a pointer
 * Return: length of string
 */
int _strlen(char *s)
{
	int length = 0;

	while (s[length])
	{
		length++;
	}
	return (length);
}
/**
 * _strcat - fucntion that is mintioned in another code
 * Description: function to do task for alx
 * @dest: '*dest' is a pointer
 * @src: '*src' is a pointer
 * Return: Always 0.
 */
char *_strcat(char *dest, char *src)
{
int length1 = 0;
int length2 = 0;

while (dest[length1] != 0)
length1++;
while (src[length2] != 0)
{
dest[length1 + length2] = src[length2];
length2++;
}
dest[length1 + length2] = '\0';
return (dest);
}
/**
 * _strncat - fucntion that is mintioned in another code
 * Description: function to do task for alx
 * @dest: '*dest' is a pointer
 * @n: 'n' is an integer
 * @src: '*src' is a pointer
 * Return: Always 0.
 */
char *_strncat(char *dest, char *src, int n)
{
int length1 = 0;
int length2 = 0;

while (dest[length1] != 0)
length1++;
while (src[length2] != 0 && length2 < n)
{
dest[length1] = src[length2];
length1++;
length2++;
}
return (dest);
}
/**
 * _strchr - fucntion that is mintioned in another code
 * Description: function to do task for alx
 * @s: '*s' is a pointer
 * @c: 'n' is an integer
 * Return: Always 0.
 */
char *_strchr(char *s, char c)
{
int i = 0;
while (s[i] != 0)
{
if (s[i] == c)
return (s + i);
i++;
}
if (s[i] == c)
	return (s + i);
return ('\0');
}
