/*Usually there are 3 parts in a header file:
 the first part is data structure definition,
 the second part is a list of defined constants,
 the first part is a list of function prototypes */

//data structure definition
typedef struct{
        char ChunkID[4];
        int ChunkSize;
        char Format[4];
        char Subchunk1ID[4];
        int Subchunk1Size;
        short int AudioFormat;
        short int NumChannels;
        int SampleRate;
        int ByteRate;
        short int BlockAlign;
        short int BitsPerSample;
        char Subchunk2ID[4];
        int Subchunk2Size;
}WAVHDR;

//#define DEBUG
#define SAMPLE_RATE 16000
#define PI 3.1415926
//funtion prototypes
void displayWAVHDR(WAVHDR h);
void printID(char *);
void fillID( char *d,const char s[]);
void testTone(int f,double d);
void displayWAVdata(short int s[]);
