/*
FILE
... mysh_parse.c

DESCRIPTION
... This file contains parsing functions, which help us execute commands.

DATE
... 2013-02-08

AUTHOR
... sLo
*/

#include <stdlib.h>
#include <string.h>
#include "mysh_parse.h"

/*
FUNCTION
... int mysh_parse(char *str, char *delim, char **grp)

PARAMETER
... str   : string to be parsed
... delim : delimeter
... grp   : group of strings which were split

RETURN
... the number of split strings

EXAMPLE
... Here is an example code.

    main()
    {
        int i;
        char *group[4];
        int n = mysh_parse("Hello World!", "l", group);
        for (i = 0; i < n; i++)
            printf("group[%d] = %s\n", i, group[i]);
    }

... Here is the output.

    group[0] = He
    group[1] = o Wor
    group[2] = d!

DATE
... 2012-02-08
*/
static int mysh_parse(char *str, char *delim, char **grp)
{
	int i;

	grp[0] = strtok(str, delim);

	for (i = 0; grp[i] != NULL; i++)
		grp[i + 1] = strtok(NULL, delim);

	return i;
}

/*
FUNCTION
... int mysh_parse_cmdgrp      (char *str, char **grp)
... int mysh_parse_args        (char *str, char **grp)
... int mysh_parse_pipe        (char *str, char **grp)
... int mysh_parse_redirect_in (char *str, char **grp)
... int mysh_parse_redirect_out(char *str, char **grp)

DESCRIPTION
... These are wrapper functions.
... It can be used for parsing input command line.

PARAMETER
... str : string to be parsed
... grp : group of strings which were split
*/
int mysh_parse_cmdgrp(char *str, char **grp)
{
	return mysh_parse(str,";",grp);
}
int mysh_parse_args(char *str, char **grp)
{
	return mysh_parse(str," \t",grp);
}
int mysh_parse_pipe(char *str, char **grp)
{
	return mysh_parse(str,"|",grp);
}
int mysh_parse_redirect_in(char *str, char **grp)
{
	return mysh_parse(str,"<",grp);
}
int mysh_parse_redirect_out(char *str, char **grp)
{
	return mysh_parse(str,">",grp);
}

