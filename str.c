/**
 * _strlen - finds the length of a string
 *
 * @s: string whose length is being evaluated
 *
 * Return: int, length of the string @s
 */
int _strlen(char *s)
{
	int i;

	i = 0;
	while (*(s + i) != '\0')
	{
		i++;
	}

	return (i);
}

/**
 * _strcpy - copies the string @src to @dest
 *
 * @src: source string
 * @dest: destination
 *
 * Return: char * - a char pointer
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings
 *
 * @s1: first string to be compared
 * @s2: second string to be compared
 *
 * Return: the numerical difference of the two strings
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;

	if (s1[i] == '\0' && s2[i] != '\0')
		return (0 - s2[i]);

	else if (s1[i] != '\0' && s2[i] == '\0')
		return (s1[i]);

	return (s1[i] - s2[i]);
}

/**
 * _strcat - concatenates two strings
 *
 * @dest: the string onto which @src is concatenated
 * @src: the string which is being concatenated to @dest
 *
 * Return: a pointer to @dest
 */
char *_strcat(char *dest, char *src)
{
	int i, length;

	length = 0;
	while (dest[length] != '\0')
		length++;

	i = 0;
	while (src[i] != '\0')
	{
		dest[length + i] = src[i];
		i++;
	}

	dest[length + i] = '\0';

	return (dest);
}


/**
 * _strdup - duplicates a string
 *
 * @str: string to be duplicated
 *
 * Return: pointer to duplicate string
 */
char *_strdup(char *str)
{
	char *copy;

	copy = malloc(_strlen(str) + 1);
	copy = _strcpy(str);

	return (copy);
}
