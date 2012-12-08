/*
FILE
... mysh_parse.h

DESCRIPTION
... This header file contains declarations of parsing functions

DATE
... 2013-02-08

AUTHOR
... sLo
*/

#ifndef __MYSH_PARSE_H__
#define __MYSH_PARSE_H__

extern int parse_cmdgrp      (char *str, char **grp);
extern int parse_args        (char *str, char **grp);
extern int parse_pipe        (char *str, char **grp);
extern int parse_redirect_in (char *str, char **grp);
extern int parse_redirect_out(char *str, char **grp);

#endif
