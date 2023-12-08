#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define init {0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL}
/**
 * struct _arg - for arguments handling
 * @token: an argument
 * @exit_st: an argument
 * @pid: an argument
 * @fd: an argument
 * @num_path: an argument
 * @i: an argument
 * @command: an argument
 * @prog_name: an argument
 * @path: an argument
 * @old_path: an argument
 * @pwd: an argument
 * @env: an argument
 * Description: singly linked list node structure
 */
typedef struct _arg
{
	int token;
	int exit_st;
	int pid;
	int fd;
	int num_path;
	int i;
	char *command;
	char *prog_name;
	char *path;
	char *old_path;
	char **pwd;
	char **env;
} _arg;

void initialize_args(_arg *arg, int argc, char **argv, char **env);
int _putchar(char c);
void new_line(int signal);
int command_getter(_arg *arg, int point, int *dot);
void input_exit(_arg *arg, int point);
int token_maker(char *command, char *sign);
char *_strtok(char *str, const char *sign);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
void prog_exit(_arg *arg);
ssize_t line_getter(_arg *arg);
char *realloc_handler(_arg *arg, char *temp, int *buff, int i, int m);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
int input_helper(_arg *arg);
void atos(char *str, int number);
char *_env(char **enviroment, char *env, int length);
int _strncmp(const char *str1, const char *str2, size_t n);
void sign_handler(char *temp, char **sign, _arg *arg);
void spacing(char **command, _arg *arg);
void dotaizing(char **command, _arg *arg);
int _atoi(char *s);
int exit_func(_arg *arg);
void pwd_ch(_arg *arg);
int _cd(_arg *arg);
int _env2(_arg *arg);
int compare_backward(char *str1, char *str2);
int _execve(_arg *arg, char *buffer);
int command_maker(_arg *arg);
char **pwd_getter(_arg *arg);
char *_strdup(_arg *arg, char *str);


#endif
