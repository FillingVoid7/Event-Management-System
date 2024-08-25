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
        cout << "Event Location: " << sqlite3_column_text(stmt, 2) << "\n"; // Changed to eventDuration
        cout << "Event Duration: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 6) << "\n"; // Added eventLocation
        cout << "--------------------------\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void browseEventsByCategory() {
    browseEvents();
    string category;
    cout << "Enter Event Category to browse: ";
    cin.ignore();
    getline(cin, category);

    sqlite3* db = openDatabase();

    string query = "SELECT * FROM events WHERE eventCategory = '" + category + "'";
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    bool eventFound = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        eventFound = true;
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 2) << "\n"; 
        cout << "Event Duration: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 6) << "\n"; 
        cout << "--------------------------\n";
    }

    if (!eventFound) {
        cout << "No events found for the category: " << category << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}



void joinEvent(int userID) {
    browseEvents();
    int eventID;
    cout << "Enter Event ID to join: ";
    cin >> eventID;

    sqlite3* db = openDatabase();

    string checkQuery = "SELECT COUNT(*) FROM event_registrations WHERE userID = " + to_string(userID) + " AND eventID = " + to_string(eventID);
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &checkStmt, nullptr);

    sqlite3_step(checkStmt);
    int count = sqlite3_column_int(checkStmt, 0);
    sqlite3_finalize(checkStmt);

    if (count > 0) {
        cout << "You have already joined the event.\n";
        sqlite3_close(db);
        return;
    }

    string insertQuery = "INSERT INTO event_registrations (userID, eventID) VALUES (" + to_string(userID) + ", " + to_string(eventID) + ")";
    sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, nullptr);

    cout << "Successfully joined the event.\n";
    sqlite3_close(db);
}




void joinEventByCategory(int userID) {
    browseEvents();
    string category;
    cout << "Enter Event Category to join: ";
    cin.ignore();
    getline(cin, category);

    sqlite3* db = openDatabase();

    string query = "SELECT * FROM events WHERE eventCategory = '" + category + "'";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    bool eventFound = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        eventFound = true;
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 2) << "\n"; 
        cout << "Event Duration: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 6) << "\n";
        cout << "--------------------------\n";
    }

    if (!eventFound) {
        cout << "No events found for the category: " << category << "\n";
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    string checkQuery = "SELECT COUNT(*) FROM event_registrations er "
                        "INNER JOIN events e ON er.eventID = e.eventID "
                        "WHERE er.userID = " + to_string(userID) + " AND e.eventCategory = '" + category + "'";
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &checkStmt, nullptr);

    sqlite3_step(checkStmt);
    int count = sqlite3_column_int(checkStmt, 0);
    sqlite3_finalize(checkStmt);

    if (count > 0) {
        cout << "You have already joined an event in the given category.\n";
        sqlite3_close(db);
        return;
    }

    int eventID;
    cout << "Enter Event ID to join: ";
    cin >> eventID;

    string insertQuery = "INSERT INTO event_registrations (userID, eventID) VALUES (" + to_string(userID) + ", " + to_string(eventID) + ")";
    sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, nullptr);

    cout << "Successfully joined the event.\n";
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}





void cancelEventRegistration(int userID) {
    browseEvents();
    int eventID;
    cout << "Enter Event ID to cancel registration: ";
    cin >> eventID;

    sqlite3* db = openDatabase();

    string checkQuery = "SELECT COUNT(*) FROM event_registrations WHERE userID = " + to_string(userID) + " AND eventID = " + to_string(eventID);
    sqlite3_stmt* checkStmt;
    sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &checkStmt, nullptr);

    sqlite3_step(checkStmt);
    int count = sqlite3_column_int(checkStmt, 0);
    sqlite3_finalize(checkStmt);

    if (count == 0) {
        cout << "You have already canceled the registration or you were not registered for this event.\n";
        sqlite3_close(db);
        return;
    }

    string query = "DELETE FROM event_registrations WHERE userID = " + to_string(userID) + " AND eventID = " + to_string(eventID);
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Successfully canceled the registration.\n";
    sqlite3_close(db);
}




void listJoinedEvents(int userID) {
    sqlite3* db = openDatabase();

    string query = "SELECT e.eventID, e.eventName, e.eventLocation, e.eventDuration, e.eventDate, e.eventDescription, e.eventCategory "
                   "FROM events e INNER JOIN event_registrations er ON e.eventID = er.eventID WHERE er.userID = " + to_string(userID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    bool eventFound = false; 

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        eventFound = true;
        cout << "Event ID: " << sqlite3_column_int(stmt, 0) << "\n";
        cout << "Event Name: " << sqlite3_column_text(stmt, 1) << "\n";
        cout << "Event Location: " << sqlite3_column_text(stmt, 2) << "\n"; 
        cout << "Event Duration: " << sqlite3_column_text(stmt, 3) << "\n";
        cout << "Event Date: " << sqlite3_column_text(stmt, 4) << "\n";
        cout << "Event Description: " << sqlite3_column_text(stmt, 5) << "\n";
        cout << "Event Category: " << sqlite3_column_text(stmt, 6) << "\n"; 
        cout << "--------------------------\n";
    }

    if (!eventFound) {
        cout << "You haven't joined any events.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}



