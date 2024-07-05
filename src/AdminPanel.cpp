#include "AdminPanel.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;


void createEvent() {
    sqlite3* db = openDatabase();
    string eventName, eventSchedule, eventDescription, eventCategory;
    string eventDate;
    int createdBy;

    cout << "Enter Event Name: ";
    cin.ignore();
    getline(cin, eventName);
    cout << "Enter Event Schedule: ";
    getline(cin, eventSchedule);
    cout << "Enter Event Date (YYYY-MM-DD): ";
    getline(cin, eventDate);
    cout << "Enter Event Description: ";
    getline(cin, eventDescription);
    cout << "Enter Event Category: ";
    getline(cin, eventCategory);
    cout << "Enter Creator Admin ID: ";
    cin >> createdBy;

    string query = "INSERT INTO events (eventName, eventSchedule, eventDate, eventDescription, eventCategory, createdBy) VALUES ('" +
                        eventName + "', '" + eventSchedule + "', '" + eventDate + "', '" + eventDescription + "', '" + eventCategory + "', " + to_string(createdBy) + ")";
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Event created successfully.\n";
    sqlite3_close(db);
}

void editEvent() {
    int eventID;
    string eventName, eventSchedule, eventDescription, eventCategory;
    string eventDate;

    cout << "Enter Event ID to edit: ";
    cin >> eventID;
    cout << "Enter new Event Name: ";
    cin.ignore();
    getline(cin, eventName);
    cout << "Enter new Event Schedule: ";
    getline(cin, eventSchedule);
    cout << "Enter new Event Date (YYYY-MM-DD): ";
    getline(cin, eventDate);
    cout << "Enter new Event Description: ";
    getline(cin, eventDescription);
    cout << "Enter new Event Category: ";
    getline(cin, eventCategory);

    sqlite3* db = openDatabase();

    string query = "UPDATE events SET eventName = '" + eventName + "', eventSchedule = '" + eventSchedule + "', eventDate = '" + eventDate + "', eventDescription = '" + eventDescription + "', eventCategory = '" + eventCategory + "' WHERE eventID = " + to_string(eventID);
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Event updated successfully.\n";
    sqlite3_close(db);
}

void deleteEvent() {
    int eventID;
    cout << "Enter Event ID to delete: ";
    cin >> eventID;

    sqlite3* db = openDatabase();

    string query = "DELETE FROM events WHERE eventID = " + to_string(eventID);
    sqlite3_exec(db, query.c_str(), nullptr, nullptr, nullptr);

    cout << "Event deleted successfully.\n";
    sqlite3_close(db);
}


void viewEventRegistrations() {
    int eventID;
    cout << "Enter Event ID to view registrations: ";
    cin >> eventID;

    sqlite3* db = openDatabase();

    string query = "SELECT userID FROM event_registrations WHERE eventID = " + to_string(eventID);
    
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    cout << "Users registered for Event ID " << eventID << ":\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "User ID: " << sqlite3_column_int(stmt, 0) << "\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
