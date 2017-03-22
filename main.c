#include <stdio.h>
#include "wave.h"
#include <math.h>
#include <signal.h>
#include <sys/wait.h>
#include "screen.h"
#include <stdlib.h> //eliminate the warning when -c99 standard os using

int main(int argc,char *argv[]){
	WAVHDR h;
	FILE *fp;
	int ans,ret;
	short int sa[SAMPLE_RATE];
        //file handlder of wave file
/*	if(argc<2){	
	printf("Usage:%s wav_file\n",argv[0]);
	return -1;
	}
	fp=fopen(argv[1],"r"); //open the wav file in read-only
	if(fp==NULL){
		printf("Cannot open wav file %s\n",argv[1]);
		return -1;
	}
*/
	while(1){
 		ret=system("arecord -r16000 -c1 -d1 -f S16_LE -q data.wav");
		if(WIFSIGNALED(ret)&& WTERMSIG(ret)==SIGINT) break;
		clearScreen();	//a fresh screen to display
		fp=fopen("data.wav","r");
		fread(&h,sizeof(h),1,fp); //read the first 44 bytes(size of of file) 
                                  //of file
		displayWAVHDR(h);
		fread(&sa,sizeof(short int),SAMPLE_RATE,fp);
		displayWAVdata(sa);	
		fclose(fp);
	}
		
	printf("Do you want to generate a testtone?(1:yes,0:no) ");
	printf("%d",&ans);
	if(ans == 1) testTone(1000,5);
}

