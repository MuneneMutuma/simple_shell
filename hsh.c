#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "main.h"
#include "printf.h"

/**
 * main - shell entry point
 *
 * Return: 0
 */
int main(void)
{
	char *buf, **argv, *thisfile;
	size_t  bufsize = BUFSIZ;
	ssize_t characters = 0;
	int problem, exit_code = 0;

	thisfile = _getenv("_");
	buf = (char *)malloc(bufsize * sizeof(char));
	do {
		argv = (char **)NULL;
		if (isatty(STDIN_FILENO))
			_printf("$ ");
		characters = getline(&buf, &bufsize, stdin);
		buf[_strlen(buf) - 1] = '\0';
		if (characters == -1)
			exit_code = -1;
		if (exit_code)
			break;
		if (_strcmp(buf, "\n") == 0)
			continue;
		argv = tokenize(&buf);
		problem = error_handler(&argv, &thisfile);
		if (!problem)
			run(argv);
		if (!isatty(STDIN_FILENO))
			exit(0);
		free(argv);
	} while (exit_code != 1);
	free(thisfile);
	free(buf);
	free(argv);
	if (exit_code == -1)
	{
		_printf("\n");
		exit(EOF);
	}
	return (0);
}

/**
 * run - utility function to run child process of shell
 *
 * @av: argument vector
 *
 * Return: 1 always
 */
int run(char **av)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(-1);
	}
	else if (pid == 0)
	{
		if (execve(av[0], av, NULL) == -1)
		{
			perror("Error");
			exit(-1);
		}
	}

	else
		wait(&status);

	return (1);
}

/**
 * error_handler - utility function for handling errors in argv
 *
 * @av: argument vector
 * @thisfile: the current running file in env
 *
 * Return: 0 if no erro, return 1 when ac > 1 or av[0] does not exist
 */
int error_handler(char ***av, char **thisfile)
{
	int state;
	struct stat sb;


	if (!*av[0])
		return (1);

	state = stat(*av[0], &sb);
	if (state != 0)
	{
		perror(*thisfile);
		return (1);
	}

	return (0);
}

/**
 * tokenize - utility function to tokenize a string using a delimeter
 *
 * @buf: string to be tokenized
 * @delim: delimeter
 *
 * Return: array of string tokens
 */
char **tokenize(char **buf)
{
	int ac = 0;
	char *token, **line;
	char *delim = " ";

	line = (char **)malloc((strlen(*buf) + 1) * sizeof(char *));
	token = NULL;

	token = strtok(*buf, delim);
	while (token != NULL)
	{
		line[ac] = token;
		token = strtok(NULL, delim);
		ac++;
	}
	line[ac] = NULL;

	return (line);
}
