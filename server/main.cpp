
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <sinsocket.h>
#include <iostream>

#include "ssqls.h"
#include "messages.txt.pb.h"
#include "passwords.h"

#define MAJOR_VERSION 1
#define MINOR_VERSION 0
bool check_version( uint8_t &in ) {
    if ( (in>>4) == MAJOR_VERSION && (in&15) == MINOR_VERSION )
        return false;
    else {
        in = MINOR_VERSION + (MAJOR_VERSION<<4);
        return true; }
}
uint8_t version_from_char( const char *in_char ) {
    uint8_t major, minor;
    char temp_version[3]; temp_version[2] = '\0';
    temp_version[0] = in_char[0]; temp_version[1] = in_char[1];
    major = strtol(temp_version, NULL, 10);
    temp_version[0] = in_char[3]; temp_version[1] = in_char[4];
    minor = strtol(temp_version, NULL, 10);
    return ( (major<<4)|minor );
}


using std::cout;
using std::cerr;

//prototypes
void send_server_list( sinsocket * );
void send_current_map( sinsocket * );
uint8_t check_current_version( sinsocket * );
void send_piece( sinsocket * );
void receive_piece( sinsocket * );


///////////////////////////////////////////////////////////////////////////////
//
int main(int, char **) {

  GOOGLE_PROTOBUF_VERIFY_VERSION;

  #ifdef PTW32_STATIC_LIB
  pthread_win32_process_attach_np();
  #endif

  try {

    sinsocket server, *incoming_connection;
    char *incoming_ip;

    unsigned char request;
    bool do_quit = false;

    //create a listening socket on port 81
    if ( server.listen(35610) ) {
        cerr << "error on server.listen()! baaad\n";
        return 1; }

    while (!do_quit) {

        //block until we get a connection
        incoming_ip = (char*)malloc(IP_LENGTH);
        incoming_connection = server.accept(incoming_ip);
        if ( incoming_connection == NULL ) {
            fprintf(stderr,"error on server.accept()! baaad\n");
            return 1; }

        incoming_connection->setUserData(incoming_ip);

        //see what the client wants us to do
        incoming_connection->recvRaw(&request, 1);
        printf("Received request for 0x%x\n", request);

        switch ( request ) {
            case 0x28: //server list request
                send_server_list(incoming_connection);
                break;
            case 0x29: //current map request
                send_current_map(incoming_connection);
                break;
            case 0x43: //request to claim a piece
                send_piece(incoming_connection);
                break;
            case 0x74:
                receive_piece(incoming_connection);
                break;
            case 0x55: //terminate the server
                do_quit = true;
                break;
            case 0x71: //query for server info
                break;
        }

        incoming_connection->endDisconnect();
        delete incoming_connection;

    }

//////////
  } catch (const mysqlpp::Exception& er) {
    // Catch-all for any other MySQL++ exceptions
    std::cerr << "Error: " << er.what() << std::endl;
    return NULL;
  }
//////////

  #ifdef PTW32_STATIC_LIB
  pthread_win32_thread_detach_np();
  pthread_win32_process_detach_np();
  #endif

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
//
uint8_t check_current_version( sinsocket *insocket ) {

    //fetch the most recent version
    mysqlpp::Connection conn;
    //open the database (db, server, user, pass)
    if ( !conn.connect("updater", "localhost", UPDATER_USER, UPDATER_PASSWORD) ) {
        cerr << "DB connection failed (updater): " << conn.error() << "\n";
        return 255; }

    mysqlpp::Query query = conn.query();
    mysqlpp::StoreQueryResult res;

    char received_version[6];
    char current_version[6];
    uint8_t received_version_byte, current_version_byte;
    if ( insocket->recvRaw(&received_version_byte, 1) ) return 255;
    sprintf(received_version, "%02d.%02d",(received_version_byte>>4),(received_version_byte&15));
    res = query.store("select name,version from current_versions where name = 'sculpt' order by stamp desc");
    strcpy(current_version, res[0][1]);
    current_version_byte = version_from_char(res[0][1].c_str());
    if ( insocket->sendRaw(&current_version_byte, 1) ) return 255;
    if ( current_version_byte != received_version_byte ) {
        //version is NOT ok! return current version
        return current_version_byte;
    }

    //version is fine
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
void send_current_map( sinsocket *insocket ) {

    //first make sure we're at the current version
    uint8_t version_result;
    if ( (version_result = check_current_version(insocket) ) ) {
        //version is bad, so bail
        printf("Version is bad! (%02d.%02d)\n", version_result>>4, version_result&15);
        return; }

    mysqlpp::Connection conn;
    //open the database (db, server, user, pass)
    if ( !conn.connect("sculpt", "localhost", SCULPT_USER, SCULPT_PASSWORD) ) {
        cerr << "DB connection failed (sculpt): " << conn.error() << "\n";
        return; }

    mysqlpp::Query query = conn.query();
    mysqlpp::StoreQueryResult res;

    //fetch the active map
    query << "SELECT table_name,description,pieces_total,pieces_per_user,recharge_rate FROM server_maps WHERE completed_timestamp IS NULL ORDER BY added_timestamp ASC LIMIT 1";

    get_server_maps::table("server_maps");
    std::vector<get_server_maps> the_current_map;
    query.storein(the_current_map);

    sculpt::CurrentMap cmap;
    cmap.set_name( the_current_map[0].description );

    //calculate how many have actually been completed
    query << "SELECT COUNT(*) FROM " << the_current_map[0].table_name << " WHERE piece_order >= 0 AND checkin IS NULL AND (checkout IS NULL OR checkout < TIMESTAMPADD(HOUR,-1,CURRENT_TIMESTAMP))";
    res = query.store();
    int total_avail = res[0][0];

    //convert completed to a string
    char temp_completed[20];
    sprintf(temp_completed,"%d / %d", the_current_map[0].pieces_total-total_avail, the_current_map[0].pieces_total );
    cmap.set_completed_pieces( temp_completed );

    //calculate available to this user
    int pieces_per_user = the_current_map[0].pieces_per_user;
    //int recharge_rate = the_current_map[0].recharge_rate;
    query << "SELECT COUNT(*) FROM " << the_current_map[0].table_name << " WHERE ip = \"" << (char*)insocket->getUserData() << "\" AND checkout < TIMESTAMPADD(HOUR,CURRENT_TIMESTAMP,-" << pieces_per_user << ")";
    res = query.store();
    int actual_available = pieces_per_user - res[0][0];
    if ( actual_available > total_avail ) actual_available = total_avail;
    if ( total_avail == 0 ) actual_available = 0;
    cmap.set_available(actual_available);

    //send over the message
    int size_of_map = cmap.ByteSize();
    packet_data *cmap_packet = new packet_data(malloc(size_of_map),size_of_map);
    cmap.SerializeToArray(cmap_packet->data, size_of_map);
    cmap_packet->compress();
    insocket->sendPacket(cmap_packet);

}

///////////////////////////////////////////////////////////////////////////////
//
void send_server_list( sinsocket * ) {

}

///////////////////////////////////////////////////////////////////////////////
//
void send_piece( sinsocket *insocket ) {

    //first make sure we are at the current version
    uint8_t version_result;
    if ( (version_result = check_current_version(insocket) ) ) {
        //version is bad, so bail
        printf("Version is bad! (%02d.%02d)\n", version_result>>4, version_result&15);
        return; }

    mysqlpp::Connection conn;
    //open the database (db, server, user, pass)
    if ( !conn.connect("sculpt", "localhost", SCULPT_USER, SCULPT_PASSWORD) ) {
        cerr << "DB connection failed (sculpt): " << conn.error() << "\n";
        return; }

    mysqlpp::Query query = conn.query();
    mysqlpp::StoreQueryResult res;
    mysqlpp::SimpleResult simple_res;

    //fetch the active map
    get_server_maps::table("server_maps");
    std::vector<get_server_maps> cur_map_vec;
    get_server_maps *cur_map;
    query << "SELECT map_id,table_name,pieces_per_user,x_size,y_size,z_size,piece_x_size,piece_y_size,piece_z_size FROM server_maps WHERE completed_timestamp IS NULL ORDER BY added_timestamp ASC LIMIT 1";
    query.storein(cur_map_vec);
    cur_map = &cur_map_vec[0];

    //calculate how many have actually been completed
    query << "SELECT COUNT(*) FROM " << cur_map->table_name << " WHERE piece_order >= 0 AND checkin IS NULL AND (checkout IS NULL OR checkout < TIMESTAMPADD(HOUR,-1,CURRENT_TIMESTAMP))";
    res = query.store();
    int total_avail = res[0][0];

    //calculate available to this user
    query << "SELECT COUNT(*) FROM " << cur_map->table_name << " WHERE ip = \"" << (char*)insocket->getUserData() << "\" AND checkout < TIMESTAMPADD(HOUR,CURRENT_TIMESTAMP,-" << cur_map->pieces_per_user << ")";
    res = query.store();
    int actual_available = cur_map->pieces_per_user - res[0][0];
    if ( actual_available > total_avail ) actual_available = total_avail;
    if ( total_avail == 0 ) actual_available = 0;

    if ( actual_available == 0 ) {
        //no dice! tell them NOPE
        uint8_t nope = 0;
        insocket->sendRaw(&nope,1);
        return; }

    //tell them we're grabbing them a piece!
    uint8_t yay = 1;
    insocket->sendRaw(&yay,1);

    //grab the username
    uint32_t username_size;
    char username[25];
    insocket->recvRaw(&username_size, 4);
    insocket->recvRaw(username, username_size);

    //find the next available piece and claim it immediately
    //table probably needs to be locked so we don't accidentally dish out a piece twice
    query << "LOCK TABLES " << cur_map->table_name << " WRITE";
    query.execute();
    query << "SELECT piece_id, piece_hash FROM " << cur_map->table_name << " WHERE piece_order >= 0 AND (checkout IS NULL OR checkout < TIMESTAMPADD(HOUR,-1,CURRENT_TIMESTAMP)) ORDER BY piece_order ASC LIMIT 1";
    res = query.store();
    int piece_id = res[0][0];
    std::string hash(res[0][1]);
    query << "UPDATE " << cur_map->table_name << " SET checkout = CURRENT_TIMESTAMP, ip = \"" << (char*)insocket->getUserData() << "\", username = \"" << username << "\" WHERE piece_id = " << piece_id;
    simple_res = query.execute();
    query << "UNLOCK TABLES";
    query.execute();

    //ok, fun time.  retrieve the surrounding pieces
    std::vector<int> pieces_to_grab;
    for (int ty=-1; ty <= 1; ty++)
     for (int tz=-1; tz <= 1; tz++)
      for (int tx=-1; tx <= 1; tx++)
        if ( tx||ty||tz )
          pieces_to_grab.push_back(piece_id + tx + tz*(cur_map->x_size+2) + ty*(cur_map->x_size+2)*(cur_map->z_size+2));

    //cout << "Grabbing pieces:\n";
    //for (unsigned int i=0; i<pieces_to_grab.size(); ++i)
    //    cout << pieces_to_grab[i] << " ";
    //cout << "\n";

    query << "SELECT data FROM " << cur_map->table_name << " WHERE piece_id in (";
    query << pieces_to_grab[0];
    for (unsigned int i=1; i<pieces_to_grab.size(); ++i)
        query << "," << pieces_to_grab[i];
    query << ")";
    res = query.store();

    std::vector<uint8_t> chunk_vector;

    for (unsigned int i=0; i < res.size(); ++i) {
        if ( res[i][0] == mysqlpp::null ) {
            for (int j=0; j<cur_map->piece_x_size*cur_map->piece_y_size*cur_map->piece_z_size; ++j)
                chunk_vector.push_back(0);
        } else {
            for (int j=0; j<cur_map->piece_x_size*cur_map->piece_y_size*cur_map->piece_z_size; ++j)
                chunk_vector.push_back( (uint8_t)(((char*)&res[i][0])[j]) );
        }
    }

    //printf("Chunk vector size (%dx%dx%d): %d\n", cur_map->piece_x_size,cur_map->piece_y_size,cur_map->piece_z_size, chunk_vector.size());

    uint8_t *bit_data;
    int bit_data_size;
    sinbits::vector_to_bits(chunk_vector, &bit_data, &bit_data_size);

    sculpt::ServerPiece sending_piece;
    sending_piece.set_map_id(cur_map->map_id);
    sending_piece.set_piece_id(piece_id);
    sending_piece.set_hash(hash);
    sending_piece.set_size_x(cur_map->piece_x_size);
    sending_piece.set_size_y(cur_map->piece_y_size);
    sending_piece.set_size_z(cur_map->piece_z_size);
    sending_piece.set_data(bit_data, bit_data_size);

    int size_of_piece = sending_piece.ByteSize();
    packet_data *piece_packet = new packet_data(malloc(size_of_piece),size_of_piece);
    sending_piece.SerializeToArray(piece_packet->data, size_of_piece);
    piece_packet->compress();
    insocket->sendPacket(piece_packet);

}


void receive_piece( sinsocket *insocket ) {


    //first make sure we are at the current version
    uint8_t version_result;
    if ( (version_result = check_current_version(insocket) ) ) {
        //version is bad, so bail
        printf("Version is bad! (%02d.%02d)\n", version_result>>4, version_result&15);
        return; }

    mysqlpp::Connection conn;
    //open the database (db, server, user, pass)
    if ( !conn.connect("sculpt", "localhost", SCULPT_USER, SCULPT_PASSWORD) ) {
        cerr << "DB connection failed (sculpt): " << conn.error() << "\n";
        return; }

    mysqlpp::Query query = conn.query();
    mysqlpp::StoreQueryResult res;
    mysqlpp::SimpleResult simple_res;

    //get the piece
    packet_data *piece_packet;
    insocket->recvPacket(piece_packet);
    sculpt::SubmitPiece the_piece;
    the_piece.ParseFromArray( piece_packet->data, piece_packet->size() );

    //fetch the map they supplied
    get_server_maps::table("server_maps");
    std::vector<get_server_maps> cur_map_vec;
    get_server_maps *cur_map;
    query << "SELECT table_name,completed_timestamp FROM server_maps WHERE map_id = " << the_piece.map_id() << " LIMIT 1";
    query.storein(cur_map_vec);
    cur_map = &cur_map_vec[0];

    if ( !cur_map_vec.size() ) {
        //invalid, must have been a bad ID
        uint8_t bad_id = 0x01;
        insocket->sendRaw(&bad_id, 1);
        return;
    }

    if ( cur_map->completed_timestamp != mysqlpp::null ) {
        //map has been closed
        uint8_t map_closed = 0x02;
        insocket->sendRaw(&map_closed, 1);
        return;
    }

    //check that the piece is still submittable
    query << "SELECT piece_hash,username,checkin FROM " << cur_map->table_name << " WHERE piece_id = " << the_piece.piece_id() << " LIMIT 1";
    res = query.store();

    xxx

    //tell them it was a success
    uint8_t success = 0x00;
    insocket->sendRaw(&success, 1);

}

