#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define BUCKETCAPACITY 10
#define LEAKRATE 1

int bucket = 0;

void fillBucket(int incomingPackets) {
    if(bucket+incomingPackets<=BUCKETCAPACITY) {
        bucket+=incomingPackets;
        printf("Added %d Packets to Bucket .\nCurrent Bucket Size : %d\n",incomingPackets,bucket);
    }
    else {
        int overflow = (bucket+incomingPackets)-BUCKETCAPACITY;
        bucket = BUCKETCAPACITY;
        printf("Bucket overflow !\n%d Packets discarded !\nCurrent Bucket Size : %d",overflow,bucket);
    }
}

void leakBucket() {
    if(bucket>0) {
        bucket -= LEAKRATE;
        printf("\nLeaked one packet. Current Bucket Size : %d",bucket);
    }
}

int main() {
    int incomingPackets;

    while(1) {
        printf("\nEnter the number of Incoming Packets : ");
        scanf("%d",&incomingPackets);
        if(incomingPackets<0) {
            break;
        }
        fillBucket(incomingPackets);

        sleep(1);
        leakBucket();
    }

    return 0;
}