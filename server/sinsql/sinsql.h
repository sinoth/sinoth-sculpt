
#include <sqlite3.h>

bool sinsql_existence(sqlite3 *db, const char *query) throw (int);
bool sinsql_get_text(sqlite3 *db, const char *query, char* &result ) throw (int);
bool sinsql_get_int(sqlite3 *db, const char *query, int &result) throw (int);
bool sinsql_get_blob(sqlite3 *db, const char *query, unsigned char* &result, int &result_size) throw (int);
bool sinsql_exec(sqlite3 *db, const char *query) throw (int);
