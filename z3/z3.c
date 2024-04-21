#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define EMPTY_LINE "\n"
#define MAX_LINE 1000
#define MAX_WORD 20


//-d (cislice), -p (interpunkcia), -r (case sensitive), -R (insens), -s (split view)
int main (int argc, char *argv[]){

    int d=0, p=0, s=0, r=0, R=0;
    int c;


    while ((c = getopt (argc, argv, ":dpr:R:s"))!=-1) {
        switch (c) {
            case 'd':
                d=1;
                break;
            case 'p':
                p=1;
                break;
            case 's':
                s=1;
                break;
            case 'r':
                r=1;
                break;
            case 'R':
                R=1;
                break;
            case ':':   //missing argument
                printf("E2");
                return 0;
            case '?':   //unknown option
                printf("E1");
                return 0;
        }
    }

    if (optarg!=NULL) {
        for (int aaa=optind-1; aaa<argc; aaa++) {
            if (strlen(argv[aaa])>20 || strlen(argv[aaa])==0) {
                printf("E3");
                return 0;
            }
        }
    }

    char arr[1000][1001];
    int i=0;

    while (1) {
        fgets(arr[i],1001,stdin);
        if (strcmp(arr[i], "\n")==0) break;
        arr[i][strcspn(arr[i], "\n")] = '\0';

        i++;
    }




    char arr1[1000][1001];

    if (d==1 && p==1) {
        for (int j=0; j<i; j++) {
            for (int k=0; k<strlen(arr[j]); k++) {

                if (isdigit(arr[j][k])!=0) {
                    ;
                }else if (ispunct(arr[j][k])!=0) {
                    ;
                } else {
                    arr1[j][strlen(arr1[j])]=arr[j][k];
                }
            }
        }
    }else if (d==1) {
        for (int j=0; j<i; j++) {
            for (int k=0; k<strlen(arr[j]); k++) {

                if (isdigit(arr[j][k])==0) arr1[j][strlen(arr1[j])]=arr[j][k];

            }
        }
    }else if (p==1) {
        for (int j=0; j<i; j++) {
            for (int k=0; k<strlen(arr[j]); k++) {

                if (ispunct(arr[j][k])==0) arr1[j][strlen(arr1[j])]=arr[j][k];

            }
        }
    } else {
        for (int j=0; j<i; j++) {
            for (int k=0; k<strlen(arr[j]); k++) {

                arr1[j][strlen(arr1[j])]=arr[j][k];

            }
        }
    }

    struct Data {
        int index;
        char string1[1001];
        char string2[1001];
    };
    struct Data arr2[1000];

    if (s==1) {
        int p=0;
        int f=0;
        for (int j=0; j<i; j++) {
            int t=0;
            for (int k=0; k<strlen(arr1[j]); k++) {
                if (isalpha(arr1[j][k])!=0) {
                    arr2[p].string1[t] = arr1[j][k];
                    t++;
                }else if (isalpha(arr1[j][k-1])!=0 && (isdigit(arr1[j][k])!=0 || ispunct(arr1[j][k])!=0 || isspace(arr1[j][k])!=0)) {
                    f++;
                    arr2[p].index=f;
                } else p++;
            }
        }
    }

    //arr1[j][strlen(arr1[j])]=arr[j][k]; -kopirovanie do stringu
    //arr1[j][k]==argv[aaa] && (ispunct(arr1[j][k-1])==0 || isdigit(arr1[j][k-1])==0 || arr1[j][k-1]==" " || k==0)


    if (r==1) {
        for (int j=0; j<i; j++) {

            if (argc==optind) {
                for (int k=0; k<strlen(arr1[j]); k++) {
                    for (int ap=0; ap<strlen(optarg); ap++) {
                        if (isalpha(arr1[j][k+ap])==0) {
                            break;
                        } else {
                            arr1[j][k+ap]=optarg[ap];
                        }
                    }
                }
            } else {
                for (int aa=argc-1; aa>=optind; aa--) {
                    int k=0;
                    while (k<strlen(arr1[j])) {

                        int replace=1;
                        for (int ap=0; ap<strlen(argv[aa]); ap++) {
                            if (argv[aa][ap]!=arr1[j][k+ap] || (isalpha(arr1[j][k+ap-1])!=0 && ap==0)) {
                                replace=0;
                                break;
                            }
                        }

                        if (replace==1) {
                            for (int ap=0; ap<strlen(optarg); ap++) {
                                if (isalpha(arr1[j][k+ap])==0) {
                                    break;
                                } else {
                                    arr1[j][k+ap]=optarg[ap];
                                }
                            }
                        }

                        k++;
                    }
                }
            }
        }
    } else if (R==1) {
        for (int j=0; j<i; j++) {
            for (int aa=argc-1; aa>=optind; aa--) {
                int k=0;
                while (k<strlen(arr1[j])) {

                    int replace=1;
                    for (int ap=0; ap<strlen(argv[aa]); ap++) {
                        if (tolower(argv[aa][ap])!=tolower(arr1[j][k+ap]) || (isalpha(arr1[j][k+ap-1])!=0 && ap==0)) {
                            replace=0;
                            break;
                        }
                    }

                    if (replace==1) {
                        for (int ap=0; ap<strlen(optarg); ap++) {
                            if (isalpha(arr1[j][k+ap])==0) {
                                break;
                            } else {
                                arr1[j][k+ap]=optarg[ap];
                            }
                        }
                    }


                    k++;
                }
            }
        }
    }

    if (s==1) {
        int p=0;
        for (int j=0; j<i; j++) {
            int t=0;
            for (int k=0; k<strlen(arr1[j]); k++) {
                if (isalpha(arr1[j][k])!=0) {
                    arr2[p].string2[t]=arr1[j][k];
                    t++;
                } else p++;
            }
        }

        int maxString=0;
        for (int j=0; j<p; j++) {
            if (strlen(arr2[j].string1)>maxString) {
                maxString=strlen(arr2[j].string1);
            } else if (strlen(arr2[j].string2)>maxString) {
                maxString=strlen(arr2[j].string2);
            }
        }

        for (int j=0; j<p; j++) {
            printf("%d. %-*s:%-*s\n", arr2[p].index, maxString, arr2[j].string1, maxString, arr2[j].string2);
        }
    } else {
        for (int j=0; j<i; j++) {
            printf("%s\n", arr1[j]);
        }
    }


    return 0;
}