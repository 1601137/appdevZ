#include <stdio.h>
#include "wave.h"
#include <math.h>
#include "screen.h"
#include "comm.h"

//function definition
void printID(char s[]){
	int i;
	for(i=0;i<4;i++)putchar(s[i]);
	printf("\n");
}
//printID() and fileID() are so-called local functions because
//they are merely used by the functions in file/module

void fillID( char *d,const  char s[]){
	int i;
	for(i=0;i<4;i++) *d++=s[i];
}


void testTone(int f,double d){
	WAVHDR h;
	FILE *fp;
	int i;
	short int sample;
 	fp=fopen("testtone.wav","w");
	fillID(h.ChunkID,"RIFF");
	fillID(h.Format, "WAVE");
	fillID(h.Subchunk1ID,"fmt ");
	fillID(h.Subchunk2ID,"data");
	//Chunk size will be calculated later
	h.Subchunk1Size =16;
	h.AudioFormat=1;
	h.NumChannels=1;
	h.SampleRate=SAMPLE_RATE;
	h.BitsPerSample =16;
	h.ByteRate=SAMPLE_RATE*h.NumChannels*(h.BitsPerSample/8);
	h.BlockAlign =h.NumChannels*(h.BitsPerSample/8);
	h.Subchunk2Size =(int)h.ByteRate*d;
	h.ChunkSize=h.Subchunk2Size+36;
	fwrite(&h,sizeof(h),1,fp); //write the header to file
	for(i=0;i<SAMPLE_RATE*d;i++){
		sample=32767*sin(2*PI*f*i/SAMPLE_RATE);
		fwrite(&sample,sizeof(sample),1,fp);
	}
	fclose(fp);
	printf("Test tone created!\n");
} 

void displayWAVHDR(WAVHDR h){
	double duration;
	duration = (double)h.Subchunk2Size/h.ByteRate;
#ifdef DEBUG
	printf("Chunk ID: "); printID(h.ChunkID);
	printf("Chunk size: %d\n",h.ChunkSize);
	printf("Format: "); printID(h.Format);
	printf("Subchunk1 ID: ");printID(h.Subchunk1ID);
	printf("Subchunk1 size: %d\n",h.Subchunk1Size);
	printf("Audio Format: %d\n",h.AudioFormat);
	printf("Num of Channels: %d\n",h.NumChannels);
	printf("Sample rate: %d\n",h.SampleRate);
	printf("Byte rate: %d\n",h.ByteRate);
	printf("Block Align: %d\n",h.BlockAlign);
	printf("Bits / Sample: %d\n",h.BitsPerSample);
	printf("Subchunk2 ID: ");printID(h.Subchunk2ID);
	printf("Subchunk2 size: %d\n",h.Subchunk2Size);
	printf("Duration: %.3f sec\n",duration);
#else
	gotoXY(1,1);setFGcolor(RED); printf("%.2f sec",duration);
	gotoXY(1,10);setFGcolor(CYAN); printf("%d bit/s",h.BitsPerSample);
	gotoXY(1,20);setFGcolor(YELLOW); printf("%d sps",h.SampleRate);
	resetColors(); fflush(stdout);
#endif
}

//displayWAVdata function dispalys 80 pieces of RMS value on terminal screen,but 
//this amount are still too much to send.According to the SLM standard,
//we need to send short Leq values ,which is 8 pieces per second
void displayWAVdata(short int s[]){
	int i,j;
	double sum200,rms200;
	//the following variables are used to calculate short Leq
	double Leq[8],sum8=0.0;

	for(i=0;i<80;i++){
		sum200 = 0.0; //initiate accumulater for 200 samples
		for(j=0; j<SAMPLE_RATE/80; j++){
			sum200 += (*s)*(*s);
			s++;
		}
		sum8 += sum200;//accumulate current sum200 to sum8
		if(i%10==9){       
			Leq[i/10] = sqrt(sum8/SAMPLE_RATE/8);//calculate RMS of 2000 samples.
			sum8=0.0 ;//reset sum8 for next Leq value
		}
		rms200=sqrt(sum200/200);
#ifdef DEBUG	//confitional compiling 
		printf("%2d:%10.2f",i,rms200);
#else 
		displayBar(rms200, i+1);
#endif
	}  //end of for(1)
//	printf("data sent\n");

#ifdef COMM
	send_data(Leq);
#endif
}
