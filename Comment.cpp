#include "Comment.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std ; 

void addComment(int userID, int eventID) {
    string comment;
    cout << "Enter your comment: ";
    cin.ignore();
    getline(cin, comment);

    sqlite3* db = openDatabase();


    string query = "INSERT INTO comments (userID, eventID, comment) VALUES (" + to_string(userID) + ", " + to_string(eventID) + ", '" + comment + "')";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Comment added successfully.\n";
    sqlite3_close(db);
}


void viewComments(int eventID) {
    sqlite3* db = openDatabase();

    string query = "SELECT userID, comment FROM comments WHERE eventID = " + to_string(eventID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    cout << "Comments for Event ID " << eventID << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "User ID: " << sqlite3_column_int(stmt, 0) << " - ";
        cout << "Comment: " << sqlite3_column_text(stmt, 1) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
