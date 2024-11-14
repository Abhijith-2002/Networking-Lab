#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>

#define BUFFERSIZE 1024
#define PORT 4003
#define TOTALFRAMES 10
#define LOSSPROB 0.2

typedef struct
{
    int seqNo;
    char buffer[BUFFERSIZE];
}Frame;


int main() {
    int sockfd;
    struct sockaddr_in server_addr,client_addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    Frame dataFrame,ackFrame;
    int framesize = sizeof(Frame);

    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd,(struct sockaddr *)&server_addr,addrlen)==-1) {
        perror("bind");
    }

    int expectedSeqNo = 0;

    while(expectedSeqNo<TOTALFRAMES) {
        int valread = recvfrom(sockfd,&dataFrame,framesize,0,(struct sockaddr *)&client_addr,&addrlen);
        if(valread>0) {
            if(dataFrame.seqNo==expectedSeqNo) {
                printf("Frame-%d recieved\n",dataFrame.seqNo);
                ackFrame.seqNo = expectedSeqNo;
                sendto(sockfd,&ackFrame,framesize,0,(struct sockaddr *)&client_addr,addrlen);
                printf("ACK sent for Frame-%d",expectedSeqNo);
                expectedSeqNo++;
            }
            else if(dataFrame.seqNo>expectedSeqNo) {
                printf("Out of order Frame-%d recieved and discarded\n",dataFrame.seqNo);
                ackFrame.seqNo = expectedSeqNo-1;
                sendto(sockfd,&ackFrame,framesize,0,(struct sockaddr *)&client_addr,addrlen);
                printf("ACK resent for the last correctly recieved Frame-%d",ackFrame.seqNo);
            }
            else {
                printf("Invalid Frame recieved !");
                ackFrame.seqNo = expectedSeqNo-1;
                sendto(sockfd,&ackFrame,framesize,0,(struct sockaddr *)&client_addr,addrlen);
                printf("ACK resent for the last correctly recieved Frame-%d",ackFrame.seqNo);
            }
        }
        else {
            perror("recvfrom");
            exit(1);
        }
    }
    printf("All Frames recieved successfully !\n");
    close(sockfd);
    return 0;
}