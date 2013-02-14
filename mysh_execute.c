#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysh_common.h"
#include "mysh_execute.h"

#define NOTHING

static void mysh_execute_foreground(const char *cmd)
{
	int pid;

	char command[MAX_CMD_LEN];
	char *args[MAX_CMD_GRP];

	int nargs;

	strcpy(command, cmd);
	nargs = mysh_parse_args(command, args);

	pid = fork();

	/* fork() error */
	if (pid == -1)
		fatal("fork() error");

	/* child process */
	else if (pid == 0)
		execvp(args[0], args);

	/* parent process */
	else
	{
		signal(SIGCHLD, SIG_DFL);
		waitpid(pid, NULL, 0);
		signal(SIGCHLD, SIG_IGN);
	}
}

static void mysh_execute_background(const char *cmd)
{
	int pid;

	char command[MAX_CMD_LEN];
	char *args[MAX_CMD_GRP];

	int nargs;

	strcpy(command, cmd);
	nargs = mysh_parse_args(command, args);
	args[nargs - 1] = NULL;

	pid = fork();

	/* fork() error */
	if (pid == -1)
		fatal("fork() error");

	/* child process */
	else if (pid == 0)
		execvp(args[0], args);

	/* parent process */
	else
		NOTHING;
}

static void mysh_execute_cd(const char *path)
{
	if (path == NULL)
		return;

	if (chdir(path) == -1)
		fatal("chdir() error");
}

static void mysh_execute_exit()
{
	exit(0);
}

void mysh_execute_command(const char *cmd)
{
	char *command = calloc(strlen(cmd) + 1, sizeof(char));
	char *args[MAX_CMD_GRP];

	int nargs;

	int i;

	strcpy(command, cmd);
	nargs = mysh_parse_args(command, args);

	/* DEBUG */
	printf("total %d arguments.\n", nargs);
	for (i = 0; i < nargs; i++)
		printf("args[%d] = %s\n", i, args[i]);

	/* exit */
	if (strcmp(args[0], "exit") == 0)
	{
		free(command);
		mysh_execute_exit();
	}
	/* cd */
	else if (strcmp(args[0], "cd") == 0)
	{
		mysh_execute_cd(args[1]);
	}
	/* background session */
	else if (strncmp(args[nargs - 1], "&", 1) == 0)
	{
		mysh_execute_background(cmd);
	}
	/* foreground session */
	else
	{
		mysh_execute_foreground(cmd);
	}

	free(command);
}

