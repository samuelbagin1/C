#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int randomChar() {
    return rand() % (122+1-97)+97;
}

void meranie() {        //2.6
    printf("\n\n\n________NAVOD________\n");
    printf("F1: navod | F2: spusti meranie | ESC: program skonci\n\n\n\n");

    int ch=0;
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
                    COORD c;
                    c.X = 40;
                    c.Y = 16;
 
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
                    printf("\033[%d;%dHstlac: %c ------ %.2f s", y, x, randmCharr, Trvanie);
                }
            }

        }

        if (ch==27) printf("KONIEC");
    }


}


int main() {
    meranie();

    return 0;
}
