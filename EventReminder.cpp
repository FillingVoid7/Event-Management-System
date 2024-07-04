#include "EventReminder.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std ; 

void setEventReminder(int userID, int eventID) {
    sqlite3* db = openDatabase();

    string query = "INSERT INTO reminders (userID, eventID) VALUES (" + to_string(userID) + ", " + to_string(eventID) + ")";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Event reminder set successfully.\n";
    sqlite3_close(db);
}

void viewEventReminders(int userID) {
    sqlite3* db = openDatabase();

    string query = "SELECT e.eventID, e.eventName, e.eventDate FROM events e INNER JOIN reminders r ON e.eventID = r.eventID WHERE r.userID = " + to_string(userID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    cout << "Event Reminders for User ID " << userID << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 2) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
