#include "shell.h"

/**
 * s_strcat - function to concatenate two strings
 * @dest: the destination string
 * @src: the source string to append to dest
 * Return: pointer to the destination string 'dest'
 */
char *s_strcat(char *dest, const char *src)
{
	char *temp = dest;

	while (*temp != '\0')
	{
		temp++;
	}

	while (*src != '\0')
	{
		*temp = *src;
		temp++;
		src++;
	}
	*temp = '\0';

	return (dest);
}

/**
 * s_strcmp - function to compare two strings
 * @str1: the first string
 * @str2: the second string
 * Return: 0 if 'str1' and 'str2' are equal, a negative
 * value if 'str1' < 'str2', or a positive value if 'str1' > 'str2'
 */
int s_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	return (*str1 - *str2);
}

/**
 * s_strstr - function to perform strstr functionality
 * @str: the string to search from
 * @find: what to search from the string
 * Return: the string if found
 */
char *s_strstr(const char *str, const char *find)
{
	if (!*find)
	{
		return ((char *)str);
	}
	while (*str)
	{
		const char *h = str;
		const char *n = find;

		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}
		if (!*n)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

/**
 * print_err - function to print err
 * @command: the command enter
 * @argv: program name
 * Return: void
 */
void print_err(const char *command, char *argv)
{
	const char *not_found_msg = ": not found\n";
	const char *new = ": 1: ";

	write(STDERR_FILENO, argv, s_strlen(argv));
	write(STDERR_FILENO, new, s_strlen(new));
	write(STDERR_FILENO, command, s_strlen(command));
	write(STDERR_FILENO, not_found_msg, s_strlen(not_found_msg));
}

