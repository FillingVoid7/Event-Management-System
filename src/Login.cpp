#include "Login.h"
#include "Database.h"
#include "HashInputPassword.h"
#include "PasswordField.h"
#include <iostream>
#include <sodium.h>
#include <sqlite3.h>

using namespace std;

bool verifyPassword(const string& password, const string& hash) {
    return crypto_pwhash_str_verify(hash.c_str(), password.c_str(), password.length()) == 0;
}

int loginUser() {
    string username;
    cout << "Enter Username: ";
    cin >> username;

    PasswordField pf(20); 
    string password = pf.getline(); 

    sqlite3* db = openDatabase();
    if (!db) {
        cerr << "Failed to open database." << endl;
        return -1;
    }

    string query = "SELECT userID, userPassword FROM user_data WHERE userName = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int userID = -1;
    if (rc == SQLITE_ROW) {
        string storedHash(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        if (verifyPassword(password, storedHash)) {
            userID = sqlite3_column_int(stmt, 0);
            cout << "\033[32mLogin successful\033[0m" << endl;
        } else {
            cout << "Invalid username or password." << endl;
        }
    } else {
        cout << "Invalid username or password." << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return userID;
}

int loginAdmin() {
    string adminName;
    cout << "Enter Admin Username: ";
    cin >> adminName;

    PasswordField pf(20);
    string adminPassword = pf.getline(); 

    sqlite3* db = openDatabase();
    if (!db) {
        cerr << "Failed to open database." << endl;
        return -1;
    }

    string sql = "SELECT adminID, adminPassword FROM admin_data WHERE adminName = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, adminName.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int userID = -1;
    if (rc == SQLITE_ROW) {
        string storedHash(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        if (verifyPassword(adminPassword, storedHash)) {
            userID = sqlite3_column_int(stmt, 0);
            cout << "\033[32mLogin successful.\033[0m" << endl;
        } else {
            cout << "\033[31mInvalid username or password\033[0m" << endl;
        }
    } else {
        cout << "\033[31mInvalid username or password\033[0m" << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return userID;
}
