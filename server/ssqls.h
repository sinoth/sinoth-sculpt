#ifndef SERV_SSQLS_H
#define SERV_SSQLS_H

#include <mysql++.h>
#include <ssqls.h>


sql_create_16( server_maps, 1, 16,
              mysqlpp::sql_int, map_id,
              mysqlpp::sql_varchar, name,
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
              mysqlpp::sql_int, pieces_total,
              mysqlpp::sql_int, pieces_left,
              mysqlpp::sql_varchar, distribution,
              mysqlpp::sql_varchar, notes
          );


sql_create_7( map, 1, 7,
              mysqlpp::sql_int, piece_id,
              mysqlpp::sql_varchar, hash,
              mysqlpp::sql_varchar, username,
              mysqlpp::sql_varchar, ip,
              mysqlpp::sql_timestamp, checkout,
              mysqlpp::sql_timestamp, checkin,
              mysqlpp::sql_blob, data
          );


#endif

