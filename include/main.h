#ifndef MAIN_H_
#define MAIN_H_

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>

int main();
int shell_space_alloc();
void shell_init_ifo();
void show_propmt();
void shell_update();
void record();

#endif /*main.h*/
