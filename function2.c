#include "shell.h"

/**
 * set_env_var - function to implement setenv
 * @var: the variable name to set
 * @value: the value to set it to
 * Return: 0 for success and 1 otherwise
 */
int set_env_var(char *var, char *value)
{
	char *memory_alloc = malloc(s_strlen(value) + 1);

	if (memory_alloc == NULL)
		return (1);
	s_strcpy(memory_alloc, value);

	if (setenv(var, memory_alloc, 1) != 0)
	{
		free(memory_alloc);
		return (1);
	}
	free(memory_alloc);
	return (0);
}

/**
 * unset_env - function to implement unsetenv
 * @var: the variable to unset
 * Return: 0 for success 1 otherwise
 */
int unset_env(char *var)
{
	if (unsetenv(var) != 0)
		return (1);
	return (0);
}
/**
 * token_command - function to tokenize command
 * @user_command: the user command
 * @args: array to store the command and arg
 * Return: the number of tokenize arg
 */
int token_command(char *user_command, char *args[])
{
	int index;
	char *copy = user_command;
	char *mytok = s_strtok(copy, TOK_DELIM);

	for (index = 0; mytok != NULL; index++)
	{
		args[index] = mytok;
		mytok = s_strtok(NULL, TOK_DELIM);
	}
	args[index] = NULL;

	return (index);
}

/**
 * setenv_cmd - function to set environment variable
 * @user_command: the user command to check
 * Return: 0 for success
 */
int setenv_cmd(char *user_command)
{
	char *cmd_and_args[3];
	int tk_cnt = token_command(user_command, cmd_and_args);

	if (tk_cnt < 1)
		return (-1);

	if (s_strcmp(cmd_and_args[0], "setenv") == 0)
	{
		if (cmd_and_args[1] == NULL || cmd_and_args[2] == NULL)
			return (1);
		return (set_env_var(cmd_and_args[1], "myvalue"));
	}
	return (-1);
}
/**
 * unsetenv_cmd - function to unset an envrionment variable
 * @user_command: the user command passed
 * Return: 0 for success
 */
int unsetenv_cmd(char *user_command)
{
	char *cmd_and_args[2];
	int tk_cnt = token_command(user_command, cmd_and_args);

	if (tk_cnt < 1)
		return (-1);

	if (s_strcmp(cmd_and_args[0], "unsetenv") == 0)
	{
		if (cmd_and_args[1] == NULL)
			return (1);
		return (unset_env(cmd_and_args[1]));
	}
	return (-1);
}
