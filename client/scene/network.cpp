
#include "scene.h"

typedef struct serverinfo_s {
    char server_name[100];
    int total_pieces;
    int pieces_left;
    unsigned char player_total;
    unsigned char player_left;
} serverinfo;


bool scene::retrieveServerList() {

    sinsocket client_socket;
    serverinfo servers[5];
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
    client_socket.send( &list_request, 1 );

    //get number of servers being transferred
    client_socket.recv( &num_of_servers, 1 );
    printf("* NETWORK: Preparing to receive %d servers...\n", num_of_servers );

    for ( int i=0; i < num_of_servers; ++i ) {
        client_socket.recv( &server_name_length, 1 );
        client_socket.recv( servers[i].server_name, server_name_length );
        client_socket.recv( &servers[i].total_pieces, 4 );
        client_socket.recv( &servers[i].pieces_left, 4 );
        client_socket.recv( &servers[i].player_total, 1 );
        client_socket.recv( &servers[i].player_left, 1 );

        printf("%d: [%s], %d/%d total pieces, %u/%u available pieces\n", i+1,
                                                                         servers[i].server_name,
                                                                         servers[i].pieces_left,
                                                                         servers[i].total_pieces,
                                                                         servers[i].player_left,
                                                                         servers[i].player_total );
    }

    //clean up the socket
    client_socket.disconnect();

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


