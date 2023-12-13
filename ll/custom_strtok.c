#include "projectshell.h"

/**
 *  * custom_strtok - this is a function believe me
 *   * @str: did you really will read this
 *    * @delim: did you really will read this
 *     * Return: return pointer of string
 *     */

char *custom_strtok(char *str, const char *delim)
{
	    static char *saveptr = NULL;
	        char *token;
		    char *p;

		        if (str != NULL)
				    {
					            saveptr = str;
						        }
			    if (saveptr == NULL || *saveptr == '\0')
				        {
						        return NULL;
							    }
			        saveptr += strspn(saveptr, delim);
				    if (*saveptr == '\0')
					        {
							        return NULL;
								    }
				        token = saveptr;
					    p = strpbrk(saveptr, delim);
					        if (p != NULL)
							    {
								            *p = '\0';
									            saveptr = p + 1;
										        }
						    else
							        {
									        saveptr += strlen(saveptr);
										    }

						        return (token);
}
