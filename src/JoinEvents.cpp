#include "JoinEvents.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std ; 


void browseEvents() {
    sqlite3* db = openDatabase();
    string query = "SELECT * FROM events";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Duration: " << sqlite3_column_text(stmt, 2) << "\n"; // Changed to eventDuration
        cout << "Event Date: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 6) << "\n"; // Added eventLocation
        cout << "--------------------------\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void browseEventsByCategory() {
    string category;
    cout << "Enter Event Category to browse: ";
    cin.ignore();
    getline(cin, category);

    sqlite3* db = openDatabase();

    string query = "SELECT * FROM events WHERE eventCategory = '" + category + "'";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Duration: " << sqlite3_column_text(stmt, 2) << "\n"; // Changed to eventDuration
        cout << "Event Date: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 6) << "\n"; // Added eventLocation
        cout << "--------------------------\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}



void joinEvent(int userID) {
    int eventID;
    cout << "Enter Event ID to join: ";
    cin >> eventID;

    sqlite3* db = openDatabase();


    string query = "INSERT INTO event_registrations (userID, eventID) VALUES (" + to_string(userID) + ", " + to_string(eventID) + ")";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Successfully joined the event.\n";
    sqlite3_close(db);
}

void joinEventByCategory(int userID) {
    string category;
    cout << "Enter Event Category to join: ";
    cin.ignore();
    getline(cin, category);

    browseEventsByCategory();

    int eventID;
    cout << "Enter Event ID to join: ";
    cin >> eventID;

    sqlite3* db = openDatabase();


    string query = "INSERT INTO event_registrations (userID, eventID) VALUES (" + to_string(userID) + ", " + to_string(eventID) + ")";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Successfully joined the event.\n";
    sqlite3_close(db);
}

void cancelEventRegistration(int userID) {
    int eventID;
    cout << "Enter Event ID to cancel registration: ";
    cin >> eventID;

    sqlite3* db = openDatabase();


    string query = "DELETE FROM event_registrations WHERE userID = " + to_string(userID) + " AND eventID = " + to_string(eventID);
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Successfully canceled the registration.\n";
    sqlite3_close(db);
}

void listJoinedEvents(int userID) {
    sqlite3* db = openDatabase();

    string query = "SELECT e.eventID, e.eventName, e.eventDuration, e.eventDate, e.eventDescription, e.eventCategory, e.eventLocation "
                   "FROM events e INNER JOIN event_registrations er ON e.eventID = er.eventID WHERE er.userID = " + to_string(userID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Duration: " << sqlite3_column_text(stmt, 2) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 6) << "\n"; // Display eventLocation
        cout << "--------------------------\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


