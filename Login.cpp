#include "Login.h"
#include "Database.h"
#include <iostream>
#include <string>

using namespace std;

bool loginUser() {
    string userName, userPassword;
    cout << "Enter Username: ";
    cin >> userName;
    cout << "Enter Password: ";
    cin >> userPassword;

    sqlite3* db = openDatabase();

    string sql = "SELECT userID FROM user_data WHERE userName = ? AND userPassword = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, userPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        cout << "Login successful. User ID: " << sqlite3_column_text(stmt, 0) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return true;
    } else {
        cout << "Login failed." << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
}

bool loginAdmin() {
    string adminName, adminPassword;
    cout << "Enter Admin Username: ";
    cin >> adminName;
    cout << "Enter Password: ";
    cin >> adminPassword;

    sqlite3* db = openDatabase();

    string sql = "SELECT adminID FROM admin_data WHERE adminName = ? AND adminPassword = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, adminName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, adminPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        cout << "Login successful. Admin ID: " << sqlite3_column_text(stmt, 0) << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return true;
    } else {
        cout << "Login failed." << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
}
