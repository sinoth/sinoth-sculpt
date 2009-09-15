
#include <stdio.h>
#include "sinsocket.h"


int main(int argc, char *argv[] ) {

    sinsocket server, *incoming_connection;
    int result;

    //create a listening socket on port 81
    if ( server.listen(3490) ) {
        fprintf(stderr, "error on server.listen()! baaad\n");
        return 1; }

    //block until we get a connection
    incoming_connection = server.accept();
    if ( incoming_connection == NULL ) {
        fprintf(stderr,"error on server.accept()! baaad\n");
        return 1; }

    result = incoming_connection->send("hello dude", 11);

    if ( incoming_connection->send("hello dude", 11) ) {
        fprintf(stderr,"Error on send! Baad!\n");
    }


    return 0;
}


