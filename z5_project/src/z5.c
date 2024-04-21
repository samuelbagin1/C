#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monopoly.h" // Nemenit !!!
// Nevkladat monopoly.c !!!

int main(int argc, char *argv[]) {
    int b=0, t=0;
    int c;
    char* bFile, * tFile;


    while ((c=getopt(argc, argv, ":b:t:"))!=-1) {
        switch (c) {
            case 'b':
                b=1;
                bFile=optarg;
                break;
            case 't':
                t=1;
                tFile=optarg;
                break;
            case ':':   //missing argument
                break;
            case '?':   //unknown option
                break;
        }
    }

    FILE *inputFileB, *inputFileT;
    if (b==1) { inputFileB=fopen(bFile, "r"); }
    if (t==1) { inputFileT=fopen(tFile, "r"); }
    if (inputFileB==NULL || inputFileT==NULL) {
        printf("E1");
        return 0;
    }




    return 0;
}
