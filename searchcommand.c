#include "shell.h"

/**
 * tokenize_usercommand - function to tokenize user command from the argument
 * @user_command: the string passed from the console
 * @args: the array of pointer to strings to store the tokenized arguments
 * Return: void
 */
void tokenize_usercommand(char *user_command, char **args)
{
	int index;
	char *copy = s_strdup(user_command);
	char *mytok = s_strtok(copy, " ");

	for (index = 0; mytok != NULL; index++)
	{
		args[index] = mytok;
		mytok = s_strtok(NULL, " ");
	}
	args[index] = NULL;
}

/**
 * exec_command_withpath - function to execute command without path specifield
 * @user_command: the user command
 * @args: the flag of the command
 * @env: parent environment
 * Return: 0 for success
 */
int exec_command_withpath(char *user_command, char *args[], char **env)
{
	int index;
	int result = -1;
	char *path_token;
	char *command_path, *duplicate;

	command_path = getenv("PATH");

	if (command_path == NULL)
		return (-1);

	duplicate = s_strdup(command_path);
	if (duplicate == NULL)
		return (-1);

	path_token = s_strtok(duplicate, ":");

	for (index = 0; path_token != NULL; index++)
	{
		char abs_path[PATH_SIZE];

		s_strcpy(abs_path, path_token);
		s_strcat(abs_path, "/");
		s_strcat(abs_path, user_command);

		result = execve(abs_path, args, env);

		if (result == -1)
			path_token = s_strtok(NULL, ":");
	}
	free(duplicate);

	return (result);
}

/**
 * exec_command - function to execute the command
 * @user_command: the command pass
 * @args: the flag of the command
 * @argv: the program name
 * @envp: the parent environment
 * Return: 0 if success
 */
int exec_command(char *user_command, char *args[], char *argv, char **envp)
{
	int result;

	if (s_strchr(user_command, '/') != NULL)
	{
		result = execve(user_command, args, envp);
		return (result);
	}
	else
	{
		if (check_cmd(args[0]) == 0)
		{
			print_err(args[0], argv);
			exit(127);
		}
		result = exec_command_withpath(user_command, args, envp);

		if (result == -1)
		{
			print_err(args[0], argv);
			exit(127);
		}

		return (result);
	}
}

/**
 * run_commandfile - function to run command
 * @user_command: the command to run
 * @argv:; the program name
 * @envp: parent environment
 * Return: child pid
 */

int run_commandfile(char *user_command, char *argv, char *envp[])
{
	int handled = 0;
	int i, last_status = 0;
	char *cmd_list[ARG_SIZE];
	int num_cmd = 0;
	char *cmd_token = s_strtok(user_command, ";\n");

	while (cmd_token != NULL)
	{
		cmd_list[num_cmd] = cmd_token;
		num_cmd++;
		cmd_token = s_strtok(NULL, ";\n");
	}

	for (i = 0; i < num_cmd; i++)
	{
		char *mycmd = cmd_list[i];
		char *args[ARG_SIZE];
		int check = token_command(mycmd, args);

		replace_status_variable(args, check, &last_status);
		handled = handle_cd(mycmd, args, check, &last_status, argv, envp);
		if (handled != 1)
			return (handled);
		handled = handle_exit(args, check, argv);
		if (handled != 1)
			return (handled);
		handled = handle_setenv(mycmd, args, check, &last_status);
		if (handled != 1)
			return (handled);
		handled = handle_unsetenv(mycmd, args, check, &last_status);
		if (handled != 1)
			return (handled);
		if (execute_command(args, check, &last_status, argv, envp) == 1)
			return (2);
	}
	return (last_status);
}
