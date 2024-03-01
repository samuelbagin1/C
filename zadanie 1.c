#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double binarSkok(double x) {
    if (x<0) {
        return 0;
    }

    return 1.0;
}

double sigmoida(double x) {
    return 1/(1+exp(-x));
}

double hyperbolicTan(double x) {
    return (exp(x)-exp(-x))/(exp(x)+exp(-x));
}

double gauss(double x) {
    return exp(-x*x);
}

double relu(double x) {
    return (x>0) ? x : 0;
}

double squareplus(double x, double b) {
    return 0.5*(x+sqrt(x*x+b));
}


int main() {
    char input;
    scanf("%c", &input);

    if (input=='0') {
        char xStartStr[32], xStopStr[32], stepStr[32];
        scanf("%s %s %s", xStartStr, xStopStr, stepStr);


        double xStart, xStop, step;
        if (sscanf(xStartStr, "%lf", &xStart)==0 || sscanf(xStopStr, "%lf", &xStop)==0 || sscanf(stepStr, "%lf", &step)==0) {

            printf("E2\n");
            return 0;

        } else {
            sscanf(xStartStr, "%lf", &xStart);  //premena zo stringu do double
            sscanf(xStopStr, "%lf", &xStop); 
            sscanf(stepStr, "%lf", &step);

            if (xStart>=xStop) {

                printf("E3\n");
                return 0;

            } else {

                for (double j=xStart; j<=xStop; j+=step) {
                    printf("%10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f\n", j, binarSkok(j), sigmoida(j), hyperbolicTan(j), gauss(j), relu(j), squareplus(j, 4));
                }

            }
            
        }

        
    } else if (input=='1') {
        char inputt[32];
        double inputDouble;

        do {
            scanf("%s", inputt);

            if (sscanf(inputt, "%lf", &inputDouble)!=0) {
                sscanf(inputt, "%lf", &inputDouble);
                printf("%10.2f %10.2f %10.2f %10.2f %10.2f %10.2f %10.2f\n", inputDouble, binarSkok(inputDouble), sigmoida(inputDouble), hyperbolicTan(inputDouble), gauss(inputDouble), relu(inputDouble), squareplus(inputDouble, 4));
            }

        } while (sscanf(inputt, "%lf", &inputDouble)!=0);

    } else {

        printf("E1\n");

    }

    return 0;
}