#include "projectshell.h"

/**
 *  * find_command - this is a function believe me
 *   * @command: did you really will read this
 *    * @path: did you really will read this
 *     * Return: return pointer of string
 *     */

int find_command(char *command, char *path)
{
	    char *token;
	        char *full_path = NULL;
		    char *path_copy = strdup(path);
		        int found = 0;

			    token = custom_strtok(path_copy, ":");
			        while (token != NULL)
					    {
						            full_path = malloc(strlen(token) + strlen(command) + 2);
							            sprintf(full_path, "%s/%s", token, command);
								            if (access(full_path, X_OK) == 0)
										            {
												                found = 1;
														            break;
															            }
									            free(full_path);
										            token = custom_strtok(NULL, ":");
											        }
				    free(path_copy);
				        if (full_path != NULL)
						    {
							            strcpy(command, full_path);
								            free(full_path);
									        }
					    return (found);
}
