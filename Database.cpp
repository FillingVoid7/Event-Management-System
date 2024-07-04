#include "Database.h"
#include <sqlite3.h>
#include <iostream>

sqlite3* openDatabase() {
    sqlite3* db;
    int rc = sqlite3_open("event_management.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return nullptr;
    }
    return db;
}
