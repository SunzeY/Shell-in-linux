#ifndef _COLOR_H_
#define _COLOR_H_
/*set_front_color*/
#define PRINT_FONT_BLA  printf("\033[30m"); //black
#define PRINT_FONT_RED  printf("\033[31m"); //red
#define PRINT_FONT_GRE  printf("\033[32m"); //green
#define PRINT_FONT_YEL  printf("\033[33m"); //yellow
#define PRINT_FONT_BLU  printf("\033[34m"); //blue
#define PRINT_FONT_PUR  printf("\033[35m"); //puple
#define PRINT_FONT_CYA  printf("\033[36m"); //crayon
#define PRINT_FONT_WHI  printf("\033[37m"); //write
/*set_background_color*/ 
#define PRINT_BACK_BLA  printf("\033[40m"); //black
#define PRINT_BACK_RED  printf("\033[41m"); //red
#define PRINT_BACK_GRE  printf("\033[42m"); //green
#define PRINT_BACK_YEL  printf("\033[43m"); //yellow
#define PRINT_BACK_BLU  printf("\033[44m"); //blue
#define PRINT_BACK_PUR  printf("\033[45m"); //puple
#define PRINT_BACK_CYA  printf("\033[46m"); //crayon
#define PRINT_BACK_WHI  printf("\033[47m"); //write
/*settings*/
#define PRINT_ATTR_REC  printf("\033[0m");  //back_to_default_value
#define PRINT_ATTR_BOL  printf("\033[1m");  //Broad 
#define PRINT_ATTR_LIG  printf("\033[2m");  //half_bright
#define PRINT_ATTR_LIN  printf("\033[4m");  //underline
#define PRINT_ATTR_GLI  printf("\033[5m");  //staring 
#define PRINT_ATTR_REV  printf("\033[7m");  //rev_direction 
#define PRINT_ATTR_THI  printf("\033[22m"); ///role
#define PRINT_ATTR_ULIN  printf("\033[24m");//stop_underlin 
#define PRINT_ATTR_UGLI  printf("\033[25m");//stop_staring 
#define PRINT_ATTR_UREV  printf("\033[27m");//stop_rev_direction 

#endif /*color.h*/
