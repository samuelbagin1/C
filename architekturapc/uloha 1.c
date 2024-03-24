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




void fibonacci(int k) {
    int i=1;
    int p=1;
    int sum=i+p;

    printf("%d %d ", i, p);

    while (sum<=k) {
        printf("%d ", sum);
        i=p;
        p=sum;
        sum=p+i;
    }
}




//taylorov rad sinus

float faktorial(float k) {

    if (k<=1.0) {
        return 1.0;
    } else {
        return k*faktorial(k-1.0);
    }

}

//x na n-tu
float mocnina(float x, int n) {
    float numb=1;

    for (int i=0; i<n; ++i)
        numb*=x;

    return numb;
}

float absolutna(float x) {
    if (x<0) {
        return -x;
    }
    
    return x;
}

float absolut(float x) {
    if (x<0) {
        return -x;
    }
    
    return x;
}

int lessDegree(int degree) {
    while (degree>=360) {
        degree -= 360;
    }

    while (degree<=0) {
        degree += 360;
    }

    return degree;
}

float sinus(float radians, float epsilon) {
    radians=lessDegree(radians);

    printf("%f\n", radians);
    radians=radians*(3.141592653589/180);    //ak je uhol zadany v stupnoch a nie radianoch
    float num=radians;
    float numPred=0;
    float n=1;

    while (absolutna(numPred-num)>epsilon) {
        numPred=num;
        num+=(mocnina(-1, n)*mocnina(radians, 2*n+1))/absolut(faktorial(2*n+1));

        printf("%f,     %f,     %f,       %f\n", num, mocnina(radians, 2*n+1), absolut(faktorial(2*n+1)), n);
        n+=1.0;
    }

    return num;
}


void rimske(int n) {
    char s[32];
    int i=0;

    while (n!=0) {
        if (n>=90) {
            s[i]='X';
            s[i+1]='C';
            n-=90;
            i+=2;
        } else if (n>=50) {
            s[i]='L';
            n-=50;
            i++;
        } else if (n>=10) {
            s[i]='X';
            n-=10;
            i++;
        } else if (n>=9) {
            s[i]='I';
            s[i+1]='X';
            n-=9;
            i+=2;
        } else if (n>=5) {
            s[i]='V';
            n-=5;
            i++;
        } else if (n>=4) {
            s[i]='I';
            s[i+1]='V';
            n-=4;
            i+=2;
        } else if (n>=1) {
            s[i]='I';
            n-=1;
            i++;
        }
    }

    for (int j=0; j<i; ++j) {
        printf("%c", s[j]);
    }
}




int main() {
    int num, u;
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


    printf(" \n");
    fibonacci(30);

    printf("\n");
    printf("%f", sinus(-7777, 0.000000001));

    scanf("%d", &u);
    rimske(u);

    return 0;
}