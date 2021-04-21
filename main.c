#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include"color.h"

#define LINESIZE 1024
char curPath[LINESIZE];
struct passwd* pwd;
char* username;
uid_t user_id;

void shell_init_ifo()
{	
	user_id = getuid();
	pwd = getpwuid(user_id);
	username = pwd->pw_name;
}
void show_propmt() 
{	
	PRINT_ATTR_BOL
	
	PRINT_FONT_GRE
	printf("%s@myShell", username);

	PRINT_FONT_BLU
	printf("%s", curPath);
	
	PRINT_FONT_WHI
	printf("$");
	
	PRINT_ATTR_REC
}
void exception_handler(int cause)
{
	PRINT_FONT_RED
	switch(cause){
		case 1:
			printf("myShell failed when getting currentID!\n");
			break;
		default:
			break;
	}
	printf(">>>>>>>>>>>>>>>>>>>>>myShell crashed and exit!<<<<<<<<<<<<<<<<<<<<<<");
	exit(-1);
}
void shell_update()
{
	if (getcwd(curPath, LINESIZE) == 0) {
		exception_handler(1);
	}
}
int main() {
  	shell_init_ifo();
  	PRINT_FONT_YEL
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>myShell<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	PRINT_ATTR_REC
	char cmd_line[LINESIZE];
	while(1)
	{
		shell_update();
		show_propmt();
		fgets(cmd_line, LINESIZE, stdin);
		cmd_line[strlen(cmd_line)-1] = 0;
		if(!strcmp(cmd_line, "exit")) break;
		printf("input: %s\n", cmd_line);
		
	}
	PRINT_FONT_YEL
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>myshell_exit<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	PRINT_ATTR_REC
	return 0;
}
