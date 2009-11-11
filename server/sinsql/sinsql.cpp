
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sinsql.h"


///////////////////////////////////////////////////////////////////////////////
//
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
            throw (rc);
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
            fprintf(stderr, "SQL error (finalize in existence): %s\n", sqlite3_errmsg(db) );
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


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_exec(sqlite3 *db, const char *query) throw (int) {

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
            fprintf(stderr, "SQL error (prepare in exec): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_step(temp_statement);
    switch ( rc ) {
        case SQLITE_DONE:
            //successful
            result = false;
            break;
        case SQLITE_ROW:
            //found a row, this shouldn't be happening but.. whatever..
            result = false;
            break;
        default:
            fprintf(stderr, "SQL error (step in exec): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_finalize(temp_statement);
    switch( rc ) {
        case SQLITE_OK:
            //everything is fine
            break;
        default:
            fprintf(stderr, "SQL error (finalize in exec): %s\n", sqlite3_errmsg(db) );
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


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_get_int(sqlite3 *db, const char *query, int &output) throw (int) {

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
            fprintf(stderr, "SQL error (prepare in get_int): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_step(temp_statement);
    switch ( rc ) {
        case SQLITE_DONE:
            //we don't want this! we want a result :( ah well, return error
            result = true;
            break;
        case SQLITE_ROW:
            //yeaaa a result, lets get that sucker
            output = sqlite3_column_int(temp_statement, 0);
            result = false;
            break;
        default:
            fprintf(stderr, "SQL error (step in get_int): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_finalize(temp_statement);
    switch( rc ) {
        case SQLITE_OK:
            //everything is fine
            break;
        default:
            fprintf(stderr, "SQL error (finalize in get_int): %s\n", sqlite3_errmsg(db) );
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


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_get_text(sqlite3 *db, const char *query, char* &output ) throw (int) {

  sqlite3_stmt *temp_statement = NULL;

  try {

    bool result;
    int rc;
    int string_size;

    rc = sqlite3_prepare_v2(db, query, -1, &temp_statement, NULL);
    switch ( rc ) {
        case SQLITE_OK:
            //everything is fine
            break;
        default:
            fprintf(stderr, "SQL error (prepare in get_text): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_step(temp_statement);
    switch ( rc ) {
        case SQLITE_DONE:
            //we don't want this! we want a result :( ah well, return error
            output = NULL;
            result = true;
            break;
        case SQLITE_ROW:
            //make sure its a blob
            if ( sqlite3_column_type(temp_statement,0) != SQLITE_TEXT ) {
                //not a blob, return error
                output = NULL; result = true;
                break;
            }
            //grab the result
            string_size = sqlite3_column_bytes(temp_statement,0);
            output = (char*)malloc(string_size);
            memcpy(output, sqlite3_column_text(temp_statement, 0), string_size);
            result = false;
            break;
        default:
            fprintf(stderr, "SQL error (step in get_blob): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_finalize(temp_statement);
    switch( rc ) {
        case SQLITE_OK:
            //everything is fine
            break;
        default:
            fprintf(stderr, "SQL error (finalize in get_text): %s\n", sqlite3_errmsg(db) );
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


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_get_blob(sqlite3 *db, const char *query, void* &output, int &output_size ) throw(int) {

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
            fprintf(stderr, "SQL error (prepare in get_blob): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_step(temp_statement);
    switch ( rc ) {
        case SQLITE_DONE:
            //we don't want this! we want a result :( ah well, return error
            output = NULL;
            result = true;
            break;
        case SQLITE_ROW:
            //make sure its a blob
            if ( sqlite3_column_type(temp_statement,0) != SQLITE_BLOB ) {
                //not a blob, return error
                output = NULL; output_size = -1; result = true;
                break;
            }
            //grab the result
            output_size = sqlite3_column_bytes(temp_statement,0);
            output = (void*)malloc(output_size);
            memcpy(output, sqlite3_column_blob(temp_statement, 0), output_size);
            result = false;
            break;
        default:
            fprintf(stderr, "SQL error (step in get_blob): %s\n", sqlite3_errmsg(db) );
            throw (rc);
            break;
    }

    rc = sqlite3_finalize(temp_statement);
    switch( rc ) {
        case SQLITE_OK:
            //everything is fine
            break;
        default:
            fprintf(stderr, "SQL error (finalize in get_blob): %s\n", sqlite3_errmsg(db) );
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


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_open_db(const char *db_name, sqlite3* &db ) throw (int) {
  try {

    int rc;
    int result;

    rc = sqlite3_open(db_name, &db);
    switch ( rc ) {
        case SQLITE_OK:
            //everything is fine
            result = false;
            break;
        default:
            //freak out!
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            db = NULL;
            throw (rc);
            break;
    }

    return result;

//////////
  } catch ( int error ) {
      throw;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_stmt_prep(sqlite3 *db, const char *query, sqlite3_stmt* &statement) throw (int) {
  try {

    int rc;
    int result;

    rc = sqlite3_prepare_v2(db,         // Database handle
                            query,      // SQL statement, UTF-8 encoded
                            -1,         // Maximum length of zSql in bytes (-1 is till \0)
                            &statement, // OUT: Statement handle
                            NULL        // OUT: Pointer to unused portion of zSql
                            );

    switch ( rc ) {
        case SQLITE_OK:
            //everything is fine
            result = false;
            break;
        default:
            //badness
            fprintf(stderr, "SQL error (stmt prepare): %s\n", sqlite3_errmsg(db) );
            sqlite3_finalize(statement);
            throw (rc);
            break;
    }

    return result;

//////////
  } catch ( int error ) {
      throw;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_stmt_step(sqlite3_stmt* &statement) throw (int) {
  try {

    int rc;
    int result;

    rc = sqlite3_step(statement);
    switch ( rc ) {
        case SQLITE_DONE:
            //everything is fine
            result = false;
            break;
        case SQLITE_ROW:
            //return a 1 when we get a row
            result = true;
            break;
        default:
            //badness
            fprintf(stderr, "SQL error (stmt step): %d\n", rc); //sqlite3_errmsg(db)
            sqlite3_finalize(statement);
            throw (rc);
            break;
    }

    return result;

//////////
  } catch ( int error ) {
      throw;
  }
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_stmt_fin(sqlite3_stmt* &statement) throw (int) {
  try {

    int rc;
    int result;

    rc = sqlite3_finalize(statement);
    switch ( rc ) {
        case SQLITE_OK:
            //everything is fine
            result = false;
            break;
        default:
            //badness
            fprintf(stderr, "SQL error (stmt finalize): %d\n", rc); //sqlite3_errmsg(db)
            throw (rc);
            break;
    }

    return result;

//////////
  } catch ( int error ) {
      throw;
  }
}
