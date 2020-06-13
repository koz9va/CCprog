#include "waveRead.h"
#include <math.h>

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

    file->input = fopen(in, "rb");
    file->out = fopen(out, "wb");

    if (file->input == NULL || file->out == NULL) {
        printf("There is no %s or %s already exists in folder :(\n", in, out);
        return;
    }

    fread(&file->header, sizeof(file->header), 1, file->input);

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

        file->first8bit = (char *) malloc((file->header.Subchunk2Size / 2) * sizeof(char));
        file->sec8bit = (char *) malloc((file->header.Subchunk2Size / 2) * sizeof(char));

        file->first16bit = NULL;
        file->sec16bit = NULL;

        file->elemNum = file->header.Subchunk2Size / 2;

        for (i = 0; i < file->header.Subchunk2Size / 2; i++) {
            fread(&file->first8bit[i], sizeof(char), 1, file->input);
            fread(&file->sec8bit[i], sizeof(char), 1, file->input);
        }
    }
    if (file->header.n_bits_per_sample == 16) {
        file->maxType = (int) ((1u << ((sizeof(short) * 8) - 1u)) - 1);
        file->minType = -(int) ((1u << ((sizeof(short) * 8) - 1u)));

        file->first16bit = (short *) malloc((file->header.Subchunk2Size / 4) * sizeof(short));
        file->sec16bit = (short *) malloc((file->header.Subchunk2Size / 4) * sizeof(short));

        file->elemNum = file->header.Subchunk2Size / 4;

        for (i = 0; i < file->header.Subchunk2Size / 4; i++) {
            fread(&file->first16bit[i], sizeof(short), 1, file->input);
            fread(&file->sec16bit[i], sizeof(short), 1, file->input);
        }
        file->first8bit = NULL;
        file->sec8bit = NULL;

    }


}

int normalize(wav *file) {
    float pGain = 1.f;
    float nGain = 1.f;
    u_int32_t i;
    short fmax;
    short smax;
    short fmin;
    short smin;


    if (file->first8bit != NULL && file->sec8bit != NULL) {
        fmax = file->first8bit[0];
        fmin = fmax;
        smax = file->sec8bit[0];
        smin = smax;

        for (i = 0; i < file->elemNum; i++) {
            if (file->first8bit[i] > fmax) fmax = file->first8bit[i];
            if (file->first8bit[i] < fmin) fmin = file->first8bit[i];
            if (file->sec8bit[i] > smax) smax = file->sec8bit[i];
            if (file->sec8bit[i] < smin) smin = file->sec8bit[i];
        }


    } else if (file->first16bit != NULL && file->sec16bit != NULL) {
        fmax = file->first16bit[0];
        fmin = fmax;
        smax = file->sec16bit[0];
        smin = smax;
        for (i = 0; i < file->elemNum; i++) {
            if (file->first16bit[i] > fmax) fmax = file->first16bit[i];
            if (file->first16bit[i] < fmin) fmin = file->first16bit[i];
            if (file->sec16bit[i] > smax) smax = file->sec16bit[i];
            if (file->sec16bit[i] < smin) smin = file->sec16bit[i];
        }


    } else return 1;

    pGain = (float) file->maxType / (float) fmax;
    nGain = (float) file->minType / (float) fmin;

    if (file->first8bit != NULL && file->sec8bit != NULL) {

        for (i = 0; i < file->elemNum; i++) {
            if (file->first8bit >= 0) {
                file->first8bit[i] = (char) floorf((float) file->first8bit[i] * pGain);
            } else {
                file->first8bit[i] = (char) floorf((float) file->first8bit[i] * nGain);
            }
            if (file->sec8bit >= 0) {
                file->sec8bit[i] = (char) floorf((float) file->sec8bit[i] * pGain);
            } else {
                file->sec8bit[i] = (char) floorf((float) file->sec8bit[i] * nGain);
            }
        }
    } else if (file->first16bit != NULL && file->sec16bit != NULL) {
        for (i = 0; i < file->elemNum; i++) {
            if (file->first16bit >= 0) {
                file->first16bit[i] = (short) floorf((float) file->first16bit[i] * pGain);
            } else {
                file->first16bit[i] = (short) floorf((float) file->first16bit[i] * nGain);
            }
            if (file->sec16bit >= 0) {
                file->sec16bit[i] = (short) floorf((float) file->sec16bit[i] * pGain);
            } else {
                file->sec16bit[i] = (short) floorf((float) file->sec16bit[i] * nGain);
            }
        }
    }
    return 0;
}

void writeWav(wav *file) {
    u_int32_t i;

    if (file->first8bit != NULL && file->sec8bit != NULL) {
        for (i = 0; i < file->elemNum; i++) {
            fwrite(&file->first8bit[i], sizeof(char), 1, file->out);
            fwrite(&file->sec8bit[i], sizeof(char), 1, file->out);
        }
    } else if (file->first16bit != NULL && file->sec16bit != NULL) {
        for (i = 0; i < file->elemNum; i++) {
            fwrite(&file->first16bit[i], sizeof(short), 1, file->out);
            fwrite(&file->sec16bit[i], sizeof(short), 1, file->out);
        }
    } else {
        printf("There is an error in allocated buffers :(\n");
        exit(EXIT_FAILURE);
    }

}

void closeFile(wav *file) {
    fclose(file->input);
    fclose(file->out);
    if (file->header.n_bits_per_sample == 8) {
        free(file->first8bit);
        free(file->sec8bit);
    }
    if (file->header.n_bits_per_sample == 16) {
        free(file->first16bit);
        free(file->sec16bit);
    }

}