#ifndef PARA_H_
#define PARA_H_

#define LINESIZE 1024             //max char_size
#define NMATCH 1
#define MAX_COMMAND_PER_LINE 128  //max command per line (with pipe to seperate)
#define MAX_ARGV 20               //max argument num each command

#define HISTORY_SIZE 65536

/*standard file descriptor*/
#define STDIN  0
#define STDOUT 1
#define STDERR 2

#define MODE 0666                 //inial authoritation of a new file when automatically created

/*different oflags value when calling open()*/
#define OUTR_A_FLAG O_WRONLY|O_CREAT|O_APPEND
#define OUTR_FLAG O_WRONLY|O_CREAT|O_TRUNC

struct cmd {
	int arg_cnt;
	char** argv;
	int in_redir_fd;     // stdin  redirection file descriptor
	int out_redir_fd;    // stdout redirection file descriptor
	int err_redir_fd;    // stderr redirection file descriptor
};

#endif /*para.h*/
