#include "Database.h"
#include <sqlite3.h>
#include <iostream>
#include <string>

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

    const char* dropTablesSQL = R"(
        DROP TABLE IF EXISTS admin_data;
        DROP TABLE IF EXISTS user_data;
        DROP TABLE IF EXISTS events;
        DROP TABLE IF EXISTS event_registrations;
        DROP TABLE IF EXISTS comments;
        DROP TABLE IF EXISTS feedback;
        DROP TABLE IF EXISTS reminders;
        DROP TABLE IF EXISTS admin_reports;
    )";

    const char* adminTableSQL = R"(
        CREATE TABLE IF NOT EXISTS admin_data (
            adminID INTEGER PRIMARY KEY AUTOINCREMENT,
            adminName TEXT NOT NULL,
            adminPassword TEXT NOT NULL
        );
    )";

    const char* userTableSQL = R"(
        CREATE TABLE IF NOT EXISTS user_data (
            userID INTEGER PRIMARY KEY AUTOINCREMENT,
            userName TEXT NOT NULL,
            userPassword TEXT NOT NULL
        );
    )";

    const char* eventsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS events (
            eventID INTEGER PRIMARY KEY AUTOINCREMENT,
            eventName TEXT NOT NULL,
            eventLocation TEXT UNIQUE NOT NULL,
            eventDuration TEXT NOT NULL,  
            eventDate TEXT NOT NULL,
            eventDescription TEXT NOT NULL,
            eventCategory TEXT NOT NULL,
            createdBy INTEGER NOT NULL,
            FOREIGN KEY(createdBy) REFERENCES admin_data(adminID)
        );
    )";

    const char* eventRegistrationsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS event_registrations (
            regID INTEGER PRIMARY KEY AUTOINCREMENT,
            userID INTEGER NOT NULL,
            eventID INTEGER NOT NULL,
            FOREIGN KEY(userID) REFERENCES user_data(userID),
            FOREIGN KEY(eventID) REFERENCES events(eventID)
        );
    )";

    const char* commentsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS comments (
            commentID INTEGER PRIMARY KEY AUTOINCREMENT,
            userID INTEGER NOT NULL,
            eventID INTEGER NOT NULL,
            commentText TEXT NOT NULL,
            commentDate TEXT NOT NULL,
            FOREIGN KEY(userID) REFERENCES user_data(userID),
            FOREIGN KEY(eventID) REFERENCES events(eventID)
        );
    )";

    const char* feedbackTableSQL = R"(
        CREATE TABLE IF NOT EXISTS feedback (
            feedbackID INTEGER PRIMARY KEY AUTOINCREMENT,
            userID INTEGER NOT NULL,
            eventID INTEGER NOT NULL,
            feedbackText TEXT NOT NULL,
            feedbackDate TEXT NOT NULL,
            FOREIGN KEY(userID) REFERENCES user_data(userID),
            FOREIGN KEY(eventID) REFERENCES events(eventID)
        );
    )";

    const char* remindersTableSQL = R"(
        CREATE TABLE IF NOT EXISTS reminders (
            reminderID INTEGER PRIMARY KEY AUTOINCREMENT,
            userID INTEGER NOT NULL,
            eventID INTEGER NOT NULL,
            reminderDate TEXT NOT NULL,
            FOREIGN KEY(userID) REFERENCES user_data(userID),
            FOREIGN KEY(eventID) REFERENCES events(eventID)
        );
    )";

    const char* adminReportsTableSQL = R"(
        CREATE TABLE IF NOT EXISTS admin_reports (
            reportID INTEGER PRIMARY KEY AUTOINCREMENT,
            reportType TEXT NOT NULL,
            reportDate TEXT NOT NULL,
            generatedBy INTEGER NOT NULL,
            FOREIGN KEY(generatedBy) REFERENCES admin_data(adminID)
        );
    )";

    char* errMsg = nullptr;

    int rc = sqlite3_exec(db, dropTablesSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error dropping tables: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    
    rc = sqlite3_exec(db, adminTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating admin_data table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, userTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating user_data table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, eventsTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating events table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, eventRegistrationsTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating event_registrations table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, commentsTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating comments table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, feedbackTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating feedback table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, remindersTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating reminders table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    rc = sqlite3_exec(db, adminReportsTableSQL, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error creating admin_reports table: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);
}
