#include "EventSearch.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std ; 


void searchEventByName() {
    string eventName;
    cout << "Enter Event Name to search: ";
    cin.ignore();
    getline(cin, eventName);

    sqlite3* db = openDatabase();

    string query = "SELECT * FROM events WHERE eventName LIKE '%" + eventName + "%'";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Schedule: " << sqlite3_column_text(stmt, 2) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 6) << "\n"; // Include eventLocation
        cout << "--------------------------\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void searchEventByDate() {
    string eventDate;
    cout << "Enter Event Date (YYYY-MM-DD) to search: ";
    cin.ignore();
    getline(cin, eventDate);

    sqlite3* db = openDatabase();

    string query = "SELECT * FROM events WHERE eventDate = '" + eventDate + "'";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Schedule: " << sqlite3_column_text(stmt, 2) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 6) << "\n"; // Include eventLocation
        cout << "--------------------------\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
