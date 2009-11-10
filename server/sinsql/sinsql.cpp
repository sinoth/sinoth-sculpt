
#include <stdio.h>
#include "sinsql.h"

bool sinsql_existence(sqlite3 *db, const char *query) throw(int) {

  sqlite3_stmt *temp_statement = NULL;

  try {

    bool result;
    int rc;

    rc = sqlite3_prepare_v2(db, query, -1, &temp_statement, NULL);
    switch ( rc ) {
        case SQLITE_OK:
            //everything is fine
            break;
        default:
            fprintf(stderr, "SQL error (prepare in existence): %s\n", sqlite3_errmsg(db) );
            throw (1);
            break;
    }

    rc = sqlite3_step(temp_statement);
    switch ( rc ) {
        case SQLITE_DONE:
            //no result from query, so send back a negatory
            result = false;
            break;
        case SQLITE_ROW:
            //found a row! send back an affirmative
            result = true;
            break;
        default:
            fprintf(stderr, "SQL error (step in existence): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_finalize(temp_statement);
    switch( rc ) {
        case SQLITE_OK:
            //everything is fine
            break;
        default:
            fprintf(stderr, "SQL error (finalize check piece): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    return result;

//////////
  } catch (int error) {
      //free statement if we need to
      if ( temp_statement != NULL ) {
          sqlite3_finalize(temp_statement);
      }
      throw;
  }
}








//bool sinsql_get_text(sqlite3 *db, const char *query, char* &result );
//bool sinsql_get_int(sqlite3 *db, const char *query, int &result);
//bool sinsql_get_blob(sqlite3 *db, const char *query, unsigned char* &result, int &result_size);
//bool sinsql_exec(sqlite3 *db, const char *query);

