#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "main.h"

/**
 * _which - checks for file in the PATH
 *
 * @file: file to be checked on PATH
 *
 * Return: full path to file if in path, else NULL
 */
char *_which(char *file)
{
	char *path, **list, *token, *filename = '\0';
	size_t i, len;
	unsigned int k;
	struct stat st;

	path = _getenv("PATH");
	list = (char **)malloc(_strlen(path) * sizeof(list));

	for (i = 0; ; path = NULL, i++)
	{
		token = strtok(path, ": ");
		if (token == NULL)
			break;
		list[i] = token;
	}

	for (k = 0; list[k]; k++)
	{
		len = _strlen(list[k])  + _strlen(file) + 1;
		filename = realloc(filename, len * sizeof(filename));
		_strcat(filename, list[k]);
		_strcat(filename, "/");
		_strcat(filename, file);
		if (stat(filename, &st) == 0)
		{
			printf("%s\n", filename);
			free(list);
			return (filename);
		}
		_memset(filename, '\0', 1);
	}

	free(list);
	return (NULL);
}

/**
 * _getenv - get envrionment variable
 *
 * @name: name of the environment variable
 *
 * Return: value of the environment variable
 */
char *_getenv(char *name)
{
	char *buf, *token, *value;
	unsigned int i = 0;

	value = "\0";
	while (environ[i])
	{
		for (buf = environ[i]; ; buf = NULL)
		{
			token = strtok(buf, "=");
			if (token == NULL)
			{
				break;
			}
			if (_strcmp(name, value) == 0)
			{
				free(value);
				value = _strdup(token);
				return (value);
			}
			if (_strcmp(token, name) == 0)
			{
				value = _strdup(token);
			}
		}
		i++;
	}
	free(buf);
	return (NULL);
}

/**
 * _setenv - sets environment variable
 *
 * @name: name of the variable
 * @value: value of the variable
 * @overwrite: if 0 don't overwrite, otherwise overwrite
 *
 * Return: 0 if not overwritten, 1 if overwritten
 */
int _setenv(char *name, char *value, int overwrite)
{
	char *newenv, *test, *buf, *token;
	int i;
	size_t len;

	len = (_strlen(name) + _strlen(value) + 3);
	newenv = malloc(len);
	_memset(newenv, '\0', len);
	buf = "\0";

	test = _getenv(name);

	_strcat(newenv, name);
	_strcat(newenv, "=");
	_strcat(newenv, value);

	printf("%s\n", environ[0]);
	if (test && overwrite)
	{
		for (i = 0; environ[i]; i++)
		{
			buf = _strdup(environ[i]);
			token = strtok(buf, "=");
			if (_strcmp(token, name) == 0)
			{
				environ[i] = _memcpy(environ[i], newenv, _strlen(newenv) + 1);
			}
			free(buf);
		}
	}

	if (!test)
	{
		environ[i] = newenv;
		return (0);
	}
	free(newenv);
	free(test);
	return (1);
}

/**
 * _unsetenv - unsets an environment variable
 *
 * @name: environment variable to be unset
 *
 * Return: 0 if name is not set, 1 if name is unset
 */
int _unsetenv(char *name)
{
	char *buf, *token, *test;
	int i;

	test = _getenv(name);

	if (!test)
		return (0);

	for (i = 0; environ[i]; i++)
	{
		buf = _strdup(environ[i]);
		token = strtok(buf, "=");
		if (_strcmp(token, name) == 0)
		{
			for (; environ[i]; i++)
				environ[i] = environ[i + 1];

			break;
		}
		free(buf);
	}

	for (i = 0; environ[i]; i++)
		printf("[%d]: %s\n", i, environ[i]);

	free(buf);
	free(test);
	return (1);
}
