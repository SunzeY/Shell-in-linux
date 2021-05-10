#include"main.h" 
#include"para.h"
#include"color.h"
#define MONITORED //if this macro is defined, the keybored will be monitored.
#define NODEBUG
#include<assert.h>

char in_redir_file[LINESIZE];
char out_redir_file[LINESIZE];
char error_redir_file[LINESIZE];
char initial_workdir[LINESIZE];
char log_history[LINESIZE][LINESIZE];
int num_of_cmd;
struct cmd cmds[MAX_COMMAND_PER_LINE];
int cmd_i;
int status;
int last_pid;
char curPath[LINESIZE];
char cmd_line[LINESIZE];
struct passwd* pwd;
char* username;
uid_t user_id;

/* OverView of function `main`:
	the entry of the whole project.
	the steps of its execution can be seen as a loop:
		1. initialize the environment and allocate space for its running.
		loop:
			2. get information of current directory and username.
			3. update memory(turn every var into its initial value).
			4. show propmt.
			5. read a line of commands.
			6. if input is `exit`, goto 11.
			7. parse the commands line.
			8. execute commands.
			9. show error information if any.
			10.goto 2. 
		loop_end:
		11.exit.
*/
int main() 
{
	shell_space_alloc();
  	shell_init_ifo();
  	PRINT_INIT;

	while(1)
	{
		shell_update();
		show_propmt();
		//readline(cmd_line);
		#ifdef MONITORED
		read_with_ctrl(cmd_line);
		#endif
		#ifndef MONITORED
		fgets(cmd_line, LINESIZE, stdin);
		#endif
		record(cmd_line);
		if(!strcmp(cmd_line, "exit")) break;
		parse(cmd_line);
		status = execute();
		if (status==1) {
			PRINT_COLOR("command syntx error!\n", RED, 1);	
		}
	}
	// clean history.
	creat(initial_workdir, MODE);
	PRINT_END;
	return 0;
}

int shell_space_alloc() {
	int i = 0;
	for(i=0;i<MAX_COMMAND_PER_LINE;i++)
	{
        cmds[i].argv = (char **)malloc(sizeof(char *)*MAX_ARGV);
        memset(cmds[i].argv,0,sizeof(char *)*MAX_ARGV);
    }
}

void shell_init_ifo()
{	
	user_id = getuid();
	pwd = getpwuid(user_id);
	username = pwd->pw_name;
	getcwd(initial_workdir, LINESIZE);
	
	// remove hisory last time recorded.
	strcat(initial_workdir, "/tmp/history.txt");
	creat(initial_workdir, MODE);
}

void show_propmt() 
{	
	PRINT_USERNAME(username);
	PRINT_CURRENT_DIR(curPath);
}

void record(char* cmd)
{
	int fd = open(initial_workdir, O_WRONLY|O_APPEND);
	write(fd, cmd, strlen(cmd));
	close(fd);
	cmd[strlen(cmd)-1] = 0;
	strcpy(log_history[num_of_cmd++], cmd);
}

/* OverView of function `shell_update`:
	this function use a loop to change the
	value of global cmds array to its initail
	and change dir, which will be used to show
	prompt.
*/
void shell_update()
{	
	for (int k=0; k<LINESIZE; k++) {
		cmd_line[k] = 0;
	}
	if (getcwd(curPath, LINESIZE) == 0) 
	{
		fprintf(stderr, "get current cwd failed: %s\n", strerror(errno));
	}
	cmd_i = 0;
    int i;
    for(i=0;i<MAX_COMMAND_PER_LINE;i++) {
    	cmds[i].argv = (char **)malloc(sizeof(char *)*MAX_ARGV);
		memset(cmds[i].argv,0,sizeof(char *)*(MAX_ARGV));
		assert(cmds[i].argv!=NULL);
		cmds[i].arg_cnt = 0;
		cmds[i].in_redir_fd = STDIN;
		cmds[i].out_redir_fd = STDOUT;
		cmds[i].err_redir_fd = STDERR;
    }
    memset(in_redir_file, 0, LINESIZE);
    memset(out_redir_file, 0, LINESIZE);
    memset(error_redir_file, 0, LINESIZE);
}

