#include "screen.h"
#include <stdio.h>

void setFGcolor(int fg){
	printf("\033[%d;1m",fg);
	fflush(stdout);
}

void resetColors(void){
	printf("\033[0m");
	fflush(stdout);
}

void gotoXY(int row,int col){
	printf("\033[%d;%dH",row,col);
	fflush(stdout);
}

void clearScreen(void){
	printf("\033[2J");
	fflush(stdout);
}

void displayBar(double rms,int col){
	int i;
	for(i=0;i<rms/100;i++){
		gotoXY(45-i,col);  //start display the bar from i+2 and go down
#ifdef UNICODE
		printf("%s",BAR);
#else
		printf("*");
#endif
	}
	fflush(stdout);
}
