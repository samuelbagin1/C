#include <stdio.h>

int ifPrvo(int k) {
    int p;
    for (p=2; p<k; p++) {
        if (k%p==0) {
            return 0;
        }
    }
    return 1;
}

void primeFactors(int a, int m) {
    int i=2;
    int n=0;

    if (a>1) {
        while (i<=a && n<m) {
            if (a%i==0 && ifPrvo(i)==1) {
                printf("%d\n", i);
                ++n;
            }
            
            ++i;
        }
        
    } else {
        printf("ERROR\n");
    }
}

int main() {
    int num1, num2;
    scanf("%d %d", &num1, &num2);

    primeFactors(num1, num2);
    return 1;

}