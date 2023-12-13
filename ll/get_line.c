#include "projectshell.h"

/**
 *  * custom_getline - this is a function believe me
 *   * @argc: did you really will read this
 *    * @argv: did you really will read this
 *     * Return: return pointer of string
 *     */

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	        size_t i = 0;
		    int c;
		        if (!*lineptr) {
				        *lineptr = malloc(BUFFER_SIZE);
					        if (!*lineptr) {
							            perror("malloc");
								                exit(EXIT_FAILURE);
										        }
						        *n = BUFFER_SIZE;
							    }


			    while ((c = fgetc(stream)) != EOF && c != '\n') {
				            if (i == *n - 1) {
						                *lineptr = realloc(*lineptr, *n + BUFFER_SIZE);
								            if (!*lineptr) {
										                    perror("realloc");
												                    exit(EXIT_FAILURE);
														                }
									                *n += BUFFER_SIZE;
											        }
					            (*lineptr)[i++] = c;
						        }

			        if (i > 0 && (*lineptr)[i - 1] == '\r') {
					        (*lineptr)[i - 1] = '\0';
						    } else {
							            (*lineptr)[i] = '\0';
								        }

				    return (c == EOF && i == 0) ? -1 : (ssize_t)i;
}

