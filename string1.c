#include "shell.h"

/**
 * s_strdup - function to duplicate a string
 * @string: the string to copy
 * Return: the string back
 */
char *s_strdup(const char *string)
{
	int len = s_strlen(string);
	char *copy;

	if (string == NULL)
		return (NULL);

	copy = malloc(len + 1);

	if (copy == NULL)
		return (NULL);

	s_strcpy(copy, string);
	return (copy);
}
/**
 * s_strlen - function to return the length of string
 * @string: the string
 * Return: the length of the string
 */
int s_strlen(const char *string)
{
	int index = 0;

	while (string[index] != '\0')
		index++;
	return (index);
}

/**
 * s_strcspn - function that return the index of the first occurence of char
 * @string: the string to search
 * @chr: the character to search for
 * Return: the index of the search
 */
int s_strcspn(const char *string, const char *chr)
{
	int index = 0;

	while (string[index] != '\0')
	{
		int charindex = 0;
			while (chr[charindex] != '\0')
			{
				if (string[index] == chr[charindex])
					return (index);
				charindex++;
			}
		index++;
	}
	return (index);
}

/**
 * s_strcpy - fuction to copy content of one string to another
 * @dest_string: the destination string
 * @src_string: the source string
 * Return: pointer to destination string
 */
char *s_strcpy(char *dest_string, const char *src_string)
{
	while (*src_string != '\0')
	{
		*dest_string = *src_string;
		dest_string++;
		src_string++;
	}

	*dest_string = '\0';
	return (dest_string);
}
