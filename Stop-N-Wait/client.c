#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/socket.h>

#define PORT 4001
#define IP "127.0.0.1"
#define WINDOWSIZE 4
#define BUFFERSIZE 1024
#define TOTALFRAMES 10
#define TIMEOUT 2

typedef struct 
{
    int seqNo;
    char buffer[BUFFERSIZE];
}Frame;

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    Frame dataFrame,ackFrame;
    int framesize = sizeof(Frame);

    if((sockfd=socket(AF_INET,SOCK_DGRAM,0))==-1) {
        perror("socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    struct timeval tv;
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    if(setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv))<0) {
        perror("setsockopt");
        exit(1);
    }

    int base = 0;
    int nextSeqNo = 0;
    Frame buffer[TOTALFRAMES];

    while(nextSeqNo<TOTALFRAMES) {
        dataFrame.seqNo = nextSeqNo;
        buffer[nextSeqNo] = dataFrame;
        sendto(sockfd,&dataFrame,framesize,0,(struct sockaddr *)&server_addr,addrlen);
        printf("Frame-%d sent\n",dataFrame.seqNo);
        int valread = recvfrom(sockfd,&ackFrame,framesize,0,(struct sockaddr *)&server_addr,&addrlen);
        if(valread>0) {
            if(ackFrame.seqNo==nextSeqNo) {
                printf("ACK recieved for Frame-%d\n",ackFrame.seqNo);
                nextSeqNo++;
            }
            else {
                printf("Invalid ACK receieved ! Discarded \n");
            }
        }
        else {
            printf("Timeout occured ! Retransmitting Frame-%d",nextSeqNo);
            dataFrame.seqNo = nextSeqNo;
            sendto(sockfd,&dataFrame,framesize,0,(struct sockaddr *)&server_addr,addrlen);
            printf("Frame-%d resent\n",buffer[nextSeqNo].seqNo);
        }

    }
    printf("All frames sent and acknowledged !\n");

}