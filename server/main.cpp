
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#include "sinsocket.h"
#include "sinsql.h"


//global database stuff
sqlite3 *db;
char temp_query[200];


//prototypes
void send_server_list( sinsocket * );
void send_piece( sinsocket * );
void construct_blob( unsigned char*, int,int,int,int,int,int,int,const char* );


///////////////////////////////////////////////////////////////////////////////
//
int main(int, char **) {

    sinsocket server, *incoming_connection;
    unsigned char request;

//////////
  try {
    //open the database
    sinsql_open_db("sculpt-db", db);
    printf("Opened database.\n");

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
            case 0x43: //request to claim a piece
                send_piece(incoming_connection);
                break;
            case 0x55: //terminate the server
                break;
            case 0x71: //query for server info
                break;
        }

        incoming_connection->disconnect();

    }

//////////
  } catch ( int error ) {
    if ( db != NULL ) printf("Last SQL error: %s\n", sqlite3_errmsg(db));
  }
//////////

    sqlite3_close(db);
    return 0;
}



///////////////////////////////////////////////////////////////////////////////
//
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

  try {

    //retrieve number of servers
    sinsql_get_int(db, "select count(*) from server_maps;", num_of_servers);

    //send number of servers
    insocket->send( &num_of_servers, 1 );
    printf("Number of servers: %d\n", num_of_servers);

    //collect and send data for each server
    sinsql_stmt_prep(db, "select * from server_maps;", list_statement);
    for ( int i=0; i < num_of_servers; ++i ) {

        sinsql_stmt_step(list_statement);

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

    sinsql_stmt_fin(list_statement);

//////////
  } catch (int error) {
      throw;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
void send_piece( sinsocket *insocket ) {

    //sqlite stuff
    sqlite3_stmt *sql_statement;

    unsigned char requested_id;
    unsigned char allowed;
    int pieces_per_user;
    int distribution;
    char table_name[50];
    char temp_hash[17];
    int piece_x_size, piece_y_size, piece_z_size;
    int map_x_size, map_y_size, map_z_size;
    int piece_id;
    unsigned char *data_to_send;


  try {

    //find requested table make sure it is valid
    insocket->recv(&requested_id, 1);
    sprintf(temp_query, "select null from server_maps where id = %d;", requested_id);
    if ( !sinsql_existence(db, temp_query) ) {
        //this server is not found, send back a negatory
        allowed = false; insocket->send(&allowed, 1);
        return;
    }

    //fetch actual info from table
    sprintf(temp_query, "select * from server_maps where id = %d;", requested_id);
    sinsql_stmt_prep(db,temp_query,sql_statement);
    sinsql_stmt_step(sql_statement);

    //get the table info
    strcpy(table_name,(const char*)sqlite3_column_text(sql_statement, 1));
    distribution    = sqlite3_column_int(sql_statement, 13);
    pieces_per_user = sqlite3_column_int(sql_statement,  9);
    piece_x_size    = sqlite3_column_int(sql_statement,  6);
    piece_y_size    = sqlite3_column_int(sql_statement,  7);
    piece_z_size    = sqlite3_column_int(sql_statement,  8);
    map_x_size      = sqlite3_column_int(sql_statement,  3);
    map_y_size      = sqlite3_column_int(sql_statement,  4);
    map_z_size      = sqlite3_column_int(sql_statement,  5);

    sinsql_stmt_fin(sql_statement);

    //see if this IP can get a piece from table
    ///for now always say true
    //sprintf(temp_query, "select name from server_maps where id = %d;", requested_id);
    //rc = sqlite3_prepare_v2(db, temp_query, -1, &sql_statement, NULL);
    //    if(rc!=SQLITE_OK){fprintf(stderr, "SQL error (prepare check avail): %s\n", sqlite3_errmsg(db) ); return; }
    allowed = true;
    insocket->send(&allowed, 1);


    //pick a piece to send based on distribution method
    switch ( distribution ) {
        case 0: //purely random
            sprintf(temp_query, "select id,hash from %s where checkout is null order by random() limit 1;",table_name);
            break;
        default: break;
    }

    //retrieve the piece hash
    sinsql_stmt_prep(db, temp_query, sql_statement);
    sinsql_stmt_step(sql_statement);
      piece_id = sqlite3_column_int(sql_statement,  0);
      strcpy(temp_hash, (const char*)sqlite3_column_text(sql_statement,1));
    sinsql_stmt_fin(sql_statement);

    //send the hash and piece size
    insocket->send(temp_hash, 17);
    insocket->send(&piece_x_size, 1);
    insocket->send(&piece_y_size, 1);
    insocket->send(&piece_z_size, 1);


    //how much storage do we need?
    int blob_size = piece_x_size*piece_y_size*piece_z_size*26;
    data_to_send = new unsigned char[blob_size];

    //construct blob of data to send over the wire
    construct_blob(data_to_send, piece_id, piece_x_size, piece_y_size, piece_z_size, map_x_size, map_y_size, map_z_size, table_name);

    insocket->send(data_to_send, blob_size);

    delete[] data_to_send;

//////////
  } catch (int inerror) {
    throw;
  }
}



void construct_blob( unsigned char *data_in, int id, int p_x, int p_y, int p_z, int m_x, int m_y, int m_z, const char *table_name ) {

    int data_counter = 0;
    int check_id;
    void *temp_blob;
    int temp_blob_size;

  try {

    for (int i=-1; i <= 1; ++i )
        for (int j=-1; j <= 1; ++j)
            for (int k=-1; k <= 1; ++k) {

                check_id = id + (i) + (j*m_x) + (k*m_x*m_y);

                if ( check_id < 1 || check_id > m_x*m_y*m_z ) {
                    //out of bounds, so send all 0's
                    for ( int ii=0; ii<p_x*p_y*p_z; ++ii )
                        data_in[data_counter++] = false;
                } else {
                    //valid id, check if it is empty
                    sprintf(temp_query, "select null from %s where id = %d and checkout is null;", table_name, check_id);
                    if ( sinsql_existence(db, temp_query) ) {
                        //empty, fill with 0
                        for ( int ii=0; ii<p_x*p_y*p_z; ++ii )
                            data_in[data_counter++] = false;
                    } else {
                        //not empty! grab the blob
                        sprintf(temp_query, "select data from %s where id = %d;", table_name, check_id);
                        sinsql_get_blob(db, temp_query, temp_blob, temp_blob_size);
                        //loop through the blob, adding to data
                        for ( int ii=0; ii<p_x*p_y*p_z; ++ii )
                            data_in[data_counter++] = ((unsigned char*)temp_blob)[ii];
                        //free the blob
                        free(temp_blob);
                    }

                }
            }


//////////
  } catch (int error) {
    throw;
  }
}





/*
    result = incoming_connection->send("hello dude", 11);
    if ( incoming_connection->send("hello dude", 11) ) {
        fprintf(stderr,"Error on send! Baad!\n");
    }
*/
/*
void set_bit(unsigned char*in, int bit, bool value) {
    if ( value ) //setting true, so use OR
        in[bit/8] |= (1 << (bit - (bit/8)*8));
    else //setting false, so use AND
        in[bit/8] &= (1 << (bit - (bit/8)*8));
}
*/
