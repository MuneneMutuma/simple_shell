/**
 * _memset - fills the first n bytes of memory area pointed to by s
 *
 * @s: pointer to memory area to be filled
 * @b: character to fill @s
 * @n: number of @b's to fill @s
 *
 * Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i, j;

	i = 0;
	while (s[i] != '\0')
		i++;

	for (j = 0; j < n; j++)
	{
		s[j] = b;
	}

	return (s);
}

/**
 * _memcpy - copies n memory values from source to destination
 *
 * @dest: pointer to destination string
 * @src: pointer to source string
 * @n: the number of characters being copied
 *
 * Return: pointer to @dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}
