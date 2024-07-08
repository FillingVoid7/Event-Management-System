#include "Login.h"
#include "Database.h"
#include <iostream>
#include <string>

using namespace std;

int loginUser() {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter Password: ";
    cin >> password;

    sqlite3* db = openDatabase();
    if (!db) return -1;

    const char* errMsg = nullptr;
    string query = "SELECT userID FROM user_data WHERE userName = ? AND userPassword = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int userID = -1;
    if (rc == SQLITE_ROW) {
        userID = sqlite3_column_int(stmt, 0);
        cout << "\033[32mLogin successful\n \033[0m\n";         // ANSI escape code for green color
       
    } else {
        cout << "Invalid username or password.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return userID;
}

int loginAdmin() {
    string adminName, adminPassword;
    cout << "Enter Admin Username: ";
    cin >> adminName;
    cout << "Enter Admin Password: ";
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
    int userID = -1;
    if (rc == SQLITE_ROW) {
        userID = sqlite3_column_int(stmt, 0);              // ANSI escape code for green color
        cout << "\033[32mLogin successful. \033[0m\n";     //cout << "Login successful. User ID: " << userID << endl;
    } else {
         cout << "\033[31mInvalid username or password\033[0m\n";           // ANSI escape code for red color
        return -1;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return userID;
}
