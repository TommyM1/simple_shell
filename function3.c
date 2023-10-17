#include "shell.h"

/**
 * execute_command - function that create fork and execute command
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * @argv: the program name
 * @envp: parent environment
 * Return: 0 for success
 */
int execute_command(char *args[], int check, int *last_status,
		char *argv, char *envp[])
{
	int j;
	test mytest;
	pid_t child_pid = fork();

	if (child_pid < 0)
		return (-1);
	if (child_pid == 0)
	{
		char **exec_Args = malloc((check + 1) * sizeof(char *));

		if (exec_Args == NULL)
			return (-1);
		for (j = 0; j < check; j++)
		{
			exec_Args[j] = s_strdup(args[j]);

			if (exec_Args[j] == NULL)
				return (-1);
		}
		exec_Args[check] = NULL;

		if (exec_command(exec_Args[0], exec_Args, argv, envp) == -1)
		{
			perror(exec_Args[0]);
			exit(2);
		}
		for (j = 0; j < check; j++)
			free(exec_Args[j]);
		free(exec_Args);
	}

	else
	{
		wait(&(mytest.status));
		if (WIFEXITED(mytest.status))
			mytest.status = WEXITSTATUS(mytest.status);
		*last_status = mytest.status;
	}
	return (mytest.status);
}


/**
 * handle_cd - function to handle CD command
 * @mycmd: the command at the first index
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * @argv: the program name
 * @envp: parent environment
 * Return: 0 for success
 */
int handle_cd(char *mycmd, char *args[], int check,
		int *last_status, char *argv, char *envp[])
{
	if (chk_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "cd") == 0)
	{
		int outcome = cd_dir(args[1], argv, envp);

		if (outcome == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}

/**
 * handle_setenv - function to handle setenv command
 * @mycmd: the command at first index
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * Return: 0 on success
 */
int handle_setenv(char *mycmd, char *args[],
		int check, int *last_status)
{
	if (chk_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "setenv") == 0)
	{
		int env_rs = setenv_cmd(mycmd);

		if (env_rs == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}


/**
 * handle_unsetenv - function to handle unsetenv command
 * @mycmd: the command at first index
 * @args: the command to execute
 * @check: the number of token return
 * @last_status: the variable that keeps the value of return
 * Return: 0 on success
 */
int handle_unsetenv(char *mycmd, char *args[],
		int check, int *last_status)
{
	if (chk_cmd_before_fork(mycmd) == 1 && check > 0 &&
		s_strcmp(args[0], "unsetenv") == 0)
	{
		int unset_rs = unsetenv_cmd(mycmd);

		if (unset_rs == 0)
		{
			*last_status = 0;
			return (0);
		}
		*last_status = -1;
		return (-1);
	}
	return (1);
}
