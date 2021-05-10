#include"exec.h" 
#include"para.h"
#include"color.h"
#define NODEBUG
#include<assert.h>

extern struct cmd cmds[MAX_COMMAND_PER_LINE];
extern char in_redir_file[LINESIZE];
extern char out_redir_file[LINESIZE];
extern int last_pid; 
extern int is_append;
extern int cmd_i;
extern char initial_workdir[LINESIZE];
char file[HISTORY_SIZE];


/* OverView of function `execute`
	this function execute command according to `cmds` array.
	the author separate the command into two kinds:
		1. cd/history: by systemcall `chdir` to change its path,
		   record history in tmp, and w/r it. 
		   these two commands are the only two internal commands
		   implemented in myshell.
		2. others(external commands): all other command will fork a 
		   new process and do command using `exevcp`, which is not 
		   a system-call if strictly speaking, but mainly call the 
		   function `execve`, which is a syscall in linux.
*/ 
int execute()
{
	if (cmd_i == 0) return 1;
	if (!strcmp(cmds[0].argv[0], "cd")) 
	{	
		char *path;
		if(cmds[0].argv[1]==NULL||cmds[0].argv[1][0]==' ')
		{
	    	struct passwd* pwd;
	    	pwd = getpwuid(getuid());
	    	path = pwd->pw_dir;
		} else path = cmds[0].argv[1];
		if(chdir(path)<0) {
			char error[LINESIZE];
			sprintf(error, "No such dir or file: %s !", path);
			PRINT_COLOR(error, RED, 1);
		}
		return 0;
	} else if (!strcmp(cmds[0].argv[0], "history")) {
		int fd = open(initial_workdir, O_RDONLY);
		read(fd, file, HISTORY_SIZE);
		file[strlen(file)-1] = 0;
		printf("%s\n", file);
		close(fd);
		return 0;
	}
	if(in_redir_file[0]!='\0') {
		cmds[0].in_redir_fd = open(in_redir_file, O_RDONLY);
	}
	if(out_redir_file[0]!='\0') {
		if(is_append)
			cmds[cmd_i-1].out_redir_fd = open(out_redir_file, OUTR_A_FLAG, MODE);
		else
			cmds[cmd_i-1].out_redir_fd = open(out_redir_file, OUTR_FLAG, MODE);	
	}
	int i;
	int fd;
	int p_fd[2];
	for(i=0; i<cmd_i; i++) {
		
		if(i!=cmd_i-1) {
			pipe(p_fd);
			cmds[i+1].in_redir_fd = p_fd[0];
			cmds[i].out_redir_fd = p_fd[1];
		}
		exe_cmd(i);
		/* to see the dynamic structure data of cmd when using pipe or redirection
		   when	remove the comments.
		*/
		// printf("cmds[%d].in_redir_fd: is %d\n", i, cmds[i].in_redir_fd);
		// printf("cmds[%d].out_redir_fd: is %d\n", i, cmds[i].out_redir_fd);
		if((fd=cmds[i].in_redir_fd)!=STDIN)  close(fd);
		if((fd=cmds[i].out_redir_fd)!=STDOUT)close(fd);
	}
	while(wait(NULL)!=last_pid);
}

/*OverView of function `exe_cmd`
	this function focus on execute type 2 command.
	the subprocess stdin, stderr, stdout rediretion is also 
	set here, and after its implementation, it well exit, after
	which the parent process(or main process) will continue.
*/ 
void exe_cmd(int i) {
	pid_t pid = fork();
	if(pid<0) {
		fprintf(stdout, "fork a new process to execute failed!: %s\n", strerror(errno));
		return;
	}
	if(pid>0) {
		last_pid = pid;
		usleep(500);
	}
	else if(pid==0) {
		if(cmds[i].in_redir_fd!=STDIN)
			dup2(cmds[i].in_redir_fd, fileno(stdin));
		if(cmds[i].out_redir_fd!=STDOUT)
			dup2(cmds[i].out_redir_fd, fileno(stdout));
		if(cmds[i].err_redir_fd!=STDERR)
			dup2(cmds[i].err_redir_fd, fileno(stderr));
		int status = execvp(cmds[i].argv[0], cmds[i].argv);
		if (status<0) { //execvp failed to perform current command.
			PRINT_COLOR("command syntx error!", RED, 1);	
		}
		exit(EXIT_FAILURE);
	}
}

