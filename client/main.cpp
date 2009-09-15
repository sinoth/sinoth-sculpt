/*
** client.c -- a stream socket client demo
*/

#include <stdio.h>

#include "sinsocket.h"



int main(int argc, char *argv[])
{

    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("client: received '%s'\n",buf);

    close(sockfd);

#ifdef _WIN32_WINNT
 WSACleanup();
#endif

    return 0;
}
