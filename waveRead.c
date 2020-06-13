#include "waveRead.h"


void printfHeader(riff_header *in) {
    printf("Wav file Header read:\n");
    printf("File Type: %s\n", in->riff_title);
    printf("File Size: %u\n", in->riff_chank_size);
    printf("WAV Marker: %s\n", in->wave_title);
    printf("Format Name: %s\n", in->fmt_title);
    printf("Format Length: %u\n", in->fmt_size);
    printf("Format Type: %hd\n", in->format_tag);
    printf("Number of Channels: %hd\n", in->n_channels);
    printf("Sample Rate: %u\n", in->n_samples_per_sec);
    printf("Sample Rate * Bits/Sample * Channels / 8: %u\n", in->n_avg_bytes_per_sec);
    printf("Bits per Sample * Channels / 8.1: %hd\n", in->n_block_align);
    printf("Bits per Sample: %hd\n", in->n_bits_per_sample);
}


void openWav(wav *file, char *in, char *out) {
    int i;
    const char riff[] = "RIFF";
    short * ptr;
    int cnt = 0;
    file->input = fopen(in, "rb");
    file->out = fopen(out, "wb");
    FILE *w = fopen("w.txt", "w");


    if (file->input == NULL || file->out == NULL) {
        printf("There is no %s or %s already exists in folder :(\n", in, out);
        return;
    }

    fread(&file->header, sizeof(file->header), 1, file->input);

    file->bytesPerSample = (char)(file->header.n_bits_per_sample/8);

    for (i = 0; i < 4; i++) {
        if (riff[i] != file->header.riff_title[i]) {
            printf("Sorry, I can't read this type of file :(\n");
            return;
        }
    }

    fwrite(&file->header, sizeof(file->header), 1, file->out);



    if (file->header.n_bits_per_sample == 8) {
        file->maxType = (int) ((1u << ((sizeof(char) * 8) - 1u)) - 1);
        file->minType = -(int) ((1u << ((sizeof(char) * 8) - 1u)));
        file->buffC = malloc(file->header.Subchunk2Size);
        fread(file->buffC, sizeof(char), file->header.Subchunk2Size, file->input);
    }
    if (file->header.n_bits_per_sample == 16) {
        file->maxType = (int) ((1u << ((sizeof(short) * 8) - 1u)) - 1);
        file->minType = -(int) ((1u << ((sizeof(short) * 8) - 1u)));
        file->buffS = malloc(file->header.Subchunk2Size);
        fread(file->buffS, sizeof(short), file->header.Subchunk2Size/2, file->input);
        ptr = file->buffS;

        while(ptr < file->buffS+500000){
            if(cnt == 512)printf("\n");
            fprintf(w, "%d ", *ptr);
            ptr++;
            cnt++;
        }
    }

    fclose(w);

}

int normalize(wav *file) {
    float pGainRight = 1.f;
    float nGainRight = 1.f;
    float pGainLeft = 1.f;
    float nGainLeft = 1.f;
    u_int32_t i;
    short * ptrS;
    char * ptrC;
    short maxRight = 0;
    short minRight = 0;
    short maxLeft = 0;
    short minLeft = 0;

    if(file->bytesPerSample == 1){
        ptrC = file->buffC;
        while(*ptrC != '\0'){
            if(*ptrC > maxRight) maxRight = *ptrC;
            if(*ptrC < minRight) minRight = *ptrC;
            ptrC++;
            if(*ptrC > maxLeft) maxLeft = *ptrC;
            if(*ptrC < minLeft) minLeft = *ptrC;
            ptrC++;
        }
    }else if(file->bytesPerSample == 2){
        ptrS = file->buffS;
        while(ptrS < file->buffS+file->header.Subchunk2Size/2){
            if(*ptrS > maxRight) maxRight = *ptrS;
            if(*ptrS < minRight) minRight = *ptrS;
            ptrS++;
            if(*ptrS > maxLeft) maxLeft = *ptrS;
            if(*ptrS < minLeft) minLeft = *ptrS;
            ptrS++;
        }
    }else return 1;

    pGainRight = (float) file->maxType / (float) maxRight;
    nGainRight = (float) file->minType / (float) minRight;
    pGainLeft = (float) file->maxType / (float) maxLeft;
    nGainLeft = (float) file->minType / (float) minLeft;
    printf("Positive Right Rain %f\n Neg R Gain %f\n Pos L gain %f\n Neg L gain %f\n", pGainRight, nGainRight, pGainLeft, nGainLeft);
    if (file->bytesPerSample == 1) {
        ptrC = file->buffC;
        while(*ptrC != '\0'){
            if(*ptrC < 0){
                *ptrC = (char)((float)(*ptrC) * (float)nGainRight);
            }else{
                *ptrC = (char)((float)(*ptrC) * (float)pGainRight);
            }
            ptrC++;
            if(*ptrC < 0){
                *ptrC = (char)((float)(*ptrC) * (float)nGainLeft);
            }else{
                *ptrC = (char)((float)(*ptrC) * (float)pGainLeft);
            }
            ptrC++;
        }

    } else if (file->bytesPerSample == 2) {
        ptrS = file->buffS;
        while(ptrS < file->buffS+file->header.Subchunk2Size/2){
            if(*ptrS < 0){
                *ptrS = (short)((float)(*ptrS) * (float)nGainRight);
            }else{
                *ptrS = (short)((float)(*ptrS) * (float)pGainRight);
            }
            ptrS++;
            if(*ptrS < 0){
                *ptrS = (short)((float)(*ptrS) * (float)nGainLeft);
            }else{
                *ptrS = (short)((float)(*ptrS) * (float)pGainLeft);
            }
            ptrS++;
        }
    }
    return 0;
}

void writeWav(wav *file) {
    u_int32_t i;

    if(file->bytesPerSample == 1){
        fwrite(file->buffC, file->header.Subchunk2Size, 1, file->out);
    }else if(file->bytesPerSample == 2){
        fwrite(file->buffS, file->header.Subchunk2Size, 1, file->out);
    }
    else {
        printf("There is an error in allocated buffers :(\n");
        exit(EXIT_FAILURE);
    }

}

void closeFile(wav *file) {
    fclose(file->input);
    fclose(file->out);

    if(file->bytesPerSample == 1){
        free(file->buffC);
    }else{
        free(file->buffS);
    }

}