
#include "scene.h"

bool scene::retrieveServerList() {

    sinsocket client_socket;
    unsigned char list_request = 0x28;
    unsigned char num_of_servers;


    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n"); return 1; }

    //ask for a server list (0x28)
    client_socket.send( &list_request, 1 );

    //get number of servers being transferred
    client_socket.recv( &num_of_servers, 1 );

    return 0;
}


