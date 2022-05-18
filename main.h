#ifndef MAIN_H
#define MAIN_H

extern char **environ;

int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strdup(char *str);
char *_which(char *str);
char *_getenv(char *path);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int i);

#endif
