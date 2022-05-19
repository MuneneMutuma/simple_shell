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
	size_t bufsize, argc;
	ssize_t characters = 0;
	int problem;

	thisfile = _getenv("_");
	buf = NULL;
	do {
		if (isatty(STDIN_FILENO))
			_printf("$ ");

		characters = getline(&buf, &bufsize, stdin);
		if (characters == -1)
		{
			_printf("\n");
			exit(EOF);
		}

		argv = (char **)malloc((_strlen(buf) + 1) * sizeof(argv));

		argc = tokenize(&argv, &buf, " \n");

		problem = error_handler(&argc, &argv, &thisfile);
		if (!problem)
			run(argv);
		if (!isatty(STDIN_FILENO))
			exit(0);

	} while (1);

	free(argv);
	free(buf);
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
	int status, err = 0;

	pid = fork();
	if (pid == 0)
	{
		err = execve(av[0], av, NULL);
		exit(err);
	}

	if (pid > 1)
	{
		wait(&status);
	}

	return (1);
}

/**
 * error_handler - utility function for handling errors in argv
 *
 * @ac: argument count
 * @av: argument vector
 * @thisfile: the current running file in env
 *
 * Return: 0 if no erro, return 1 when ac > 1 or av[0] does not exist
 */
int error_handler(size_t *ac, char ***av, char **thisfile)
{
	int state;
	struct stat sb;

	if (*ac > 1)
	{
		stat(" ", &sb);
		perror(*thisfile);
		return (1);
	}

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
 * @av: final array of tokens, NULL terminated
 * @buf: string to be tokenized
 * @delim: delimeter
 *
 * Return: number of tokens
 */
int tokenize(char ***av, char **buf, char *delim)
{
	int ac;
	char *token;

	for (ac = 0; ; ac++)
	{
		if (!ac)
			token = strtok(*buf, delim);
		else
			token = strtok(NULL, delim);

		if (token == NULL)
		{
			*av[ac] = token;
			break;
		}
		*av[ac] = token;
	}

	return (ac);
}
