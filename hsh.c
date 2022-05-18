#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"
#include "printf.h"

/**
 * main - shell entry point
 *
 * Return: 0
 */
int main(void)
{
	char *buf, **argv, *token;
	size_t bufsize, argc;
	int exit_code;

	buf = NULL;
	do {
		_printf("$ ");
		getline(&buf, &bufsize, stdin);
		argv = (char **)malloc((_strlen(buf) + 1) * sizeof(argv));
		for (argc = 0; ; argc++)
		{
			exit_code = 1;
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
		run(argv);
		exit_code = 0;
	} while (_strcmp(buf, "exit") != 0 && !exit_code);

	free(argv);
	free(buf);
	return (0);
}

int run(char **av)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(av[0], av, NULL);
		exit(0);
	}

	if (pid > 1)
	{
		wait(&status);
	}

	return (0);
}
