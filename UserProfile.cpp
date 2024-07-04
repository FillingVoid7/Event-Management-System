#include "UserProfile.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

void updateUserProfile(int userID) {
    string newUsername;
    cout << "Enter new Username: ";
    cin >> newUsername;

    sqlite3* db = openDatabase();
    const char* errMsg = nullptr;

    string query = "UPDATE user_data SET userName = ? WHERE userID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, newUsername.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, userID);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Error updating username: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Username updated successfully.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void changeUserPassword(int userID) {
    string newPassword;
    cout << "Enter new Password: ";
    cin >> newPassword;

    sqlite3* db = openDatabase();
    const char* errMsg = nullptr;

    string query = "UPDATE user_data SET userPassword = ? WHERE userID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, userID);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cerr << "Error updating password: " << sqlite3_errmsg(db) << endl;
    } else {
        cout << "Password updated successfully.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
