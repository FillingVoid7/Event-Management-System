// Database.h
#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

void initializeDatabase();

sqlite3* openDatabase();

#endif // DATABASE_H
