#include "CreateUserAccount.h"
#include "Database.h"
#include <iostream>
#include <string>

using namespace std;

void createUserAccount() {
    string userName, userPassword;
    cout << "Enter Username: ";
    cin >> userName;
    cout << "Enter Password: ";
    cin >> userPassword;

    sqlite3* db = openDatabase();

    string sql = "INSERT INTO user_data (userName, userPassword) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, userPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        // cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        cout <<"Username already exists !" <<endl;  
    } else {
        cout << "User account created successfully." << endl;
    }

    sqlite3_finalize(stmt);
     sqlite3_close(db);
}

void createAdminAccount() {
    string adminName, adminPassword;
    cout << "Enter Admin Username: ";
    cin >> adminName;
    cout << "Enter Password: ";
    cin >> adminPassword;

    sqlite3* db = openDatabase();

    string sql = "INSERT INTO admin_data (adminName, adminPassword) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, adminName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, adminPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        // cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        cout <<"Username already exists !" <<endl;  

    } else {
        cout << "Admin account created successfully." << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
