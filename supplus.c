#include "shell.h"

int execute_commands_from_file(const char *filename, char *envp[],
		char *program_name)
{
	char line[INPUT_SIZE];
	ssize_t bytes_read;
	char *exp_cmd;
	int last_status;
	int fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		if (errno == EACCES)
			exit(126);
		if (errno == ENOENT)
		{
			int program_len = s_strlen(program_name);
			int filename_len = s_strlen(filename);

			write(2, program_name, program_len);
			write(2, ": 0: cannot open ", 17);
			write(2, filename, filename_len);
			write(2, ": No such file\n", 15);
			exit(2);
		}
	}

	while ((bytes_read = read(fd, line, sizeof(line))) > 0)
	{
		line[bytes_read] = '\0';
		remove_comment(line);
		exp_cmd = handle_double_dollars(line, envp);
		last_status = run_commandfile(exp_cmd, program_name, envp);
		if (last_status > 0)
		{
			int status;

			waitpid(last_status, &status, 0);
		}
	}
	close(fd);
	return (0);
}

/**
 * is_whitespace - function to check for whitespace
 * @c: the chracter to check
 * Return: escape character
 */
int is_whitespace(char c)
{
	return ((c == ' ' || c == '\t' || c == '\n' || c == '\r'));
}

/**
 * is_word_start - function to check if a word start
 * @str: the string to search
 * @index: the index to iterate over
 * Return: 1 if success
 */
int is_word_start(char *str, int index)
{
	if (index == 0 || is_whitespace(str[index - 1]))
	{
		return (1);
	}
	return (0);
}

/**
 * check_cmd - function to check for external command
 * @mycmd: the command to check for
 * Return: 0 on success
 */
int check_cmd(char *mycmd)
{
	if (chk_cmd_before_fork(mycmd) == 1 && s_strcmp(mycmd, "exit") != 0 &&
		s_strcmp(mycmd, "cd") != 0 && s_strcmp(mycmd, "setenv") != 0 &&
		s_strcmp(mycmd, "unsetenv") != 0 && s_strcmp(mycmd, "alias") != 0)
	{
		return (0);
	}
	else
		return (1);
}
