#include <stdio.h>
#include <stdlib.h>
#include "mysh_common.h"

const int TRUE = 1;
const int FALSE = 0;

const int MAX_CMD_LEN = 1024;
const int MAX_CMD_GRP = 512;

void fatal(char *msg)
{
	printf("fatal: %s\n", msg);
	exit(1);
}
