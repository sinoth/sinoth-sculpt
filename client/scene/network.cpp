
#include "scene.h"
#include "messages.txt.pb.h"

bool scene::retrieveCurrentMap() {

    sinsocket client_socket;
    uint8_t currentmap_request = 0x29;
    char temp_label_text[100];

    ui_label *temp_label;
    temp_label= (ui_label*)mainGui.getWidget("cmap_name");
    temp_label->my_font.setText("(connecting to server...)");
    temp_label->my_font.cook();
    render();

    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n");
        //should do some error dialog here
        ui_label *temp_label;
        temp_label= (ui_label*)mainGui.getWidget("cmap_name");
        temp_label->my_font.setText("(ERROR: cannot connect to server)");
        temp_label->my_font.cook();
        return 1; }

    //ask for current map info
    if ( client_socket.sendRaw( &currentmap_request, 1 ) ) return 1;

    //make sure our version is okay
    uint8_t their_version, my_version = (VERSION_MAJOR<<4) | VERSION_MINOR;;
    if ( client_socket.sendRaw(&my_version, 1) ) return 1;
    if ( client_socket.recvRaw(&their_version, 1) ) return 1;

    if ( their_version != my_version ) {
        printf("ERROR: Versions do not match, please update.\n");
        //should display a dialog about restarting/updating here, or even initiate an update
        client_socket.beginDisconnect();
        return 1;
    }

    //grab the protobuffer object
    packet_data *map_packet;
    if ( client_socket.recvPacket(map_packet, true) ) return 1;
    sculpt::CurrentMap cmap;
    cmap.ParseFromArray( map_packet->data, map_packet->size() );

    client_socket.beginDisconnect();

    //now update the dialog with relevant data
    temp_label= (ui_label*)mainGui.getWidget("cmap_name");
    temp_label->my_font.setText(cmap.name().c_str());
    temp_label->my_font.cook();

    temp_label= (ui_label*)mainGui.getWidget("cmap_complete");
    temp_label->my_font.setText(cmap.completed_pieces().c_str());
    temp_label->my_font.cook();

    temp_label= (ui_label*)mainGui.getWidget("cmap_available");
    sprintf(temp_label_text, "%d", cmap.available() );
    temp_label->my_font.setText(temp_label_text);
    temp_label->my_font.cook();

    return 0;
}

bool scene::retrievePiece() {

    sinsocket client_socket;
    uint8_t request_piece = 0x43;

    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n");
        //should do some error dialog here
        return 1; }

    //ask for current map info
    if ( client_socket.sendRaw( &request_piece, 1 ) ) return 1;

    //make sure our version is okay
    uint8_t their_version, my_version = (VERSION_MAJOR<<4) | VERSION_MINOR;;
    if ( client_socket.sendRaw(&my_version, 1) ) return 1;
    if ( client_socket.recvRaw(&their_version, 1) ) return 1;

    if ( their_version != my_version ) {
        printf("ERROR: Versions do not match, please update.\n");
        //should display a dialog about restarting/updating here, or even initiate an update
        client_socket.beginDisconnect();
        return 1;
    }

    uint8_t allowed;
    if ( client_socket.recvRaw(&allowed, 1) ) return 1;

    if ( !allowed ) {
        //we've been rejected
        printf("ERROR: Cannot participate in server\n");
        client_socket.beginDisconnect();
        return 1;
    }

    //send our username
    uint32_t name_length = strlen(username);
    if ( client_socket.sendRaw(&name_length, 4) ) return 1;
    if ( client_socket.sendRaw(username, name_length) ) return 1;

    //grab the protobuffer object
    packet_data *piece_packet;
    if ( client_socket.recvPacket(piece_packet, true) ) return 1;
    client_socket.beginDisconnect();

    sculpt::ServerPiece the_piece;
    the_piece.ParseFromArray( piece_packet->data, piece_packet->size() );
    delete piece_packet;

    my_piece_hash = the_piece.hash();
    my_piece_map_id = the_piece.map_id();
    my_piece_id = the_piece.piece_id();

    //convert the data from bitstream to vector
    std::vector<uint8_t> chunk_vector;
    sinbits::bits_to_vector( (const uint8_t*)&the_piece.data()[0], the_piece.data().size(), &chunk_vector );

    //create these boxes to render
    int current_piece = 0;
    surrounding_boxes.clear();

    for ( int o_y = 0; o_y <= 2; ++o_y )
      for ( int o_z = 0; o_z <= 2; ++o_z )
        for ( int o_x = 0; o_x <= 2; ++o_x )
          for ( unsigned int t_y=0; t_y < the_piece.size_y(); ++t_y)
            for ( unsigned int t_z=0; t_z < the_piece.size_z(); ++t_z)
              for ( unsigned int t_x=0; t_x < the_piece.size_x(); ++t_x)
                if ( o_y!=1 || o_z!=1 || o_x!=1 )
                  if ( chunk_vector[current_piece++] )
                    surrounding_boxes.draw(  0.5+o_x*the_piece.size_x()+t_x, 0.5+o_y*the_piece.size_y()+t_y, 0.5+o_z*the_piece.size_z()+t_z, 0.5);

    //printf("DEBUG: current_piece = %d, actual size = %d\n", current_piece, chunk_vector.size() );

    surrounding_boxes.optimize();
    have_piece = true;

    return 0;
}

bool scene::submitPiece() {

    if ( !have_piece ) return 1;

    sinsocket client_socket;
    uint8_t submit_piece = 0x74;

    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n");
        //should do some error dialog here
        return 1; }

    //ask for current map info
    if ( client_socket.sendRaw( &submit_piece, 1 ) ) return 1;

    //make sure our version is okay
    uint8_t their_version, my_version = (VERSION_MAJOR<<4) | VERSION_MINOR;;
    if ( client_socket.sendRaw(&my_version, 1) ) return 1;
    if ( client_socket.recvRaw(&their_version, 1) ) return 1;

    if ( their_version != my_version ) {
        printf("ERROR: Versions do not match, please update.\n");
        //should display a dialog about restarting/updating here, or even initiate an update
        client_socket.beginDisconnect();
        return 1;
    }

    uint8_t *bit_data;
    int bit_data_size;
    sinbits::vector_to_bits(built_list, &bit_data, &bit_data_size);

    sculpt::SubmitPiece to_submit;
    to_submit.set_piece_id(my_piece_id);
    to_submit.set_map_id(my_piece_map_id);
    to_submit.set_hash(my_piece_hash);
    to_submit.set_username(username);
    to_submit.set_data(bit_data, bit_data_size);

    int size_of_submit = to_submit.ByteSize();
    packet_data *sending_packet = new packet_data( malloc(size_of_submit), size_of_submit );
    to_submit.SerializeToArray(sending_packet->data, size_of_submit);
    if ( client_socket.sendPacket(sending_packet) ) return 1;

    //see if our submit was successful
    uint8_t submit_result;
    client_socket.recvRaw(&submit_result, 1);

    if ( submit_result ) {
        printf("ERROR: could not submit due to reason: %d\n", submit_result);
    }

    client_socket.beginDisconnect();

    return 0;
}


bool scene::retrieveEntireMap(int in) {

    sinsocket client_socket;
    uint8_t request_entire_map = 0x81;

    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n");
        //should do some error dialog here
        return 1; }

    //ask for current map info
    if ( client_socket.sendRaw( &request_entire_map, 1 ) ) return 1;

    //make sure our version is okay
    uint8_t their_version, my_version = (VERSION_MAJOR<<4) | VERSION_MINOR;;
    if ( client_socket.sendRaw(&my_version, 1) ) return 1;
    if ( client_socket.recvRaw(&their_version, 1) ) return 1;

    if ( their_version != my_version ) {
        printf("ERROR: Versions do not match, please update.\n");
        //should display a dialog about restarting/updating here, or even initiate an update
        client_socket.beginDisconnect();
        return 1;
    }

    //tell which server we want
    int32_t request_id = in;
    if ( client_socket.sendRaw(&request_id, 4) ) return 1;

    //see if our request is valid
    uint8_t is_valid;
    if ( client_socket.recvRaw(&is_valid, 1) ) return 1;

    if ( is_valid != 0x00 ) {
        //oh well
        printf("ERROR: Cannot get info for map_id %d\n",in);
        client_socket.beginDisconnect();
        return 1;
    }

    //receive the message
    packet_data *map_packet;
    if ( client_socket.recvPacket(map_packet, true) ) return 1;
    client_socket.beginDisconnect();

    sculpt::EntireMap the_map;
    the_map.ParseFromArray( map_packet->data, map_packet->size() );
    delete map_packet;

    //convert the data from bitstream to vector
    std::vector<uint8_t> chunk_vector;
    sinbits::bits_to_vector( (const uint8_t*)&the_map.data()[0], the_map.data().size(), &chunk_vector );

    //create these boxes to render
    int current_piece = 0;
    surrounding_boxes.clear();

    //printf("map: %d, %d, %d -- piece: %d, %d, %d\n", the_map.map_size_x(), the_map.map_size_y(), the_map.map_size_z(), the_map.piece_size_z(), the_map.piece_size_y(), the_map.piece_size_z());
    for ( unsigned int o_y = 0; o_y < the_map.map_size_y(); ++o_y )
      for ( unsigned int o_z = 0; o_z < the_map.map_size_z(); ++o_z )
        for ( unsigned int o_x = 0; o_x < the_map.map_size_x(); ++o_x )
          for ( unsigned int t_y=0; t_y < the_map.piece_size_y(); ++t_y)
            for ( unsigned int t_z=0; t_z < the_map.piece_size_z(); ++t_z)
              for ( unsigned int t_x=0; t_x < the_map.piece_size_x(); ++t_x)
                if ( chunk_vector[current_piece++] )
                  surrounding_boxes.draw(  0.5+o_x*the_map.piece_size_x()+t_x, 0.5+o_y*the_map.piece_size_y()+t_y, 0.5+o_z*the_map.piece_size_z()+t_z, 0.5);


    printf("DEBUG: current_piece = %d, actual size = %d\n", current_piece, chunk_vector.size() );
    surrounding_boxes.optimize();

    mainCamera.arcSetCenter( vec3f((float)the_map.map_size_x()/2.0 * (float)the_map.piece_size_x(), (float)the_map.map_size_y()/2.0 * (float)the_map.piece_size_y(), (float)the_map.map_size_z()/2.0 * (float)the_map.piece_size_z()) );

    return 0;
}



bool scene::retrieveServerList() {

    sinsocket client_socket;
    unsigned char list_request = 0x28;
    unsigned char num_of_servers;
    unsigned char server_name_length;
    ui_label *temp_label;
    char temp_widget_name[100];
    char temp_label_text[100];
    char temp_status[200];


    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n"); return 1; }

    //ask for a server list (0x28)
    client_socket.sendRaw( &list_request, 1 );

    //get number of servers being transferred
    client_socket.recvRaw( &num_of_servers, 1 );
    printf("* NETWORK: Preparing to receive %d servers...\n", num_of_servers );

    for ( int i=0; i < num_of_servers; ++i ) {
        client_socket.recvRaw( &servers[i].server_id, 1 );
        client_socket.recvRaw( &server_name_length, 1 );
        client_socket.recvRaw( servers[i].server_name, server_name_length );
        client_socket.recvRaw( &servers[i].total_pieces, 4 );
        client_socket.recvRaw( &servers[i].pieces_left, 4 );
        client_socket.recvRaw( &servers[i].player_total, 1 );
        client_socket.recvRaw( &servers[i].player_left, 1 );

        printf("%d(%d): [%s], %d/%d total pieces, %u/%u available pieces\n", i+1,
                                                                         servers[i].server_id,
                                                                         servers[i].server_name,
                                                                         servers[i].pieces_left,
                                                                         servers[i].total_pieces,
                                                                         servers[i].player_left,
                                                                         servers[i].player_total );
    }

    //clean up the socket
    client_socket.beginDisconnect();

    //populate list with correct values
    for ( int i=0; i < 5; ++i ) {

        if ( i < num_of_servers ) {
            sprintf(temp_widget_name,"server%d_name",i+1);
            temp_label = (ui_label*)mainGui.getWidget(temp_widget_name);
            sprintf(temp_label_text,"%s",servers[i].server_name);
            temp_label->my_font.setText(temp_label_text); temp_label->my_font.cook();

            sprintf(temp_widget_name,"server%d_complete",i+1);
            temp_label = (ui_label*)mainGui.getWidget(temp_widget_name);
            sprintf(temp_label_text,"%u / %u",servers[i].pieces_left, servers[i].total_pieces);
            temp_label->my_font.setText(temp_label_text); temp_label->my_font.cook();

            sprintf(temp_widget_name,"server%d_available",i+1);
            temp_label = (ui_label*)mainGui.getWidget(temp_widget_name);
            sprintf(temp_label_text,"%u / %u",servers[i].player_left, servers[i].player_total);
            temp_label->my_font.setText(temp_label_text); temp_label->my_font.cook();

        } else {
            //fill with blanks
            sprintf(temp_widget_name,"server%d_name",i+1);
            temp_label = (ui_label*)mainGui.getWidget(temp_widget_name);
            temp_label->my_font.setText(""); temp_label->my_font.cook();

            sprintf(temp_widget_name,"server%d_complete",i+1);
            temp_label = (ui_label*)mainGui.getWidget(temp_widget_name);
            temp_label->my_font.setText(""); temp_label->my_font.cook();

            sprintf(temp_widget_name,"server%d_available",i+1);
            temp_label = (ui_label*)mainGui.getWidget(temp_widget_name);
            temp_label->my_font.setText(""); temp_label->my_font.cook();
        }
    }

    sprintf(temp_status,"SUCCESS: Retrieved %d server entries.",num_of_servers);
    temp_label = (ui_label*)mainGui.getWidget("comm_status");
    temp_label->my_font.setText(temp_status); temp_label->my_font.cook();

    return 0;
}

bool scene::participateInServer( int inserver ) {

    sinsocket client_socket;
    unsigned char participate_request = 0x43;
    unsigned char can_participate = 0;
    unsigned int selected_server = servers[inserver-1].server_id;

    if ( client_socket.connect("localhost",35610) ) {
        printf("ERROR: could not connect to localhost!\n"); return 1; }

    //ask to participate (0x43) in a specific server
    client_socket.sendRaw( &participate_request, 1 );
    client_socket.sendRaw( &selected_server, 1 );

    //see if we're able to get a piece
    client_socket.recvRaw( &can_participate, 1 );

    if ( !can_participate ) {
        printf("* NETWORK: cannot participate in server_id %d!\n", servers[inserver-1].server_id);
        return 1;
    }

    //grab the hash for our piece
    client_socket.recvRaw( my_hash, 17 );
    printf("* NETWORK: received hash [%s] for our piece\n", my_hash);

    //grab the size
    client_socket.recvRaw( &piece_x_size, 1 );
    client_socket.recvRaw( &piece_y_size, 1 );
    client_socket.recvRaw( &piece_z_size, 1 );
    //printf("* NETWORK: received piece size of %d, %d, %d\n", piece_x_size, piece_y_size, piece_z_size);


    int blob_size = piece_x_size*piece_y_size*piece_z_size*26;
    piece_blob = new char[blob_size];

    //get da blob
    //printf("* NETWORK: attempting to receive blob size %d\n", blob_size);
    client_socket.recvRaw( piece_blob, blob_size );

    //we're done!
    client_socket.beginDisconnect();
    printf("* NETWORK: Successfully received blob of size %d\n", blob_size);

    //make our grid and cubes
    generateVA();

    //reset the camera in a random orientation
    resetCamera();

    //close all the menus
    myself->mainGui.getWindow("ServerList")->doFade(UI_FADE_OUT, 10);

    //grab the mouse
    mouseGrab = true;
    glfwDisable( GLFW_MOUSE_CURSOR );

    //let the program know we have a piece
    have_piece = true;



    return 0;
}

