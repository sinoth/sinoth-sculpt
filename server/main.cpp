
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "sinsocket.h"

//global database stuff
int rc;
sqlite3 *db;

//prototypes
void send_server_list( sinsocket * );


///////////////////////////////////////////////////////////////////////////////
//
int main(int, char **) {

    sinsocket server, *incoming_connection;
    unsigned char request;

    //open the database
    rc = sqlite3_open("sculpt-db", &db);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db); return true; }
    printf("Opened database successfully.\n");

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


    sqlite3_close(db);
    return 0;
}




void send_server_list( sinsocket *insocket ) {

    //sqlite stuff
    sqlite3_stmt *list_statement;

    //server info
    unsigned char server_id;
    char server_name[100];
    unsigned char server_name_length;
    int num_of_servers;
    int server_total_pieces;
    int server_pieces_left;
    unsigned char current_player_pieces;
    unsigned char total_player_pieces;

    //retrieve number of servers
    rc = sqlite3_prepare_v2(db, "select count(*) from server_maps;", -1, &list_statement, NULL);
        if(rc!=SQLITE_OK){fprintf(stderr, "SQL error (prepare count): %s\n", sqlite3_errmsg(db) ); return; }
    rc = sqlite3_step(list_statement);
        if(rc!=SQLITE_ROW){fprintf(stderr, "SQL error (step count): %s\n", sqlite3_errmsg(db) ); return; }
    num_of_servers = sqlite3_column_int(list_statement, 0);
    rc = sqlite3_finalize(list_statement);
        if(rc!=SQLITE_OK){fprintf(stderr, "SQL error (finalize count): %s\n", sqlite3_errmsg(db) ); return; }

    //send number of servers
    insocket->send( &num_of_servers, 1 );
    printf("Number of servers: %d\n", num_of_servers);

    rc = sqlite3_prepare_v2(db, "select * from server_maps;", -1, &list_statement, NULL);
        if(rc!=SQLITE_OK){fprintf(stderr, "SQL error (prepare loop): %s\n", sqlite3_errmsg(db) ); return; }

    //collect and send data for each server
    for ( int i=0; i < num_of_servers; ++i ) {

        rc = sqlite3_step(list_statement);
            if(rc!=SQLITE_ROW){fprintf(stderr, "SQL error (step loop): %s\n", sqlite3_errmsg(db) ); return; }

        server_id = sqlite3_column_int(list_statement, 0);
        strcpy(server_name, (const char*)sqlite3_column_text(list_statement,2));
        server_total_pieces = sqlite3_column_int(list_statement, 11);
        server_pieces_left = sqlite3_column_int(list_statement, 12);
        total_player_pieces = sqlite3_column_int(list_statement, 9);
        ///needs fixing
        current_player_pieces = sqlite3_column_int(list_statement, 9);

        //send ID of the server
        insocket->send( &server_id, 1 );

        //send length of server name
        server_name_length = strlen(server_name) + 1;
        insocket->send( &server_name_length, 1 );

        //send server name
        insocket->send(server_name, server_name_length);

        //send info about server
        insocket->send(&server_total_pieces, 4);
        insocket->send(&server_pieces_left, 4);
        insocket->send(&total_player_pieces, 1);
        insocket->send(&current_player_pieces, 1);

        printf("Sent %d [%d:%s] %d %d %d %d\n", server_id, server_name_length, server_name, server_total_pieces, server_pieces_left, total_player_pieces, current_player_pieces);
    }

    rc = sqlite3_finalize(list_statement);
        if(rc!=SQLITE_OK){fprintf(stderr, "SQL error (prepare loop): %s\n", sqlite3_errmsg(db) ); return; }


}



/*
    result = incoming_connection->send("hello dude", 11);
    if ( incoming_connection->send("hello dude", 11) ) {
        fprintf(stderr,"Error on send! Baad!\n");
    }
*/
