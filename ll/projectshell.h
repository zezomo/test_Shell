#ifndef PROJECTSHELL_H
#define PROJECTSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define BUFFER_SIZE 1024

extern char **environ;


void execute_command(char *command, char **arguments, char **envp);
int find_command(char *command, char *path);
void process_input(char *input);
void display_prompt(void);
void handle_env_command(char **tokens);
void handle_exit_command(char **tokens);
void handle_any_command(char **tokens);
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);
char *custom_strtok(char *str, const char *delim);


#endif
