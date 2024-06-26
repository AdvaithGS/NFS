#include <stdio.h>
#include "udp.h"

#define BUFFER_SIZE (1000)

void take_input(char ** s){
    char ch = getchar();
    int i = 0;
    while(ch != '\n' && i != BUFFER_SIZE){
        (*s)[i] = ch;
        ch = getchar();
    }
}

// client code
int main(int argc, char *argv[])
{
    struct sockaddr_in addrSnd, addrRcv;

    int sd = UDP_Open(20000);
    int rc = UDP_FillSockAddr(&addrSnd, "localhost", 10000);

    char * message = malloc(BUFFER_SIZE);
    printf("Enter Message: ");
    scanf("%[^\n]%*c",message);

    printf("client:: send message [%s]\n", message);
    rc = UDP_Write(sd, &addrSnd, message, BUFFER_SIZE);
    if (rc < 0){
        printf("client:: failed to send\n");
        exit(1);
    }

    printf("client:: wait for reply...\n");
    rc = UDP_Read(sd, &addrRcv, message, BUFFER_SIZE);
    printf("client:: got reply [size:%d contents:(%s)\n", rc, message);
    return 0;
}
