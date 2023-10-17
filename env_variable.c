#include "shell.h"


/**
 * get_environment_variable_value - function to get value of env
 * @var_name: the command
 * @envp: the parent environment
 * Return: the environment variable
 */
char *get_environment_variable_value(char *var_name, char *envp[])
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		char *env_entry = envp[i];

		if (s_strstr(env_entry, var_name) == env_entry)
		{
			const char *equals = s_strchr(env_entry, '=');

			if (equals != NULL)
			{
				return (s_strdup(equals + 1));
			}
		}
	}
	return (NULL);
}

/**
 * handle_double_dollar_internal - handle $$
 * @cmd: the command
 * @output: the output
 * @i: counter
 * @j: counter
 * Return: void
 */
void handle_double_dollar_internal(char __attribute__((__unused__))
		*cmd, char *output, int *i, int *j)
{
	char *pid_str = get_process_id_string();
	int k = 0;

	while (pid_str[k] != '\0')
	{
		output[(*j)++] = pid_str[k++];
	}
	free(pid_str);
	(*i) += 2;
}

/**
 * handle_environment_variable - function to specify it
 * @cmd: the command
 * @output: the output result
 * @i: counter
 * @j: counter
 * @envp: parent environment
 * Return: void
 */
void handle_environment_variable(char *cmd, char *output, int *i,
		int *j, char *envp[])
{
	int k = (*i);

	while (s_isalnum((unsigned char)cmd[(*i)]) || cmd[(*i)] == '_')
	{
		(*i)++;
	}

	if (k != (*i))
	{
		char *env_var = s_strndup(&cmd[k], (*i) - k);
		char *env_value = get_environment_variable_value(env_var, envp);

		if (env_value)
		{
			int l = 0;

			while (env_value[l] != '\0')
			{
				output[(*j)++] = env_value[l++];
			}
			free(env_value);
		}
		free(env_var);
	}
	else
	{
		output[(*j)++] = '$';
	}
}

/**
 * handle_double_dollars - function to handle environent variable
 * @cmd: the command enter
 * @envp: parent environment
 * Return: the absolute variable
 */
char *handle_double_dollars(char *cmd, char *envp[])
{
	char *output = malloc(strlen(cmd) * 10 + 1);
	int i = 0, j = 0;

	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$' && cmd[i + 1] == '$')
		{
			handle_double_dollar_internal(cmd, output, &i, &j);
		}
		else if (cmd[i] == '$')
		{
			i++;
			handle_environment_variable(cmd, output, &i, &j, envp);
		}
		else
		{
			output[j++] = cmd[i++];
		}
	}

	output[j] = '\0';
	return (output);
}

/**
 * get_process_id_string - function to get process id
 * Return: the process id
 */
char *get_process_id_string()
{
	pid_t pid = getpid();
	char pid_buff[16];
	int i = 0;
	char *pid_str;

	if (pid == 0)
	{
		pid_buff[i++] = '0';
	}
	else
	{
		while (pid > 0)
		{
			pid_buff[i++] = '0' + (pid % 10);
			pid /= 10;
		}
	}

	pid_str = malloc(i + 1);
	if (pid_str)
	{
		int j = 0;
		int k;

		for (k = i - 1; k >= 0; k--)
		{
			pid_str[j++] = pid_buff[k];
		}

		pid_str[j] = '\0';
	}

	return (pid_str);
}
