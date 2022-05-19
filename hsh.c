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
	char *buf, **argv, *token, *thisfile;
	size_t bufsize, argc;
	ssize_t characters;
	int problem;

	thisfile = _getenv("_");
	buf = NULL;
	do {
		_printf("$ ");
		characters = getline(&buf, &bufsize, stdin);
		if (characters == -1)
		{
			_printf("\n");
			exit(EOF);
		}

		argv = (char **)malloc((_strlen(buf) + 1) * sizeof(argv));
		for (argc = 0; ; argc++)
		{
			if (!argc)
				token = strtok(buf, " \n");
			else
				token = strtok(NULL, " \n");
			if (token == NULL)
			{
				argv[argc] = token;
				break;
			}
			argv[argc] = token;
		}

		problem = error_handler(&argc, &argv, &thisfile);
		if (!problem)
			run(argv);

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

	state = stat(*av[0], &sb);
	if (state != 0)
	{
		perror(*thisfile);
		return (1);
	}

	return (0);
}
