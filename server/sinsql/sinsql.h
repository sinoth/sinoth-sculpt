
#include <sqlite3.h>

bool sinsql_existence(sqlite3 *db, const char *query) throw (int);
bool sinsql_exec(sqlite3 *db, const char *query) throw (int);
bool sinsql_get_text(sqlite3 *db, const char *query, char* &result ) throw (int);
bool sinsql_get_int(sqlite3 *db, const char *query, int &result) throw (int);
bool sinsql_get_blob(sqlite3 *db, const char *query, void* &result, int &result_size) throw (int);
bool sinsql_open_db(const char *db_name, sqlite3* &db ) throw (int);
bool sinsql_stmt_prep(sqlite3 *db, const char *query, sqlite3_stmt* &statement) throw (int);
bool sinsql_stmt_step(sqlite3_stmt* &statement) throw (int);
bool sinsql_stmt_fin(sqlite3_stmt* &statement) throw (int);
