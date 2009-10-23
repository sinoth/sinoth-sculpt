
#include <stdio.h>
#include <string.h>
#include "sinsocket.h"


void send_server_list( sinsocket * );


int main(int, char **) {

    sinsocket server, *incoming_connection;
    unsigned char request;

    //create a listening socket on port 81
    if ( server.listen(35610) ) {
        fprintf(stderr, "error on server.listen()! baaad\n");
        return 1; }

    while (1) {

        //block until we get a connection
        incoming_connection = server.accept();
        if ( incoming_connection == NULL ) {
            fprintf(stderr,"error on server.accept()! baaad\n");
            return 1; }

        //see what the client wants us to do
        incoming_connection->recv(&request, 1);
        printf("Received request for 0x%x\n", request);

        switch ( request ) {
            case 0x28: //send a server list
                send_server_list(incoming_connection);
                break;
        }

        incoming_connection->disconnect();

    }

    return 0;
}




void send_server_list( sinsocket *insocket ) {

    //server info
    unsigned char server_name_length;
    int num_of_servers = 1;
    char server1_name[] = "Server Numero Uno";
    int server1_total_pieces = 125;
    int server1_pieces_left = 30;
    unsigned char current_player_pieces = 4;
    unsigned char total_player_pieces = 10;

    //send number of servers
    insocket->send( &num_of_servers, 1 );

    for ( int i=0; i < num_of_servers; ++i ) {
        //send length of server name
        server_name_length = strlen(server1_name) + 1;
        insocket->send( &server_name_length, 1 );

        //send server name
        insocket->send(server1_name, server_name_length);

        //send info about server
        insocket->send(&server1_total_pieces, 4);
        insocket->send(&server1_pieces_left, 4);
        insocket->send(&total_player_pieces, 1);
        insocket->send(&current_player_pieces, 1);
    }


}



/*
    result = incoming_connection->send("hello dude", 11);
    if ( incoming_connection->send("hello dude", 11) ) {
        fprintf(stderr,"Error on send! Baad!\n");
    }
*/
