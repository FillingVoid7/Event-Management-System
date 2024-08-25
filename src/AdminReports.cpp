#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sqlite3.h>
#include <Database.h>
#include <algorithm> // For count_if

using namespace std;

struct EventNode {
    int eventID;
    string eventName;
    string eventDuration;
    string eventDate;
    string eventDescription;
    string eventCategory;
    string eventLocation;
    int adminID;
    EventNode* prev;
    EventNode* next;
};

struct UserActivityNode {
    int regID;
    int eventID;
    string eventLocation;
    string username;
    UserActivityNode* prev;
    UserActivityNode* next;
};

void addEventNode(EventNode*& head, EventNode*& tail, int eventID, const string& eventName, const string& eventDuration,
                  const string& eventDate, const string& eventDescription, const string& eventCategory,
                  const string& eventLocation, int adminID) {
    EventNode* newNode = new EventNode{eventID, eventName, eventDuration, eventDate, eventDescription, eventCategory, eventLocation, adminID, nullptr, nullptr};

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}


void addUserActivityNode(UserActivityNode*& head, UserActivityNode*& tail, int regID, int eventID, const string& eventLocation,
                         const string& username) {
    UserActivityNode* newNode = new UserActivityNode{regID, eventID, eventLocation, username, nullptr, nullptr};
    
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

bool validateDate(const string& date) {
    regex datePattern("\\d{4}-\\d{2}-\\d{2}");
    return regex_match(date, datePattern);
}

bool validateStringLength(const string& input, int minLength, int maxLength) {
    int wordCount = count_if(input.begin(), input.end(), [](char c) { return c == ' '; }) + 1;
    return wordCount >= minLength && wordCount <= maxLength;
}

string getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buf);
}

void generateEventReport(int eventID) {
    string fileName = "EventReport_" + to_string(eventID) + ".txt";
    ifstream inFile(fileName);

    if (inFile.good()) {
        cout << "Event report already generated.\n";
        return;
    }
    inFile.close();

    sqlite3* db = openDatabase();
    if (!db) return;

    EventNode* head = nullptr;
    EventNode* tail = nullptr;

    string query = "SELECT eventID, eventName, eventDuration, eventDate, eventDescription, eventCategory, eventLocation, adminID "
                   "FROM events WHERE eventID = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    if (sqlite3_bind_int(stmt, 1, eventID) != SQLITE_OK) {
        cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        addEventNode(head, tail,
                     sqlite3_column_int(stmt, 0),
                     reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                     reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                     reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)),
                     reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)),
                     reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)),
                     reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)),
                     sqlite3_column_int(stmt, 7));
    } else {
        cerr << "No event found with ID " << eventID << endl;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        cerr << "Error executing query: " << sqlite3_errmsg(db) << endl;
    }

    ofstream outFile(fileName);
    if (outFile.is_open()) {
        EventNode* temp = head;
        while (temp) {
            outFile << "Event Report for Event ID " << temp->eventID << ":\n";
            outFile << "Event Name: " << temp->eventName << "\n";
            outFile << "Event Duration: " << temp->eventDuration << "\n";
            outFile << "Event Date: " << temp->eventDate << "\n";
            outFile << "Event Description: " << temp->eventDescription << "\n";
            outFile << "Event Category: " << temp->eventCategory << "\n";
            outFile << "Event Location: " << temp->eventLocation << "\n";
            outFile << "Created By (Admin ID): " << temp->adminID << "\n";
            outFile << "Report Date: " << getCurrentDate() << "\n";
            temp = temp->next;
        }
        outFile.close();
        cout << "Event report generated successfully.\n";
    } else {
        cerr << "Failed to open file for writing: " << fileName << endl;
    }

    while (head) {
        EventNode* temp = head;
        head = head->next;
        delete temp;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void generateUserActivityReport(int userID) {
    string fileName = "UserActivityReport_" + to_string(userID) + ".txt";
    ifstream inFile(fileName);

    if (inFile.good()) {
        cout << "User activity report already generated.\n";
        return;
    }
    inFile.close(); 

    sqlite3* db = openDatabase();
    if (!db) return;

    UserActivityNode* head = nullptr;
    UserActivityNode* tail = nullptr;

    string query = "SELECT er.regID, e.eventID, e.eventLocation, u.userName "
                   "FROM event_registrations er "
                   "INNER JOIN events e ON er.eventID = e.eventID "
                   "INNER JOIN user_data u ON er.userID = u.userID "
                   "WHERE er.userID = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    if (sqlite3_bind_int(stmt, 1, userID) != SQLITE_OK) {
        cerr << "Failed to bind parameter: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    while (true) {
        int result = sqlite3_step(stmt);
        if (result == SQLITE_ROW) {
            addUserActivityNode(head, tail,
                                sqlite3_column_int(stmt, 0),
                                sqlite3_column_int(stmt, 1),
                                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)),
                                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
        } else if (result == SQLITE_DONE) {
            break; 
        } else {
            cerr << "Error executing query: " << sqlite3_errmsg(db) << endl;
            break;
        }
    }

    ofstream outFile(fileName);
    if (outFile.is_open()) {
        UserActivityNode* temp = head;
        while (temp) {
            outFile << "User Activity Report for User ID " << userID << ":\n";
            outFile << "Registration ID: " << temp->regID << "\n";
            outFile << "Event ID: " << temp->eventID << "\n";
            outFile << "Event Location: " << temp->eventLocation << "\n";
            outFile << "Username: " << temp->username << "\n";
            temp = temp->next;
        }
        outFile.close();
        cout << "User activity report generated successfully.\n";
    } else {
        cerr << "Failed to open file for writing: " << fileName << endl;
    }

    while (head) {
        UserActivityNode* temp = head;
        head = head->next;
        delete temp;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
