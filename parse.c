#include"parse.h" 
#include"para.h"
#include"color.h"
#define NODEBUG
#include<assert.h>

extern struct cmd cmds[MAX_COMMAND_PER_LINE];  // global cmds' array for each line of input.
int cmd_i;  // an index record the number of cmd.

/* record signal of redirection */
int is_redirective;  // if the last matching strgroup is signal of redirection, this var is set to 1, else 0.
int in_redir;  // if the last matching strgroup is `<`, this var is set to 1, else 0
int out_redir;  // if the last matching strgroup is `>` or `>>` or `1>` or `&>`, this var is set to 1, else 0
int error_redir; // if the last matching strgroup is `2>` or `2>>` or `&>`, this var is set to 1, else 0
int is_append;  // if the last matching strgroup is `>>`, this var is set to 1, else 0

/* record the redirfile name */
extern char in_redir_file[LINESIZE];
extern char out_redir_file[LINESIZE];
extern char error_redir_file[LINESIZE];

/*OverView of function `parse`:
	get input line and split it with `space`, record each group as 
	one of the following items:
		1. command argument.
		2. redirective signal.
		3. file or path of the redirective infomation.
	after which the inputline is parsed into data in structure `cmd`
	and ready to execute.
*/
int parse(char* line)
{	
	regex_t regx_command;
	regex_t regx_redir;
	regmatch_t pmatch[100] = {0};
	char* pattern_command = "([^ ]+|[\"\'].*[\"\'])";
	regcomp(&regx_command, pattern_command, REG_EXTENDED);
	int len = 0;
	char match[LINESIZE];
	char redir_match[LINESIZE];
	while(1)
	{	
		regexec(&regx_command,line,NMATCH,pmatch,0);
		len = pmatch[0].rm_eo - pmatch[0].rm_so;
		if(len>0) {
			memset(match, 0, LINESIZE);
			memcpy(match, line+pmatch[0].rm_so, len);
			if (strcmp(match, "|") == 0) 
			{	
				cmd_i++;
				line += pmatch[0].rm_eo;
				continue;
			} 
			if (get_redir_info(match)) {
				line += pmatch[0].rm_eo;
				continue;
			}
			if (is_redirective) {
				if (in_redir) {
					memcpy(in_redir_file,match,strlen(match)+1);
					in_redir = 0;
				}
				if(out_redir) {
					memcpy(out_redir_file,match,strlen(match)+1);
					out_redir = 0;
				}
				if(error_redir) {
					memcpy(error_redir_file,match,strlen(match)+1);
					error_redir = 0;
					is_append = 0;
				}
				is_redirective = 0;
			} else {
				cmds[cmd_i].argv[cmds[cmd_i].arg_cnt] = (char *)malloc(strlen(match)+1);
				assert(cmds[cmd_i].argv[cmds[cmd_i].arg_cnt]!=NULL);
				int arg_len = strlen(match)+1;
				int arg_index = 0;
				for(int i=0;i<arg_len;i++){
			    	if(match[i]!='\"') 
						cmds[cmd_i].argv[cmds[cmd_i].arg_cnt][arg_index++] = match[i];
				}
				assert(cmds[cmd_i].argv[cmds[cmd_i].arg_cnt]!=NULL);
				cmds[cmd_i].arg_cnt++;
			}
		}
		if(pmatch[0].rm_eo < strlen(line)) 
			
			line+=pmatch[0].rm_eo;
		else {cmd_i++; break;}
    }
    return 0;
}

/*OverView of function `get_redir_info`:
	this function focus on transform the string signal of
	redirection into abstract interger siginal for parsing.
*/
int get_redir_info(char* match){
	if(match==NULL) return 0;
	int redir_sign = 1; 
	if (!strcmp(match, "<")) {
		in_redir = 1;
		is_redirective = 1;
	} else if (!strcmp(match, ">") | !strcmp(match, "1>")) {
		out_redir = 1;
		is_redirective = 1;
	} else if (!strcmp(match, ">>") | !strcmp(match, "1>>")) {
		out_redir = 1;
		is_append = 1;
		is_redirective = 1;
	} else if (!strcmp(match, "$>")) {
		out_redir = 1;
		error_redir = 1;
		is_redirective = 1;
	} else if (!strcmp(match, "$>>")) {
		out_redir = 1;
		error_redir = 1;
		is_append = 1;
		is_redirective = 1;
	} else if (!strcmp(match, "2>")) {
		error_redir = 1;
		is_redirective = 1;
	} else if(!strcmp(match, "2>>")) {
		error_redir = 1;
		is_append = 1;
		is_redirective = 1;
	} else {
		redir_sign = 0;
	}
	return redir_sign;
}

