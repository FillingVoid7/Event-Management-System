#include "Database.h"
#include <sqlite3.h>
#include <iostream>
using namespace std;
sqlite3* openDatabase() {
    sqlite3* db;
    int rc = sqlite3_open("event_management.db", &db);
    if (rc) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return nullptr;
    }
    return db;
}

void initializeDatabase() {
    sqlite3* db = openDatabase();
    if (!db) return;

    const char* userTableSQL = R"(
        CREATE TABLE IF NOT EXISTS user_data (
            userID INTEGER PRIMARY KEY AUTOINCREMENT,
            userName TEXT NOT NULL,
            userPassword TEXT NOT NULL
        );
    )";

    const char* adminTableSQL = R"(
        CREATE TABLE IF NOT EXISTS admin_data (
            adminID INTEGER PRIMARY KEY AUTOINCREMENT,
            adminName TEXT NOT NULL,
            adminPassword TEXT NOT NULL
        );
    )";

    const char* eventTableSQL = R"(
        CREATE TABLE IF NOT EXISTS events (
            eventID INTEGER PRIMARY KEY AUTOINCREMENT,
            eventName TEXT NOT NULL,
            eventDescription TEXT,
            eventDate TEXT NOT NULL,
            eventLocation TEXT NOT NULL UNIQUE,
            eventOwner INTEGER,
            FOREIGN KEY(eventOwner) REFERENCES user_data(userID)
        );
    )";

    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, userTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, adminTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, eventTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}
