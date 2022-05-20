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
	char *delim = " \n";
	size_t  bufsize, argc;
	ssize_t characters = 0;
	int problem, exit_code = 0;

	thisfile = _getenv("_");
	buf = NULL;
	do {
		argv = (char **)NULL;
		if (isatty(STDIN_FILENO))
			_printf("$ ");
		characters = getline(&buf, &bufsize, stdin);
		if (_strcmp(buf, "exit\n") == 0)
			exit_code = 1;
		if (characters == -1)
			exit_code = -1;
		if (exit_code)
			break;
		if (_strcmp(buf, "\n") == 0)
			continue;
		argv = tokenize(&buf, &delim);
		for (argc = 0; argv[argc]; argc++)
			;
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
char **tokenize(char **buf, char **delim)
{
	int ac;
	char *token, **line;

	line = (char **)malloc((strlen(*buf) + 1) * sizeof(line));
	token = NULL;
	for (ac = 0; ; ac++)
	{
		if (!ac)
			token = strtok(*buf, *delim);
		else
			token = strtok(NULL, *delim);

		if (token == NULL && ac > 0)
		{
			break;
		}
		line[ac] = token;
	}

	return (line);
}
