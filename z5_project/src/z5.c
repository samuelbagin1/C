#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "monopoly.h" // Nemenit !!!
// Nevkladat monopoly.c !!!

char* getColorName(char* string) {
    char *result = malloc(100);
    for (int i=1; i<strlen(string)-1; i++) {
        result[strlen(result)]=string[i];
    }

    result[strlen(result)]='\0';
    return result;
}

char* getPropName(char* string) {
    char *result = malloc(100);
    for (int i=1; string[i]!='"'; i++) {
        result[strlen(result)]=string[i];
    }

    result[strlen(result)]='\0';
    return result;
}

int getPropPrice(char* string) {
    char *result = malloc(2056);
    int i=0;
    while (string[i]!=':') { i++; }

    for (int p=i+1; p<strlen(string); p++) { result[strlen(result)]=string[p]; }
    result[strlen(result)]='\0';

    int num;
    sscanf(result, "%d", &num);
    return num;
}


void printPrepB(SPACE *gameBoard, int num) {
    for (int i = 0; i < num; i++) {
        char* s;
        sprintf(s, "%d", i+1);
        strcat(s, ".");
        printf("%-3s  ", s);

        if (gameBoard[i].property!=NULL) {
            printf("%-20s  %d  %-7s", gameBoard[i].property->name, gameBoard[i].property->price, (char *) property_colors[gameBoard[i].property->color]);
        } else {
            printf("%s", space_types[gameBoard[i].type]);
        }

        if (i+1==num) { printf(""); } else { printf("\n"); }
    }
}

void printPrepT(PROPERTY *gameBoard, int num) {
    for (int i = 0; i< num; i++) {
        printf("%-20s  %d  %-7s", gameBoard[i].name, gameBoard[i].price, (char *) property_colors[gameBoard[i].color]);
        if (i+1==num) { printf(""); } else { printf("\n"); }
    }
}





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
    if (b==1) {
        inputFileB=fopen(bFile, "r");
        if (inputFileB==NULL) { printf("E1"); return 0; }
    }
    if (t==1) {
        inputFileT=fopen(tFile, "r");
        if (inputFileT==NULL) { printf("E1"); return 0; }
    }



    //prepinace b a t samostatne funguju

    //hlavny program
    if (b==1 && t==1) {

        int num;    //cislo hracich poli
        char word[1000];
        fgets(word, sizeof(word), inputFileB); //nacitanie cisla poli zo suboru
        sscanf(word, "%d", &num);

        SPACE gameBoard[num];
        PROPERTY propertyBoard[100];
        int i=0; //pozicia v gameBoard arrayi
        int g=0; //pozicia v propertyBoard arrayi
        char* colorName="";

        while (fgets(word, sizeof(word), inputFileB)) {
            word[strlen(word)-1]='\0';

            if (strcmp(word, "PROPERTY")==0) {
                gameBoard[i].type=Property;
                //if (pozGameProp>=24) { printf("E2"); return 0; }

                char prop[100];

                int ptr;
                while (fgets(prop, sizeof(prop), inputFileT)) {


                    prop[strlen(prop)-1]='\0';



                    if (prop[0]=='[') {
                        colorName=getColorName(prop);
                    } else {

                        propertyBoard[g].price=getPropPrice(prop);
                        strcpy(propertyBoard[g].name, getPropName(prop));
                        int kk;
                        for (int k=0; k<8; k++) { if (strcmp(property_colors[k],colorName)==0) { kk=k; }}
                        propertyBoard[g].color=kk;



                        g++;
                        break;
                    }

                }
                if (feof(inputFileT)) { printf("E2"); return 0;}

                gameBoard[i].property=&propertyBoard[g-1];


            } else {
                for (int k=0; k<6; k++) { if (strcmp(space_types[k],word)==0) { gameBoard[i].type=k; gameBoard[i].property=NULL; break;}}
            }





            i++;
        }

        //vypis
        printPrepB(gameBoard, i);



    } else if (t==1) {


        PROPERTY gameBoard[100];
        char word[100];

        int i=0; //pozicia v arrayi
        char* colorName="";
        while (fgets(word, sizeof(word), inputFileT)) {
            word[strlen(word)-1]='\0';

            if (word[0]=='[') {
                colorName=getColorName(word);
            } else {

                gameBoard[i].price=getPropPrice(word);
                strcpy(gameBoard[i].name, getPropName(word));
                int kk;
                for (int k=0; k<8; k++) { if (strcmp(property_colors[k],colorName)==0) { kk=k; }}
                gameBoard[i].color=kk;



                i++;
            }


        }

        //vypis
        printPrepT(gameBoard, i);



    } else if (b==1) {

        int num;    //cislo hracich poli
        char word[1000];
        fgets(word, sizeof(word), inputFileB); //nacitanie cisla poli zo suboru
        sscanf(word, "%d", &num);

        SPACE gameBoard[num];
        int i=0, pozGameProp=0, pozGameNull=0;

        while (fgets(word, sizeof(word), inputFileB)) {
            word[strlen(word)-1]='\0';

            if (strcmp(word, "PROPERTY")==0) {
                if (pozGameProp>=24) { printf("E2"); return 0; }
                for (int p=pozGameProp; p<24; p++) {
                    if (strcmp(word, space_types[game_board[p].type])==0) {
                        gameBoard[i].type=game_board[p].type;
                        gameBoard[i].property=game_board[p].property;
                        pozGameProp=p+1;
                        break;
                    }
                }


            } else {
                for (int p=pozGameNull; p<24; p++) {
                    if (strcmp(word, space_types[game_board[p].type])==0) {
                        gameBoard[i].type=game_board[p].type;
                        gameBoard[i].property=game_board[p].property;
                        pozGameNull=p+1;
                        break;
                    }
                }
            }




            i++;
        }

        //vypis
        printPrepB(gameBoard, num);
    }



    if (b==1) { fclose(inputFileB); }
    if (t==1) { fclose(inputFileT); }
    return 0;
}
