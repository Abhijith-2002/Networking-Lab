#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/socket.h>

#define PORT 4003
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

    while(base<TOTALFRAMES) {
        while(nextSeqNo<base+WINDOWSIZE && nextSeqNo<TOTALFRAMES) {
            dataFrame.seqNo = nextSeqNo;
            buffer[nextSeqNo] = dataFrame;
            sendto(sockfd,&dataFrame,framesize,0,(struct sockaddr *)&server_addr,addrlen);
            printf("Frame-%d sent\n",nextSeqNo);
            nextSeqNo++;
        }

        int valread = recvfrom(sockfd,&ackFrame,framesize,0,(struct sockaddr *)&server_addr,&addrlen);
        if(valread>0) {
            if(ackFrame.seqNo==base) {
                printf("ACK recieved for Frame-%d\n",ackFrame.seqNo);
                base++;
                printf("Sliding Window to Frame-%d\n",base);
            }
        }
        else if(valread==-1) {
            printf("Timeout ! Resending Frames from %d to %d\n",base,nextSeqNo-1);
            for(int i=base;i<nextSeqNo;i++) {
                sendto(sockfd,&buffer[i],framesize,0,(struct sockaddr *)&server_addr,addrlen);
                printf("Frame-%d resent\n",i);
            }
        }
    }
    printf("All frames sent and acknowledged !\n");
}