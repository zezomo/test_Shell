#include "projectshell.h"


/**
 *  * handle_env_command - this is a function believe me
 *   * @tokens: did you really will read this
 *    * Return: return pointer of string
 *    */


void handle_env_command(char **tokens)
{
	    char **envp = environ;


	      if (tokens[1] != NULL)
		        {
				    fprintf(stderr, "env: unexpected arguments\n");
				        return;
					  }


	        while (*envp != NULL)
			  {
				      printf("%s\n", *envp);
				          envp++;
					    }
}

/**
 *  * handle_exit_command - this is a function believe me
 *   * @tokens: did you really will read this
 *    * Return: return pointer of string
 *    */

void handle_exit_command(char **tokens)
{
	     int exit_status;

	         if (strcmp(tokens[0], "exit") == 0)
			     {
				             if (tokens[1] != NULL)
						             {
								                 exit_status = atoi(tokens[1]);
										             exit(exit_status);
											             }
					             else
							             {
									                 exit(0);
											         }
						         }
}

/**
 *  * handle_any_command - this is a function believe me
 *   * @tokens: did you really will read this
 *    * Return: return pointer of string
 *    */

void handle_any_command(char **tokens)
{
	  char *command = tokens[0];
	    char *path;

	      if (access(command, X_OK) != 0)
		        {
				    path = getenv("PATH");
				        if (path != NULL && find_command(command, path))
						    {
							          tokens[0] = command;
								      }
					    else if
						          (strcmp(command, "env") == 0)
								      {
									            handle_env_command(tokens);
										          return;
											      }
					        else
							    {
								          fprintf(stderr, "%s: command not found\n", command);
									        return;
										    }
						  }
	        execute_command(tokens[0], tokens, environ);
}

/**
 *  * process_input - this is a function believe me
 *   * @input: did you really will read this
 *    * Return: return pointer of string
 *    */

void process_input(char *input)
{
	  char *token;
	    char *tokens[MAX_ARGUMENTS + 2];
	      int token_count = 0;

	        token = custom_strtok(input, " ");
		  while (token != NULL && token_count < MAX_ARGUMENTS + 1)
			    {
				        tokens[token_count++] = token;
					    token = custom_strtok(NULL, " ");
					      }
		    tokens[token_count] = NULL;
		      if (token_count > 0)
			        {
					    if (strcmp(tokens[0], "env") == 0)
						        {
								      handle_env_command(tokens);
								          }
					        else if (strcmp(tokens[0], "exit") == 0)
							    {
								          handle_exit_command(tokens);
									      }
						    else
							        {
									      handle_any_command(tokens);

									          }
						      }
}

