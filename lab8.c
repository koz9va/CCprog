#include "waveRead.h"

int main(int argc, char **argv) {

    wav test;

    if (argc < 3) {
        printf("There are not enough arguments in program call :(\n");
        return 5;
    }

    if (argv[1] == argv[2]) {
        printf("Same file names!\n");
        return 7;
    }


    openWav(&test, argv[1], argv[2]);

    normalize(&test);

    printfHeader(&test.header);

    writeWav(&test);

    closeFile(&test);

    printf("\n/////%s was normalized to %s///////\n", argv[1], argv[2]);

    return 0;
}