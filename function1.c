#include "shell.h"

/**
 * prompt - function to print $
 * @c: character pass
 * @len: length of the string
 * Return: void
 */
void prompt(char *c, int len)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, c, len);
}

/**
 * take_input - function to take command input
 * @input: th command to use
 * Return: return void
 */
ssize_t take_input(char *input)
{
	ssize_t read_bytes = read(STDIN_FILENO, input, INPUT_SIZE);

	return ((read_bytes == -1) ? -1
		: (read_bytes == 0) ? 0
		: (input[read_bytes] = '\0', read_bytes));
}


/**
 * exitShell - function to create an exitfunction
 * @status: the status code if any
 * Return: void
 */
void exitShell(int status)
{
	exit(status);
}


/**
 * chk_cmd_before_fork - function to check before creating fork
 * @user_command: the command to check
 * Return: 0 for success and 1 otherwise
 */
int chk_cmd_before_fork(char *user_command)
{
	char *path_lookup, *duplicate, *store_path;

	path_lookup = getenv("PATH");

	if (path_lookup == NULL)
		return (-1);

	duplicate = s_strdup(path_lookup);
	if (duplicate == NULL)
		return (-1);

	store_path = s_strtok(duplicate, ":");

	for (; store_path != NULL ;)
	{
		char abs_path[PATH_SIZE];

		s_strcpy(abs_path, store_path);
		s_strcat(abs_path, "/");
		s_strcat(abs_path, user_command);

		if (access(abs_path, X_OK) == 0)
		{
			free(duplicate);
			return (0);
		}
		store_path = s_strtok(NULL, ":");
	}
	free(duplicate);
	return (1);
}

/**
 * signal_handler - function to handle signal
 * @signal: the signal
 * Return: void
 */
void signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		prompt("$ ", s_strlen("$ "));
		fflush(stdout);
	}
}
