#ifndef SERV_SSQLS_H
#define SERV_SSQLS_H

#include <mysql++.h>
#include <ssqls.h>

///////////////////////////////////
sql_create_14( server_maps, 1, 14,
              mysqlpp::sql_varchar, description,
              mysqlpp::sql_varchar, table_name,
              mysqlpp::sql_int, x_size,
              mysqlpp::sql_int, y_size,
              mysqlpp::sql_int, z_size,
              mysqlpp::sql_int, piece_x_size,
              mysqlpp::sql_int, piece_y_size,
              mysqlpp::sql_int, piece_z_size,
              mysqlpp::sql_int, pieces_per_user,
              mysqlpp::sql_int, recharge_rate,
              mysqlpp::sql_varchar, distribution,
              mysqlpp::sql_int, pieces_total,
              //mysqlpp::sql_int, pieces_completed,
              mysqlpp::Null<mysqlpp::sql_varchar>, notes,
              mysqlpp::Null<mysqlpp::sql_int>, map_id );

///////////////////////////////////
sql_create_14( get_server_maps, 1, 14,
              mysqlpp::sql_varchar, description,
              mysqlpp::sql_varchar, table_name,
              mysqlpp::sql_int, x_size,
              mysqlpp::sql_int, y_size,
              mysqlpp::sql_int, z_size,
              mysqlpp::sql_int, piece_x_size,
              mysqlpp::sql_int, piece_y_size,
              mysqlpp::sql_int, piece_z_size,
              mysqlpp::sql_int, pieces_per_user,
              mysqlpp::sql_int, recharge_rate,
              mysqlpp::sql_varchar, distribution,
              mysqlpp::sql_int, pieces_total,
              //mysqlpp::sql_int, pieces_completed,
              mysqlpp::Null<mysqlpp::sql_varchar>, notes,
              mysqlpp::Null<mysqlpp::sql_timestamp>, completed_timestamp,
              mysqlpp::sql_int, map_id );

////////////////////////////////
sql_create_8( current_map, 1, 8,
              mysqlpp::sql_int, piece_id,
              mysqlpp::sql_int, piece_order,
              mysqlpp::sql_varchar, piece_hash,
              mysqlpp::Null<mysqlpp::sql_varchar>, username,
              mysqlpp::Null<mysqlpp::sql_varchar>, ip,
              mysqlpp::Null<mysqlpp::sql_timestamp>, checkout,
              mysqlpp::Null<mysqlpp::sql_timestamp>, checkin,
              mysqlpp::Null<mysqlpp::sql_blob>, data );

/////////////////////////////////////
sql_create_2( current_versions, 1, 2,
              mysqlpp::sql_varchar, name,
              mysqlpp::sql_varchar, version );

#endif

