#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h" // ReLU funkcia a pomocne funkcie
#include "data.h" // Makra, vahy a bias hodnoty

double poleToReturn[10];




//funkcie
int findMaxIndex(double x[]) {
    int index=0;
    double max=x[0];
    for (int j=1; j<10; j++) {
        if (x[j]>max) {
            max=x[j];
            index=j;
        }
    }

    return index;
}

double findMaxHod(double x[]) {
    double max=x[0];
    int length = sizeof(x) / sizeof(x[0]);

    for (int j=0; j<length; j++) {
        if (x[j]>max) {
            max=x[j];
        }
    }

    return max;
}


void softmax(double x[]) {
    for (int j=0; j<10; j++) {

        double sumMenovatel=0;
        for (int jj=0; jj<10; jj++) {
            sumMenovatel+=exp(x[jj]-findMaxHod(x));
        }

        poleToReturn[j]=exp(x[j]-findMaxHod(x))/sumMenovatel;
    }
}





int main(void) {
    int mode, index;

    scanf("%d", &mode);



    if (mode==1) {      //vypis vah pre zvoleny neuron - funguje
        scanf("%d", &index);

        if (index>=0 && index<=9) {
            int poc=0;

            for (int i=index*784; i<index*784+784; i++) {
                printf(" %8.2lf", weights[i]);
                ++poc;

                if (poc==10) {
                    printf("\n");
                    poc=0;
                }

            }
        }



    } else if (mode==2) {       //vypis vazeneho suctu pre zvol. neuron a obrazok - nefunguje
        scanf("%d", &index);

        if (index>=0 && index<=9) {
            const unsigned int len=784;
            double data[len];
            double sum=0;

            load_data(data, len);
            for (int i=0; i<784; i++) {
                sum+=data[i]*weights[i+index*784];
            }

            sum+=bias[index];

            printf("%.2lf", relu(sum));
        }



    } else if (mode==3) {       //vypis hodnoty aktivacnej funkcie - funguje
        double num;
        scanf("%lf", &num);
        printf("%.2lf", relu(num));



    } else if (mode==4) {       //vypis vyp hodnot funkcie softmax - funguje
        double arr[10];

        for (int i=0; i<10; i++) {
            scanf("%lf", &arr[i]);
        }

        softmax(arr);
        for (int i=0; i<10; i++) {
            printf("%.2lf ", poleToReturn[i]);
        }



    } else if (mode==5) {       //vypis indexu najvacsieho prvku v poli - funguje
        for (int i=0; i<10; i++) {
            scanf("%lf", &poleToReturn[i]);
        }

        printf("%d", findMaxIndex(poleToReturn));



    } else if (mode==6) {       //vypis nacitaneho obrazku cislice - funguje
        const unsigned int len=784;
        double data[len];
        load_data(data, len);

        print_image(data, 28, 28);



    } else if (mode==7) {
        const unsigned int len=784;
        double data[len];
        double dataNeuronObrazok[len];
        load_data(data, len);


        for (int i=0; i<10; i++) {
            double sum=0;
            for (int ii=0; ii<784; ii++) {
                sum+=data[ii]*weights[ii+i*784];
            }

            dataNeuronObrazok[i]=sum+bias[i];
        }

        softmax(dataNeuronObrazok);
        printf("%d", findMaxIndex(poleToReturn));
    }
    
    return 0;
}
