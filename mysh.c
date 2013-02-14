/*
FILE
... mysh.c

DESCRIPTION
... This source file contains the main function.

DATE
... 2013-02-09

AUTHOR
... sLo
*/

#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysh_common.h"
#include "mysh_parse.h"

int main()
{
	const char *prompt = "mysh$ ";
	char command[MAX_CMD_LEN];
	char *cmdgrp[MAX_CMD_GRP];

	int nread, ncmd;

	int i;

	signal(SIGCHLD, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);

	while (TRUE)
	{
		/* Print prompt. */
		if (write(STDOUT_FILENO, prompt, strlen(prompt)) <= 0)
			fatal("write() error");

		/* Get user input. */
		nread = read(STDIN_FILENO, command, MAX_CMD_LEN);
		if (nread <= 0)
			fatal("read() error");
		command[nread - 1] = '\0';

		ncmd = mysh_parse_cmdgrp(command, cmdgrp);

		for (i = 0; i < ncmd; i++)
			mysh_execute_command(cmdgrp[i]);
	}

	exit(0);
}
