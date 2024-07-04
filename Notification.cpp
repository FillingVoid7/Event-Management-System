#include "Notification.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std ; 

void addNotification(int userID, const string& message) {
    sqlite3* db = openDatabase();

    string query = "INSERT INTO notifications (userID, message) VALUES (" + to_string(userID) + ", '" + message + "')";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Notification added successfully.\n";
    sqlite3_close(db);
}


void viewNotifications(int userID) {
    sqlite3* db = openDatabase();

    string query = "SELECT message FROM notifications WHERE userID = " + to_string(userID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    cout << "Notifications for User ID " << userID << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Message: " << sqlite3_column_text(stmt, 0) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
