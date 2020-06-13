#ifndef INF1_2_WAVEREAD_H
#define INF1_2_WAVEREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef unsigned char byte1;
typedef unsigned short byte2;
typedef unsigned int byte4;
typedef struct _riff_header {
    char riff_title[4];
    byte4 riff_chank_size;
    char wave_title[4];
    char fmt_title[4];
    byte4 fmt_size;
    byte2 format_tag;
    byte2 n_channels;
    byte4 n_samples_per_sec;
    byte4 n_avg_bytes_per_sec;
    byte2 n_block_align;
    byte2 n_bits_per_sample;
    char Subchunk2ID[4];
    u_int32_t Subchunk2Size;
} riff_header;


typedef struct Wave {
    FILE *input;
    FILE *out;
    riff_header header;
    short* left;
    short* right;
    int maxType;
    int minType;
    char * buffC;
    short * buffS;
    char bytesPerSample;
} wav;


void printfHeader(riff_header *in);

void openWav(wav *file, char *in, char *out);

int normalize(wav *file);

void writeWav(wav *file);

void closeFile(wav *file);

#endif //INF1_2_WAVEREAD_H