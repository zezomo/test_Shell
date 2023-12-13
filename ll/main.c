#include "projectshell.h"

/**
 *  * main - this is a function believe me
 *   * @argc: did you really will read this
 *    * @argv: did you really will read this
 *     * Return: return pointer of string
 *     */

int main(int argc, char **argv)
{
	    char *input = NULL;
	        size_t len = 0;
		    ssize_t read;
		        (void)argv;

			    if (argc == 1 && isatty(STDIN_FILENO))
				    	{
						        while (1)
										{
											            display_prompt();
												                read = custom_getline(&input, &len, stdin);
														            if (read == -1)
																    			{
																				                write(STDOUT_FILENO, "\n", 1);
																						                break;
																								            }
															                input[strcspn(input, "\n")] = 0;
																	            process_input(input);
																		            }
							    }
			    	else
						{
							        while ((read = custom_getline(&input, &len, stdin)) != -1)
											{
												            input[strcspn(input, "\n")] = 0;
													                process_input(input);
															        }
								    }
				    free(input);
				        return (0);
}


