#ifndef _PARSE_H_
#define _PARSE_H_

#include<regex.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int get_redir_info(char* match);
int parse(char* line);

#endif /*parse.h*/
