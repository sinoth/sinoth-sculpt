
#include <stdio.h>

#include "sinsocket.h"


int main(int argc, char *argv[])
{

    sinsocket client;
    char buffer[20];
    int result;

    //to get rid of the unused variable warning
    argc = argc; argv = argv;

    //connect to the server
    if ( client.connect("localhost",3490) ) {
        fprintf(stderr,"ERROR on connect! bad!\n");
        return 1; }

    //receive data from the server
    result = client.recv(buffer,11);
    switch ( result ) {
        case -1: fprintf(stderr,"ERROR on client receive! bad!\n"); break;
        case 1:  printf("server disconnected\n"); break;
        default: printf("client: received '%s'\n",buffer); break;
    }

    return 0;
}


