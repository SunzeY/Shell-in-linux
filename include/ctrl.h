#ifndef CTRL_H_
#define CTRL_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <termio.h>

#define LINESIZE 1024

void read_with_ctrl(char* ans);
void flush();

#endif /*ctrl.h*/
