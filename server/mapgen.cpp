
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sqlite3.h>
#include <time.h>
#include <dsfmt.c>

#include "sinsql.h"


bool create_new_map(const char*,const char*,int,int,int,int,int,int,int,int,int);

///////////////////////////////////////////////////////////////////////////////
//
int main(int, char **) {

    if ( create_new_map("test_1",  //table name
                        "Initial test", //description
                        5,5,5,     //x,y,z size
                        5,5,5,     //piece x,y,z size
                        20,        //pieces per user
                        1,          //recharge rate (hours)
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

    sqlite3 *db;
    char temp_string[200];
    sqlite3_stmt *insert_statement;
    bool unique;

    //temp table values
    unsigned char map_id;
    int   table_id;
    char  table_hash[17];

    //seed the holy RNG
    init_gen_rand(time(NULL));

  try {

    //open the database file
    sinsql_open_db("sculpt-db", db);
    printf("Opened database.\n");

    //create the table for this map
    sprintf(temp_string, "CREATE TABLE %s ( id integer primary key, "
                         "hash text, username text default null, ip text default null, "
                         "hostname text default null, checkout text default null, "
                         "checkin text default null, data none default null );", name_table);

    sinsql_exec(db, temp_string);
    printf("Created table.\n");

    //generate a map ID and make sure it isn't in use
    unique = false;
    while (!unique) {
        map_id = genrand_open_close()*255;
        sprintf(temp_string, "select null from server_maps where id = %d;", map_id);
        if ( !sinsql_existence(db, temp_string) ) unique = true;
    }

    //insert an entry for this table in the information table
    sprintf(temp_string, "insert into server_maps values (%d,\"%s\",\"%s\",%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d);",
                        map_id,
                        name_table,
                        description,
                        size_x, size_y, size_z,
                        piece_size_x, piece_size_y, piece_size_z,
                        pieces_per_user, recharge_rate,
                        size_x*size_y*size_z,
                        size_x*size_y*size_z,
                        distribution );
    sinsql_exec(db, temp_string);
    printf("Inserted table information.\n");



    //prepare map insert statement
    sprintf(temp_string, "insert into %s (id,hash) values (?,?);", name_table);
    sinsql_stmt_prep(db, temp_string, insert_statement);

    //populate the database with the correct number of chunks
    sinsql_exec(db, "BEGIN;");
    for ( table_id = 0; table_id < size_x*size_y*size_z; ++table_id ) {

        for ( int i=0; i < 16; ++i )
            table_hash[i] = ( 65 + (int)(genrand_close_open()*26.0) + (genrand_close_open() < 0.5 ? 0 : 32 ) );
        table_hash[16] = '\0';

        //bind all the values to insert
        sqlite3_bind_int(insert_statement, 1, table_id);
        sqlite3_bind_text(insert_statement, 2, table_hash,-1,SQLITE_STATIC);

        //execute the insert
        sinsql_stmt_step(insert_statement);

        //reset the statement to be used again
        sqlite3_reset(insert_statement);
    }
    sinsql_exec(db, "COMMIT;");

    //clean up the statement
    sinsql_stmt_fin(insert_statement);
    printf("Created map pieces.\n");

    sqlite3_close(db);

  } catch ( int error ) {
        //print the last error if db is valid
        if ( db != NULL )
            printf("Last SQL error: %s\n", sqlite3_errmsg(db));
        //close the database if it isn't already
        if ( db != NULL ) sqlite3_close(db);

        return true;
  }
    return false;
}


/*
    //lets display what is in the database
    sprintf(temp_string,"select * from sculpture0;");
    rc = sqlite3_prepare_v2(db,                     // Database handle
                            temp_string,            // SQL statement, UTF-8 encoded
                            strlen(temp_string),    // Maximum length of zSql in bytes
                            &select_statement,      // OUT: Statement handle
                            NULL                    // OUT: Pointer to unused portion of zSql
                            );
    if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db) );
    }
    //step here
    //loop through the result set
    rc = SQLITE_ROW;
    while ( rc == SQLITE_ROW ) {
        rc = sqlite3_step(select_statement);
        switch (rc) {
            case SQLITE_ROW:
                for ( int i=0; i < sqlite3_column_count(select_statement); ++i ) {
                    switch ( sqlite3_column_type(select_statement, i) ) {
                        case SQLITE_INTEGER:
                            printf("Column %d [%s] is Integer = [%d]\n", i, sqlite3_column_name(select_statement, i), sqlite3_column_int(select_statement, i) );
                            break;
                        case SQLITE_FLOAT:
                            printf("Column %d [%s] is Float = [%f]\n", i, sqlite3_column_name(select_statement, i), sqlite3_column_double(select_statement, i) );
                            break;
                        case SQLITE_TEXT:
                            printf("Column %d [%s] is Text = \"%s\"\n", i, sqlite3_column_name(select_statement, i), sqlite3_column_text(select_statement, i) );
                            break;
                        case SQLITE_BLOB:
                            printf("Column %d [%s] is BLOB\n", i, sqlite3_column_name(select_statement, i) );
                            break;
                        case SQLITE_NULL:
                            printf("Column %d [%s] is NULL\n", i, sqlite3_column_name(select_statement, i) );
                            break;
                    }
                }
                printf("\n");
                break;

            case SQLITE_DONE:
                //do nothing, loop will exit
                break;
            case SQLITE_BUSY:
                fprintf(stderr, "SQL_BUSY returned!\n"); break;
            default:
                fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db) ); break;
        }
    }
    //clean up the statement
    sqlite3_finalize(select_statement);
*/

/*

    //loop through the result set
    rc = SQLITE_ROW;
    while ( rc == SQLITE_ROW ) {
        rc = sqlite3_step(select_statement);
        switch (rc) {
            case SQLITE_ROW:
                for ( int i=0; i < sqlite3_column_count(select_statement); ++i ) {
                    switch ( sqlite3_column_type(select_statement, i) ) {
                        case SQLITE_INTEGER:
                            printf("Column %d [%s] is Integer = [%d]\n", i, sqlite3_column_name(select_statement, i), sqlite3_column_int(select_statement, i) );
                            break;
                        case SQLITE_FLOAT:
                            printf("Column %d [%s] is Float = [%f]\n", i, sqlite3_column_name(select_statement, i), sqlite3_column_double(select_statement, i) );
                            break;
                        case SQLITE_TEXT:
                            printf("Column %d [%s] is Text = \"%s\"\n", i, sqlite3_column_name(select_statement, i), sqlite3_column_text(select_statement, i) );
                            break;
                        case SQLITE_BLOB:
                            printf("Column %d [%s] is BLOB\n", i, sqlite3_column_name(select_statement, i) );
                            break;
                        case SQLITE_NULL:
                            printf("Column %d [%s] is NULL\n", i, sqlite3_column_name(select_statement, i) );
                            break;
                    }
                }
                printf("\n");
                break;

            case SQLITE_DONE:
                //do nothing, loop will exit
                break;
            case SQLITE_BUSY:
                fprintf(stderr, "SQL_BUSY returned!\n"); break;
            default:
                fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db) ); break;
        }
    }
*/

/*
    callbackIsInit = 0;
    nCol = sqlite3_column_count(pStmt);

    while( 1 ){
      int i;
      rc = sqlite3_step(pStmt);

      // Invoke the callback function if required
      if( xCallback && (SQLITE_ROW==rc ||
          (SQLITE_DONE==rc && !callbackIsInit
                           && db->flags&SQLITE_NullCallback)) ){
        if( !callbackIsInit ){
          azCols = sqlite3DbMallocZero(db, 2*nCol*sizeof(const char*) + 1);
          if( azCols==0 ){
            goto exec_out;
          }
          for(i=0; i<nCol; i++){
            azCols[i] = (char *)sqlite3_column_name(pStmt, i);
            // sqlite3VdbeSetColName() installs column names as UTF8
            // strings so there is no way for sqlite3_column_name() to fail.
            assert( azCols[i]!=0 );
          }
          callbackIsInit = 1;
        }
        if( rc==SQLITE_ROW ){
          azVals = &azCols[nCol];
          for(i=0; i<nCol; i++){
            azVals[i] = (char *)sqlite3_column_text(pStmt, i);
            if( !azVals[i] && sqlite3_column_type(pStmt, i)!=SQLITE_NULL ){
              db->mallocFailed = 1;
              goto exec_out;
            }
          }
        }
        if( xCallback(pArg, nCol, azVals, azCols) ){
          rc = SQLITE_ABORT;
          sqlite3VdbeFinalize((Vdbe *)pStmt);
          pStmt = 0;
          sqlite3Error(db, SQLITE_ABORT, 0);
          goto exec_out;
        }
      }

      if( rc!=SQLITE_ROW ){
        rc = sqlite3VdbeFinalize((Vdbe *)pStmt);
        pStmt = 0;
        if( rc!=SQLITE_SCHEMA ){
          nRetry = 0;
          zSql = zLeftover;
          while( sqlite3Isspace(zSql[0]) ) zSql++;
        }
        break;
      }
    }

    sqlite3DbFree(db, azCols);
    azCols = 0;
  }

exec_out:
  if( pStmt ) sqlite3VdbeFinalize((Vdbe *)pStmt);
  sqlite3DbFree(db, azCols);

  rc = sqlite3ApiExit(db, rc);
  if( rc!=SQLITE_OK && ALWAYS(rc==sqlite3_errcode(db)) && pzErrMsg ){
    int nErrMsg = 1 + sqlite3Strlen30(sqlite3_errmsg(db));
    *pzErrMsg = sqlite3Malloc(nErrMsg);
    if( *pzErrMsg ){
      memcpy(*pzErrMsg, sqlite3_errmsg(db), nErrMsg);
    }else{
      rc = SQLITE_NOMEM;
      sqlite3Error(db, SQLITE_NOMEM, 0);
    }
  }else if( pzErrMsg ){
    *pzErrMsg = 0;
  }
*/

/*
int main(int argc, char **argv)
{
	sqlite3 *db;
	sqlite3_stmt *plineInfo = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t mread;

	int fd, n;
	long buflen = 0, totread = 0;
	char *buf = NULL, *pbuf = NULL;

	//  char *zErrMsg = 0;
	int rc, i;

	if (argc == 4) {
		rc = sqlite3_prepare(db, argv[3], -1, &plineInfo, 0);
		if (rc == SQLITE_OK && plineInfo != NULL) {
			//fprintf(stderr, "SQLITE_OK\n");
			sqlite3_bind_blob(plineInfo, 1, buf, totread,
					  free);
			while ((rc =
				sqlite3_step(plineInfo)) == SQLITE_ROW) {
				//
				for (i = 0;
				     i < sqlite3_column_count(plineInfo);
				     ++i)
					print_col(plineInfo, i);

				printf("\n");

			}
			rc = sqlite3_finalize(plineInfo);
		}
		fprintf(stderr, "eatblob:%d> ", sqlite3_total_changes(db));

	} else {
		fprintf(stderr, "eatblob:0> ");
		while ((mread = mygetline(&line, &len, stdin)) > 0) {
			rc = sqlite3_prepare(db, line, -1, &plineInfo, 0);
			if (rc == SQLITE_OK && plineInfo != NULL) {
				//fprintf(stderr, "SQLITE_OK\n");
				sqlite3_bind_blob(plineInfo, 1, buf,
						  totread, free);
				while ((rc =
					sqlite3_step(plineInfo)) ==
				       SQLITE_ROW) {
					//
					for (i = 0;
					     i <
					     sqlite3_column_count
					     (plineInfo); ++i)
						print_col(plineInfo, i);

					printf("\n");

				}
				rc = sqlite3_finalize(plineInfo);
			}
			fprintf(stderr, "eatblob:%d> ",
				sqlite3_total_changes(db));
		}		// end of while

	}

	if (line) {
		free(line);
	}
	sqlite3_close(db);
	return 0;
}

*/

///////////////////////////////////////////////////////////////////////////////
//
/*
static int callback(void *NotUsed, int num_results, char **argv, char **azColName){

  for(int i=0; i<num_results; ++i){
    printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
  }
  printf("\n");
  return 0;
}
*/
