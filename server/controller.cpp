
#include <stdio.h>
#include "sinsocket.h"


int main( int, char** ) {

    sinsocket client_socket;
    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n"); return 1; }

    //terminate the server
    unsigned char terminate_request = 0x55;
    client_socket.send( &terminate_request, 1 );

    //need to fix sinsocket so this isn't needed!
    //scanf("%c",&terminate_request);

    client_socket.beginDisconnect();

    return 0;
}
