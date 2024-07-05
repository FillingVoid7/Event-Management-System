#include "AdminReports.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>


using namespace std ; 

void generateEventReport(int eventID) {
    sqlite3* db = openDatabase();

    string query = "SELECT * FROM events WHERE eventID = " + to_string(eventID);
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Event Report for Event ID " << eventID << ":\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Schedule: " << sqlite3_column_text(stmt, 2) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 6) << "\n"; // Assuming eventLocation is at column index 6
        cout << "Created By: " << sqlite3_column_int(stmt, 7) << "\n"; // Assuming creatorUserID is at column index 7
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void generateUserActivityReport(int userID) {
    sqlite3* db = openDatabase();

    string query = "SELECT er.registrationID, e.eventID, e.eventLocation "
                   "FROM event_registrations er "
                   "INNER JOIN events e ON er.eventID = e.eventID "
                   "WHERE er.userID = " + to_string(userID);

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    cout << "User Activity Report for User ID " << userID << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Registration ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event ID: " << sqlite3_column_int(stmt, 1) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 2) << "\n"; // Event location retrieved
        cout << "--------------------------\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
