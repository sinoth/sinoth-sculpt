
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <dsfmt.c>
#include <iostream>

#include "ssqls.h"

using std::cerr;
using std::cout;


bool create_new_map(const char*,const char*,int,int,int,int,int,int,int,int,int);

///////////////////////////////////////////////////////////////////////////////
//
int main(int, char **) {

    if ( create_new_map("test_01",  //table name
                        "Initial test", //description
                        5,5,5,     //x,y,z size
                        5,5,5,     //piece x,y,z size
                        20,        //pieces per user
                        1,         //recharge rate (hours)
                        0          //distribution method
                        ) ) {
        //something went wrong!
        fprintf(stderr,"Error: map not created\n"); return 1; }

    printf("Map created successfully!\n");
    return 0;
}



///////////////////////////////////////////////////////////////////////////////
//
bool create_new_map(const char* name_table,
                    const char* description,
                    int size_x, int size_y, int size_z,
                    int piece_size_x, int piece_size_y, int piece_size_z,
                    int pieces_per_user,
                    int recharge_rate,
                    int distribution    ) {

    //seed the holy RNG
    init_gen_rand(time(NULL));

  try {

    mysqlpp::Connection conn;
    //make connection to the updater database
    if ( !conn.connect("sculpt", "localhost", "sculpt_user", "sculpt_password") ) {
        cerr << "DB connection failed (sculpt): " << conn.error() << "\n";
        return NULL; }

    mysqlpp::Query query = conn.query();
    mysqlpp::StoreQueryResult res;
    mysqlpp::SimpleResult simple_res;

    //open the database file
    printf("Opened database.\n");

    //create the table for this map
    query << "CREATE TABLE `" << name_table << "` (";
    query << "`piece_id` int(11) NOT NULL,";
    query << "`piece_order` int(11) NOT NULL,";
    query << "`piece_hash` varchar(32) NOT NULL,";
    query << "`username` varchar(20) NULL DEFAULT NULL,";
    query << "`ip` varchar(46) NULL DEFAULT NULL,";
    query << "`checkout` timestamp NULL DEFAULT NULL,";
    query << "`checkin` timestamp NULL DEFAULT NULL,";
    query << "`data` blob NULL DEFAULT NULL,";
    query << "PRIMARY KEY (`piece_id`),";
    query << "  UNIQUE KEY `id_UNIQUE` (`piece_id`)";
    query << ") ENGINE=InnoDB DEFAULT CHARSET=utf8;";

    if ( !(simple_res = query.execute() ) ) {
        printf("Table creation failed.\n");
        return 1;
    }

    printf("Created table.\n");


    char distribution_string[46];
    switch ( distribution ) {
        case 0: sprintf(distribution_string,"sequential from 0,0,0"); break;
        default: sprintf(distribution_string,"ERROR"); break;
    }

    server_maps new_map(description, name_table,
                        size_x, size_y, size_z,
                        piece_size_x, piece_size_y, piece_size_z,
                        pieces_per_user, recharge_rate, distribution_string,
                        size_x*size_y*size_z, //0,
                        mysqlpp::null, mysqlpp::null );

    simple_res = query.insert(new_map).execute();
    if ( simple_res.rows() != (unsigned int)1 ) {
        printf("Error in server_maps insert.\n");
        return 1;
    }
    printf("Inserted table information.\n");

    //insert each piece into map w/ hash
    current_map::table(name_table);
    std::vector<current_map> cmaps;
    char  table_hash[17];
    int piece_order=0, table_id = 0, real_pieces=0;


    for (int ty=0; ty < size_y+2; ++ty)
      for (int tz=0; tz < size_z+2; ++tz)
        for (int tx=0; tx < size_x+2; ++tx) {
        //for ( int table_id = 0; table_id < (size_x+2)*(size_y+2)*(size_z+2); ++table_id ) {
            table_id = tx + ty*(size_x+2)*(size_z+2) + tz*(size_x+2);
            //see if we're on the 'buffer'
            if ( tx==0 || tx == size_x+1 || ty == 0 || ty == size_y+1 || tz == 0 || tz == size_z+1 ) {
                sprintf(table_hash, "buffer");
                piece_order = -1;
            } else {
                //not in buffer
                for ( int i=0; i < 16; ++i )
                    table_hash[i] = ( 65 + (int)(genrand_close_open()*26.0) + (genrand_close_open() < 0.5 ? 0 : 32 ) );
                table_hash[16] = '\0';
                piece_order = real_pieces++;
            }

            cmaps.push_back( current_map(table_id, piece_order, table_hash,
                                        mysqlpp::null,
                                        mysqlpp::null,
                                        mysqlpp::null,
                                        mysqlpp::null,
                                        mysqlpp::null ) );
    }

    simple_res = query.insert( cmaps.begin(), cmaps.end() ).execute();
    if ( simple_res.rows() != (unsigned int)((size_x+2)*(size_y+2)*(size_z+2)) ) {
        printf("Problem inserting rows, only inserted %lu\n", (unsigned long)simple_res.rows());
        return 1;
    }

    printf("Created %lu map pieces.\n", (unsigned long)simple_res.rows());


//////////
  } catch (const mysqlpp::Exception& er) {
    // Catch-all for any other MySQL++ exceptions
    std::cerr << "Error: " << er.what() << std::endl;
    return true;
  }
//////////

    return false;

}
