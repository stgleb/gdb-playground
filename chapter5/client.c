#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

#define WPORT 2000
#define BUFFSIZE 1000

int main(int agrc, char** argv) {
    int sd;
    int msg_size;

    struct sockaddr_in addr;
    struct hostent *hostptr;
    char buf[BUFFSIZE];

    sd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port =  WPORT;
    hostptr = gethostbyname(argv[1]);
    memcpy(&addr.sin_addr.s_addr, hostptr->h_addr_list[0], hostptr->h_length);

    connect(sd, (struct sockaddr* )&addr, sizeof(addr));

    msg_size = read(sd, buf, BUFFSIZE);

    if(msg_size > 0) {
        write(1, buf, msg_size);
    }
    printf("\n");
    return 0;
}