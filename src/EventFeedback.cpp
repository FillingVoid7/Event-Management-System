#include "EventFeedback.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std ; 

void provideFeedback(int userID, int eventID) {
    string feedback;
    cout << "Enter your feedback: ";
    cin.ignore();
    getline(cin, feedback);

    sqlite3* db = openDatabase();

    string query = "INSERT INTO feedback (userID, eventID, feedback) VALUES (" + to_string(userID) + ", " + to_string(eventID) + ", '" + feedback + "')";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Feedback submitted successfully.\n";
    sqlite3_close(db);
}

void viewFeedback(int eventID) {
    sqlite3* db = openDatabase();

    string query = "SELECT userID, feedback FROM feedback WHERE eventID = " + to_string(eventID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    cout << "Feedback for Event ID " << eventID << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "User ID: " << sqlite3_column_int(stmt, 0) << " - ";
        cout << "Feedback: " << sqlite3_column_text(stmt, 1) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
