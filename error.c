#include "shell.h"

/**
 * createAndWriteErrorMessage - function to display error msg
 * @mytest: status code
 * @args: the argument for exit if any
 * @argv: the program name
 * Return: void
 */
void createAndWriteErrorMessage(test *mytest, char *args[], char *argv)
{
	char error_msg[100];

	s_strcpy(error_msg, argv);
	s_strcat(error_msg, ": 1");
	s_strcat(error_msg, ": ");
	s_strcat(error_msg, args[0]);
	s_strcat(error_msg, ": Illegal number: ");
	s_strcat(error_msg, args[1]);
	s_strcat(error_msg, "\n");
	write(STDERR_FILENO, error_msg, s_strlen(error_msg));
	mytest->status = 2;
}

/**
 * handleExitWithCode - function to handle exit with code
 * @mytest: the status code
 * @code: the argument code
 * Return: void
 */
void handleExitWithCode(test __attribute__((__unused__)) *mytest, int code)
{
	if (code >= 0)
		exit(code);
}

/**
 * handle_exit - funcnction to handle exit command
 * @args: the command pass to execute
 * @check: the number of token return
 * @argv: the program name
 * Return: 0 for success and 1 otherwise
 */
int handle_exit(char *args[], int check, char *argv)
{
	test mytest;

	if (check > 0 && s_strcmp(args[0], "exit") == 0)
	{
		if (check == 1)
		{
			mytest.status = 0;
			exit(mytest.status);
		}
		else if (check == 2)
		{
			char *exitarg = args[1];

			if (ispositiveInt(exitarg))
			{
				int code = atoi(exitarg);

				handleExitWithCode(&mytest, code);
			}
			else if (isnegativeInt(exitarg))
			{
				createAndWriteErrorMessage(&mytest, args, argv);
				exit(mytest.status);
			}
			else
			{
				createAndWriteErrorMessage(&mytest, args, argv);
				exit(mytest.status);
			}
		}
		return (0);
	}
	return (1);
}
