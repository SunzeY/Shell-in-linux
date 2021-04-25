#ifndef EXEC_H_
#define EXEC_H_

#include<stdlib.h>
#include<string.h>
#include<regex.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<pwd.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

void exe_cmd(int i);
int execute();

#endif /*exec.h*/
