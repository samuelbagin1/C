#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <locale.h>

#define SERVER_IP "147.175.115.34"  // server`s IP
#define SERVER_PORT 777       // server`s port

FILE *outputLog;
char *outputFileName = "outputLog.txt";

int y=10;

int isPrime(int j) {
    for (int i=2; i<j; i++) {
        if (j%i==0) { return 0; }
    }

    return 1;
}

char* primeString(char* buffer) {
    char *result = malloc(2056);
    for (int i=1; i<strlen(buffer); i++) {
        if (isPrime(i+1)==1) {
            result[strlen(result)]=buffer[i];
        }
    }

    result[strlen(result)]='\n';
    return result;
}

int writeWholeWord(const char* buff, int i) {
    for (int p=i+1; p<strlen(buff); p++) {
        if (buff[p]==' ') { return p-i; }
    }

    return strlen(buff) - i;
}



void sendGet(int sockfd, char *message, int decrypt) {
    printf("\n");
    printf("\n");
    y+=2;
    char buffer[1024] = {0};
    char res[2056];

    // Send message to server
    send(sockfd, message, strlen(message), 0);
    strcpy(res,"Message sent to server: ");
    strcat(res, message);
    int x=1;
    printf("\033[34m");     //modra farba
    for (int i=0; i<strlen(res); i++) {
        fputc(res[i], outputLog);
        if (writeWholeWord(message, i)+x>40 && message[i-1]==' ') {
            printf("\n");
            y++;
            x=1;
            printf("\033[%d;%dH%c", y, x, res[i]);
        } else {
            printf("\033[%d;%dH%c", y, x, res[i]);
        }
        fflush(stdout);
        //usleep(20000);
        if (x<40) { x++; } else { x=1; printf("\n"); y++; }
    }

    fputc('\n', outputLog); //novy riadok v subore

    // Receive response from server
    if (decrypt>0) {
        read(sockfd, buffer, 148);
        for (int i = 0; i<148; i++) {
            buffer[i]^=decrypt;
        }

    } else if (decrypt<0) {
        read(sockfd, buffer, 1024);
        char* prime=primeString(buffer);
        strcpy(buffer, prime);
    }else { read(sockfd, buffer, 1024); }

    //odstranenie \n
    unsigned long p=0;
    while (buffer[p]!='\n') { p++; }
    if (p>strlen(buffer)) p=strlen(buffer);
    buffer[p]='\0';//



    strcpy(res,"Message from server: ");
    strcat(res, buffer);
    x=40;

    printf("\033[0;32m");   //sets text color to green
    for (int i=0; i<strlen(res); i++) {
        fputc(res[i], outputLog);   //do txt
        if (res[i]==' ' && writeWholeWord(res, i)+x+1>80) {
            printf("\n");
            y++;
            x=39;
            printf("\033[%d;%dH%c", y, x, res[i]);
        } else {
            printf("\033[%d;%dH%c", y, x, res[i]);
        }
        fflush(stdout);
        //usleep(20000);
        if (x<80) { x++; } else { x=40; printf("\n"); y++; }
    }

    fputc('\n', outputLog);
    fputc('\n', outputLog);

}



int ID(const char* id) {
    int sum=0;
    for (int i=0; i<4; i++) {
        sum+= id[i] - '0';
    }

    int digit=id[4] - '0';
    digit=digit==0 ? 9 : digit; //ak sa piata cislica rovna 0 tak prehodi na 9
    return (sum % digit);
}



int main() {
    setlocale(LC_ALL, "");
    outputLog = fopen(outputFileName, "w");
    int sockfd;
    struct sockaddr_in server_addr;



    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    //844848
    printf("Connected to server\n");

    sendGet(sockfd, "hello",0);

    sendGet(sockfd, "126771",0);

    sendGet(sockfd, "What is it?",0);


    sendGet(sockfd, "844848",0);

    printf("\n");


    sendGet(sockfd, "753422",0);
    char remChar[10];
    snprintf(remChar, sizeof(remChar), "%d", ID("126771"));
    sendGet(sockfd, remChar,0);

    sendGet(sockfd, "333222334",0);

    sendGet(sockfd, "123",55);

    sendGet(sockfd, "Mount Everest",0);

    sendGet(sockfd, "27",0);

    sendGet(sockfd, "86",0);

    sendGet(sockfd, "M.E.",0);

    sendGet(sockfd, "PRIMENUMBER", -1);

    sendGet(sockfd, "LOG.CHAT",0);

    sendGet(sockfd, "Trinity",0);

    sendGet(sockfd, "16",0);

    sendGet(sockfd, "3",0);

    //sendGet(sockfd, "BONUS",0);


    //Please disconnect, then reprogram your software to display your name  including diacritics using the function SetConsoleOutputCP(CP_UTF8).  Display messages from me one letter at a time (wait a few milliseconds after each letter).Then reconnect and after reading this message send me the code 844848.
    // Close socket
    close(sockfd);
    fclose(outputLog);
    return 0;
}
