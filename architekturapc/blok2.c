#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
//#include <conio.h>
#include <time.h>
//#include <windows.h>

void pamat() {  //2.2 - 3b
    char s[]="architektura_pocitacov_je_super_predmet"; //1
    printf("%s\n",s);
    
    int* ptr= &s;    //2
    printf("%d\n", ptr);
    
    printf("\n");

    ptr++;  //3
    *ptr='2';
    printf("%c\n", *ptr);

    /* ptr=100000000000000000;    //4
    *ptr='2';
    printf("%d\n", ptr); */ //nechce ani skompilovat


    int num=22;
    int* ptrr=&num;

    printf("\n");
    printf("%d\n",num);
    printf("%d\n",ptrr);
}

void vypis() {  //2.5.1 - 1b

    for (int i=0; i<=50; i++) {
        if (i<11) {
            printf("\x1b[32m%03d\n", i); //zelena
        } else if (i>=11 && i<=22) {
            printf("\x1b[31m%03d\n", i); //cervena
        } else if (i>=23 && i<=35) {
            printf("\x1b[34m%03d\n", i); //modra
        } else {
            printf("\x1b[35m%03d\n", i); //fialova
        }

        //usleep(1000000);
        printf("\x1b[0m");
    }

}

void semigrafika() {    //2.5.2 - 3b
    char meno[]="Honza Mrkva";
    char tel[]="0803 / 255 34446436753";
    int vyska=180, hmotnost=80, x, y;


    scanf("%d %d", &x, &y);

    int lengthMaxString=strlen(meno)>strlen(tel) ? strlen(meno) : strlen(tel);
    int length=13+lengthMaxString+2;

    int minusNum=lengthMaxString%2==1 ? 13 : 14;
    //printf("\033[2J");     //ocisti obrazovku
    printf("\033[%d;%dH", y, x);    //nastavi kurzor
    printf("\x1b[32m∣"); for (int i=0; i<(length-minusNum)/2; i++) printf("\x1b[32m—");
    printf("\x1b[33m zaznam 001 ");
    for (int i=0; i<(length-13)/2; i++) printf("\x1b[32m—"); printf("∣");

    printf("\033[%d;%dH|", y+1, x);
    for (int i=0; i<length-2; i++) printf("—");
    printf("|");


    //[%d;%dH - dava kurzord na x, y suradnice
    //x1b[32m - meni farbu
    printf("\033[%d;%dH\x1b[32m| \x1b[33m%-8s \x1b[32m| \x1b[33m%*s \x1b[32m|", y+2, x, "meno", lengthMaxString, meno);
    printf("\033[%d;%dH\x1b[32m|", y+3, x); for (int i=0; i<length-2; i++) printf("—"); printf("|");
    printf("\033[%d;%dH\x1b[32m| \x1b[33m%-8s \x1b[32m| \x1b[33m%*d cm \x1b[32m|", y+4, x, "vyska", lengthMaxString-3, vyska);
    printf("\033[%d;%dH\x1b[32m|", y+5, x); for (int i=0; i<length-2; i++) printf("—"); printf("|");
    printf("\033[%d;%dH\x1b[32m| \x1b[33m%-8s \x1b[32m| \x1b[33m%*d kg \x1b[32m|", y+6, x, "hmotnost", lengthMaxString-3, hmotnost);
    printf("\033[%d;%dH\x1b[32m|", y+7, x); for (int i=0; i<length-2; i++) printf("—"); printf("|");
    printf("\033[%d;%dH\x1b[32m| \x1b[33m%-8s \x1b[32m| \x1b[33m%*s \x1b[32m|", y+8, x, "tel.", lengthMaxString, tel);
    printf("\033[%d;%dH\x1b[32m|", y+9, x); for (int i=0; i<length-2; i++) printf("—"); printf("|");

}





void htmlko() {     //2.3.1 - 2b
        FILE *inputFile, *outputFile;
        char *inputFileName = "inputFile.html";
        char *outputFileName = "output.html";
        signed char ch;

        inputFile = fopen(inputFileName, "r");
        outputFile = fopen(outputFileName, "w");


        while ((ch = fgetc(inputFile))!=EOF) {
            if (ch==(char)165) {
                fputc((char)188, outputFile);
            } else if (ch==(char)169) {
                fputc((char)138, outputFile);
            } else if (ch==(char)171) {
                fputc((char)141, outputFile);
            } else if (ch==(char)174) {
                fputc((char)142, outputFile);
            } else if (ch==(char)181) {
                fputc((char)190, outputFile);
            } else if (ch==(char)185) {
                fputc((char)154, outputFile);
            } else if (ch==(char)187) {
                fputc((char)157, outputFile);
            } else if (ch==(char)190) {
                fputc((char)158, outputFile);
            } else {
                fputc(ch, outputFile);
            }
        }

        fclose(inputFile);
        fclose(outputFile);
        printf("hotovo");


}


//windows kod
/*
int randomChar() {
    return rand() % (122+1-97)+97;
}

void meranie() {        //2.6 - 4b
    printf("\n\n\n________NAVOD________\n");
    printf("F1: navod | F2: spusti meranie | ESC: program skonci\n\n\n\n");

    int ch=0;
    COORD c;
    c.X = 40;
    c.Y = 16;
    while (ch!=27) {
        ch=getch();

        if (ch==0) {
            ch=-getch();

            if (ch==-59) {      //F1
                printf("\nukaze sa ti charakter a ty musis za co najkratsi cas stlacit dany charakter\n");
            } else if (ch==-60) {

                while (ch!=27) {
                    clock_t Start, Koniec;
                    float Trvanie;
                    int i=1;
                    int randmCharr=rand() % (122+1-97)+97;


                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);


                    printf("stlac: %c ------ X,XX s      stlacene: ", randmCharr);
                    Start = clock();
                    do {
                        ch=getch();
                        putchar(ch);

                        if (ch==27 || ch==randmCharr) i=0;
                    } while (i!=0);
                    Koniec = clock();

                    Trvanie = (float)(Koniec-Start) / 1000;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                    printf("stlac: %c ------ %.2f s", randmCharr, Trvanie);
                    c.Y+=1;
                }
            }

        }

        if (ch==27) {
            printf("KONIEC");
            ch=getch();
        }

    }


} */



//to do
//2.3.1 - 2b
//2.5.2 - 3b        najdi najdlhsi string (bude zrejme meno) a dlzku slova vyuzi ako pocet znakov -------
//2.6 - 4b


int main() {

    //pamat();
    
    //vypis();

    //semigrafika();

    htmlko();

    //meranie();


    return 0;
}
