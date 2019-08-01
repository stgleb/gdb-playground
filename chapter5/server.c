#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#define WPORT 2000
#define BUFSIZE 1000

int clientdesc;
int srvdesc;

char outputbuf[BUFSIZE];

void respond() {
    int fd;
    int nb;

    memset(outputbuf, 0, sizeof(outputbuf));
    system("w > tmp.client");
    fd = open("tmp.client", O_RDONLY);
    nb = read(fd, outputbuf, BUFSIZE);
    write(clientdesc, outputbuf, nb);
    unlink("tmp.client");
    close(clientdesc);
}

int main() {
    struct sockaddr_in bind_info;

    // Create socket to be used for serving
    srvdesc = socket(AF_INET, SOCK_STREAM, 0);
    bind_info.sin_family = AF_INET;
    bind_info.sin_port = WPORT;
    bind_info.sin_addr.s_addr = INADDR_ANY;
    bind(srvdesc, (struct sockaddr*)&bind_info, sizeof(bind));

    printf("listen to %d\n", WPORT);
    listen(srvdesc, 5);

    while(1){
        clientdesc = accept(srvdesc, 0, 0);
        printf("get connection");
        respond();
    }
}
