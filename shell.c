#include "shell.h"

/**
 * main - main function Entry point
 * @argc: t keep count the number of argument
 * @argv: array to store the argument
 * @envp: the parent environment
 * Return: 0 for success 1 otherwise
 */
int main(int argc, char *argv[], char *envp[])
{
	char user_command[INPUT_SIZE];
	ssize_t input_byte;
	char *exp_cmd;
	int last_status;

	if (argc == 2)
	{
		last_status = execute_commands_from_file(argv[1], envp, argv[0]);
	}
	else
	{
		signal(SIGINT, signal_handler);
		while (1)
		{
			prompt("$ ", s_strlen("$ "));
			input_byte = take_input(user_command);
			if (input_byte == -1)
				continue;
			else if (input_byte == 0)
			{
				prompt("\n", s_strlen("\n"));
				break;
			}

			remove_comment(user_command);
			exp_cmd = handle_double_dollars(user_command, envp);
			last_status = run_command(exp_cmd, argv[0], envp);
			free(exp_cmd);
		}
	}
	return (last_status);
}

/**
 * ispositiveInt - function to check if input is digit
 * @str: the string enter
 * Return: 1 if int
 */
int ispositiveInt(char *str)
{
	int index;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (!isdigit(str[index]))
			return (0);
	}
	return (1);
}

/**
 * isnegativeInt - function to check if a number is negative integer
 * @str: the string to check
 * Return: 0 on success
 */
int isnegativeInt(char *str)
{
	int index;

	if (str[0] == '-')
		return (1);
	for (index = 1; str[index] != '\0'; index++)
	{
		if (!isdigit(str[index]))
			return (0);
	}
	return (1);
}
