#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
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
		printf("$ ");
		getline(&buf, &bufsize, stdin);
		argv = (char **)malloc((_strlen(buf) + 1) * sizeof(argv));
		_printf("%s", buf);
		for (argc = 0; ; argc++)
		{
			exit_code = 1;
			if (!argc)
				token = strtok(buf, " ");
			else
				token = strtok(NULL, " ");
			if (token == NULL)
				break;

			argv[argc] = token;
		}
		exit_code = 0;
	} while (_strcmp(buf, "exit\n") != 0 && !exit_code);

	free(argv);
	free(buf);
	return (0);
}

