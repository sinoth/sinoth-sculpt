
/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include "sinsocket.h"

int main(void)
{


//        if (send(new_fd, "Hello, world!", 13, 0) == -1)
//            perror("send");
//        close(new_fd); // close the active connection

    sinsocket server, *incoming_connection;

    //create a listening socket on port 81
    if ( server.listen(3490) ) {
        fprintf(stderr, "error on server.listen()! baaad\n");
        return 1; }

    //block until we get a connection
    incoming_connection = server.accept();
    if ( incoming_connection == NULL ) {
        fprintf(stderr,"error on server.accept()! baaad\n");
        return 1; }


    return 0;
}
