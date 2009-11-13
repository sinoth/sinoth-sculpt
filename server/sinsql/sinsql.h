#include <exception>
#include <string>
#include <sqlite3.h>


///////////////////////////////////////////////////////////////////////////////
// sql exceptions yay
//
class sinsql_exception: public std::exception {
public:
    sinsql_exception(const std::string& in_msg, const std::string& in_db_msg, int in_rc) throw()
        { msg = in_msg; db_msg = in_db_msg; rc = in_rc; }
    ~sinsql_exception() throw() {}
    //const char* what() { return msg.c_str(); }
    const char* getMsg() { return msg.c_str(); }
    const char* getDBMsg() { return db_msg.c_str(); }
    int getRC() { return rc; }
private:
    int rc;
    std::string msg;
    std::string db_msg;
};


///////////////////////////////////////////////////////////////////////////////
// statement class for RAII magic
//
class sinsql_statement {
public:
    sinsql_statement(sqlite3 *db, const char *query);
    ~sinsql_statement() throw();
    sqlite3_stmt* me() { return my_statement; }
    int step();
    void reset() { sqlite3_reset(my_statement); }
private:
    int rc;
    sqlite3_stmt *my_statement;
    sqlite3 *my_db;
};


///////////////////////////////////////////////////////////////////////////////
// sqlite helper functions
//
bool sinsql_existence(sqlite3 *db, const char *query);
bool sinsql_exec(sqlite3 *db, const char *query);
bool sinsql_get_text(sqlite3 *db, const char *query, char* &result );
bool sinsql_get_int(sqlite3 *db, const char *query, int &result);
bool sinsql_get_blob(sqlite3 *db, const char *query, void* &result, int &result_size);
bool sinsql_open_db(const char *db_name, sqlite3* &db );
