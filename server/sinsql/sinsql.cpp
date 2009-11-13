
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sinsql.h"


///////////////////////////////////////////////////////////////////////////////
// statement class for RAII magic
sinsql_statement::sinsql_statement(sqlite3 *db, const char *query) {
    my_db = db;
    rc = sqlite3_prepare_v2(db, query, -1, &my_statement, NULL);
    switch ( rc ) {
        case SQLITE_OK: break;
        default:
            throw (sinsql_exception("sinsql_statement ctor",sqlite3_errmsg(db),rc));
            break;
    }
}
///////////////////////////////////////////////////////////////////////////////
int sinsql_statement::step() {
    rc = sqlite3_step(my_statement);
    switch ( rc ) {
        case SQLITE_DONE: case SQLITE_ROW:
            //both of these cases are fine.  pass the result
            return rc; break;
        default:
            //everything else is an error, so flip out
            throw (sinsql_exception("sinsql_statement step",sqlite3_errmsg(my_db),rc));
            break;
    }
}
///////////////////////////////////////////////////////////////////////////////
sinsql_statement::~sinsql_statement() throw () {
    switch( sqlite3_finalize(my_statement) ) {
        case SQLITE_OK: break;
        default:
            fprintf(stderr, "SQL error (sinsql_statement dtor): [%d]%s\n", rc, sqlite3_errmsg(my_db) );
            //throw (rc); //don't throw! bad things will happen!
            break;
    }
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_existence(sqlite3 *db, const char *query) {

    sinsql_statement temp_statement(db, query);

    switch ( temp_statement.step() ) {
        case SQLITE_DONE:
            //no result from query, so send back a negatory
            return false; break;
        case SQLITE_ROW:
            //found a row! send back an affirmative
            return true; break;
        default:
            break;
    }
    return false;
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_exec(sqlite3 *db, const char *query) {

    sinsql_statement temp_statement(db, query);

    switch ( temp_statement.step() ) {
        case SQLITE_DONE:
            //successful
            return false; break;
        case SQLITE_ROW:
            //also okay
            return false; break;
        default:
            break;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_get_int(sqlite3 *db, const char *query, int &output) {

    sinsql_statement temp_statement(db, query);

    switch ( temp_statement.step() ) {
        case SQLITE_DONE:
            //we don't want this! we want a result :( ah well, return error
            return true; break;

        case SQLITE_ROW:
            //yeaaa a result, lets get that sucker
            output = sqlite3_column_int(temp_statement.me(), 0);
            return false; break;

        default:
            break;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_get_text(sqlite3 *db, const char *query, char* &output ) {

    int string_size;
    sinsql_statement temp_statement(db, query);


    switch ( temp_statement.step() ) {
        case SQLITE_DONE:
            //we don't want this! we want a result :( ah well, return error
            output = NULL;
            return true; break;

        case SQLITE_ROW:
            //make sure its a blob
            if ( sqlite3_column_type(temp_statement.me(),0) != SQLITE_TEXT ) {
                //not a blob, return error
                output = NULL;
                return true; break;
            }
            //grab the result
            string_size = sqlite3_column_bytes(temp_statement.me(),0);
            output = (char*)malloc(string_size);
            memcpy(output, sqlite3_column_text(temp_statement.me(), 0), string_size);
            return false; break;

        default:
           break;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_get_blob(sqlite3 *db, const char *query, void* &output, int &output_size ) {

    sinsql_statement temp_statement(db, query);

    switch ( temp_statement.step() ) {
        case SQLITE_DONE:
            //we don't want this! we want a result :( ah well, return error
            output = NULL;
            return true; break;

        case SQLITE_ROW:
            //make sure its a blob
            if ( sqlite3_column_type(temp_statement.me(),0) != SQLITE_BLOB ) {
                //not a blob, return error
                output = NULL; output_size = -1;
                return true; break;
            }
            //grab the result
            output_size = sqlite3_column_bytes(temp_statement.me(),0);
            output = (void*)malloc(output_size);
            memcpy(output, sqlite3_column_blob(temp_statement.me(), 0), output_size);
            return false; break;

        default:
            break;
    }
    return true;
}


///////////////////////////////////////////////////////////////////////////////
//
bool sinsql_open_db(const char *db_name, sqlite3* &db ) {

    int rc;

    rc = sqlite3_open(db_name, &db);
    switch ( rc ) {
        case SQLITE_OK:
            //everything is fine
            return false; break;
        default:
            //freak out!
            throw (sinsql_exception("sinsql_open_db",sqlite3_errmsg(db),rc));
            break;
    }
}

