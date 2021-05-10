#include"ctrl.h"
#define NODEBUG
#include<assert.h>

char cur_cmd[LINESIZE];
char test[LINESIZE] = "test";

/* OverView of function `flash`:
	this function is used when using `up` or `down`
	to flush current command line.
*/
void flush() {
	int size = (int)(strlen(cur_cmd));
	for (int k=0; k<size; k++) {
		cur_cmd[k] = 0;
		printf("\b");
		printf(" ");
		printf("\b");
	}
}

/* Overview of function `read_with_ctrl`
	this function is called by main to read an command line.
	the screen will only show stdout in this function, However,
	It will give the user a hallucination that the screen shows
	what he or she is typing.
	only by using this method can we implemented simple Keyboard 
	monitoring without creating a new process.
*/
void read_with_ctrl(char* ans) {
	extern char log_history[LINESIZE][LINESIZE];
	extern int num_of_cmd;
  	char in;
  	int size = (int)(strlen(cur_cmd));
	for (int k=0; k<size; k++) {
		cur_cmd[k] = 0;
	}
	//screen settings to make sure no echo when input in console.
	struct termios new_settings;
	struct termios stored_settings;
	tcgetattr(0,&stored_settings);     /*save current settings*/
	new_settings = stored_settings;
 	new_settings.c_lflag &= (~ICANON); /*ignore cache of current line*/
	new_settings.c_lflag &= ~ECHO;     /*set no echo on screen(main)*/
	new_settings.c_cc[VTIME] = 0;      /*set time limit*/
	new_settings.c_cc[VMIN] = 1;       /*set min_char_num limit*/
	tcsetattr(0,TCSANOW,&new_settings);
	
	//main loop
	int i;
	while(in!='\n') {
		in = getchar();
		
		// input `backspace`.
		if (in==127) { // in == '\b'
			if (strlen(cur_cmd)>0) {
				printf("\b");
				printf(" ");
				printf("\b");
				cur_cmd[strlen(cur_cmd)-1] = '\0';
				i = num_of_cmd - 1;
			}
		}
		
		// signal input `up` or `down` will input 3 chars on screen.
		else if (in==27) { // in == '['
			in = getchar();
			in = getchar();
			if (in==65) { // in == 'up'
				flush();
				strcpy(cur_cmd, log_history[i]);
				// setting pointer to its next proper position.
				i = ((i-1)<0? (i-1+num_of_cmd) : (i-1))&(num_of_cmd-1);
			} else if (in==66) { // in == 'down'
				flush();
				extern int num_of_cmd;
				strcpy(cur_cmd, log_history[i]);
				
				// setting pointer to its next proper position.
				i = (i+1)&(num_of_cmd-1);
			} 
			printf("%s", cur_cmd);
		}
		
		// not ctrl input but normal command input.
		else {
			printf("%c", in);
			cur_cmd[strlen(cur_cmd)] = in;
			i = num_of_cmd - 1;
		}	
	}
	tcsetattr(0,TCSANOW,&stored_settings);    /* restore original settings */
	strcpy(ans, cur_cmd);
}

