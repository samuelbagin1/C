#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define SERVER_IP "147.175.115.34"  // Change this to the IP address of your server
#define SERVER_PORT 777       // Change this to the port your server is listening on

int y=5;

void sendGet(int sockfd, char *message, int decrypt) {
    char buffer[1024] = {0};
    char* mess;
    char res[2056];

    // Send message to server
    send(sockfd, message, strlen(message), 0);
    strcpy(res,"Message sent to server: ");
    strcat(res, message);
    int x=1;
    for (int i=0; i<strlen(res); i++) {
        printf("\033[%d;%dH%c", y, x, res[i]);
        fflush(stdout);
        //usleep(20000);
        if (x<40) { x++; } else { x=1; printf("\n"); y++; }
    }



    // Receive response from server
    if (decrypt!=0) {
        read(sockfd, buffer, 148);
        for (int i = 0; i<148; i++) {
            buffer[i]^=decrypt;
        }
    } else { read(sockfd, buffer, 1024); }
    strcpy(res,"Message from server: ");
    strcat(res, buffer);
    x=40;
    for (int i=0; i<strlen(res); i++) {
        printf("\033[%d;%dH%c", y, x, res[i]);
        fflush(stdout);
        //usleep(20000);
        if (x<80) { x++; } else { x=40; printf("\n"); y++;}
    }

    y++;
}



int ID(char* id) {
    int sum=0;
    for (int i=0; i<4; i++) {
        sum+= id[i] - '0';
    }

    int digit=id[4] - '0';
    return (sum % digit);
}



int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};
    const char *message = "Hello from client";

    printf("\033[0;32m");   //sets text color to green

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

    sendGet(sockfd, "ME",0);


    //Please disconnect, then reprogram your software to display your name  including diacritics using the function SetConsoleOutputCP(CP_UTF8).  Display messages from me one letter at a time (wait a few milliseconds after each letter).Then reconnect and after reading this message send me the code 844848.
    // Close socket
    close(sockfd);
    return 0;
}
