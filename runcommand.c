#include "shell.h"

/**
 * run_command - function for run_command
 * @user_command: the user input
 * @argv: the program name
 * @envp: parent environment
 * Return: status
 */
int run_command(char *user_command, char *argv, char *envp[])
{
	int handled = 0;
	int i, last_status = 0;
	char *cmd_list[ARG_SIZE];
	int num_cmd = 0;
	char *copy = strdup(user_command);
	char *cmd_token = s_strtok(user_command, ";\n");

	while (cmd_token != NULL)
	{
		if (!is_whitespace_string(cmd_token))
		{
			cmd_list[num_cmd] = cmd_token;
			num_cmd++;
		}
		cmd_token = s_strtok(NULL, ";\n");
	}

	for (i = 0; i < num_cmd; i++)
	{
		char *mycmd = cmd_list[i];
		char *args[ARG_SIZE];
		int check = token_command(mycmd, args);

		replace_status_variable(args, check, &last_status);
		handled = handle_noninbuilt_cmd(mycmd, args, check,
				&last_status, argv, envp);
		if (handled != 1)
			return (handled);
		execute_logical_commands(copy, args, check,
				&last_status, argv, envp);
	}
	free(copy);
	return (last_status);
}

/**
 * split_logical_operator - function to split logic operand
 * @input: user input
 * @delimiter: delimiter to sepperate user input
 * @output: where to store it
 * Return: the number of seperated command
 */
int split_logical_operator(char *input, const char *delimiter, char *output[])
{
	int num_parts = 0;
	char *token = s_strtok(input, delimiter);

	while (token != NULL)
	{
		output[num_parts] = token;
		num_parts++;
		token = s_strtok(NULL, delimiter);
	}
	return (num_parts);
}

/**
 * execute_logical_commands - function to perform logical function
 * @copy: the command
 * @args: the argument
 * @check: to check the command for inbuilt
 * @last_status: the status code
 * @argv: the program name
 * @envp: parent environment
 * Return: void
 */
void execute_logical_commands(char *copy, char *args[], int check,
		int *last_status, char *argv, char *envp[])
{
	if (s_strstr(copy, "&&"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int num_parts = split_logical_operator(copy, "&&", cmd_parts);

		for (j = 0; j < num_parts; j++)
		{
			int part_check = token_command(cmd_parts[j], args);

			if (execute_command(args, part_check, last_status,
						argv, envp) != 0)
			{
				return;
			}
		}
	}
	else if (s_strstr(copy, "||"))
	{
		char *cmd_parts[ARG_SIZE];
		int j;
		int num_parts = split_logical_operator(copy, "||", cmd_parts);

		for (j = 0; j < num_parts; j++)
		{
			int part_check = token_command(cmd_parts[j], args);

			if (execute_command(args, part_check, last_status,
						argv, envp) == 0)
			{
				return;
			}
		}
	}
	else
	{
		execute_command(args, check, last_status, argv, envp);
	}
}

/**
 * is_whitespace_string- function to check for continuous whitespace
 * @str: the string to search for
 * Return: 0 if not all otherwise 1
 */
int is_whitespace_string(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!isspace(str[i]))
			return (0);
	}
	return (1);
}

/**
 * handle_noninbuilt_cmd - function to handle non inbuilt command
 * @mycmd: user command
 * @args: the argument if any
 * @check: checker for non_inbuilt cmd
 * @last_status: the status of command
 * @argv: the program name
 * @envp: parent environment
 * Return: the handle status
 */
int handle_noninbuilt_cmd(char *mycmd, char *args[], int check,
		int *last_status, char *argv, char *envp[])
{
	int handled = 1;

	handled = handle_cd(mycmd, args, check, last_status, argv, envp);
	if (handled != 1)
		return (handled);

	handled = handle_exit(args, check, argv);
	if (handled != 1)
		return (handled);

	handled = handle_setenv(mycmd, args, check, last_status);
	if (handled != 1)
		return (handled);

	handled = handle_unsetenv(mycmd, args, check, last_status);
	if (handled != 1)
		return (handled);

	return (handled);
}
