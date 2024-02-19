#include <stdio.h>

void toBinary(int k) {
    int s[32];
    int i=0;

    while (k!=0) {
        if (k%2==0) {
            s[i]=0;
        } else {
            s[i]=1;
        }

        k=k/2;
        i++;
    }

    for (int j=i-1; j>=0; j--) {
        printf("%d", s[j]);
    }

    printf("\n");
}

void toHex(int k) {
    char s[32];
    int i=0;

    while (k!=0) {
        if (k%16==15) {
            s[i]='F';
        } else if (k%16==14) {
            s[i]='E';
        } else if (k%16==13) {
            s[i]='D';
        } else if (k%16==12) {
            s[i]='C';
        } else if (k%16==11) {
            s[i]='B';
        } else if (k%16==10) {
            s[i]='A';
        } else if (k%16==9) {
            s[i]='9';
        } else if (k%16==8) {
            s[i]='8';
        } else if (k%16==7) {
            s[i]='7';
        } else if (k%16==6) {
            s[i]='6';
        } else if (k%16==5) {
            s[i]='5';
        } else if (k%16==4) {
            s[i]='4';
        } else if (k%16==3) {
            s[i]='3';
        } else if (k%16==2) {
            s[i]='2';
        } else if (k%16==1) {
            s[i]='1';
        } else if (k%16==0) {
            s[i]='0';
        }

        k=k/16;
        i++;
    }

    for (int j=i-1; j>=0; j--) {
        printf("%c", s[j]);
    }

    printf("\n");
}

int main() {
    int num;
    char str;

    scanf("%d %c", &num, &str);

    printf("decimal\n");
    printf("%d\n", num);
    printf("%d\n", str);
    
    printf("binary\n");
    toBinary(num);
    toBinary(str);
    
    printf("hexadecimal\n");
    toHex(num);
    toHex(str);

    return 0;
}