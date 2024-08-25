#include "CreateUserAccount.h"
#include "Database.h"
#include "HashInputPassword.h"
#include "PasswordField.h"
#include <iostream>
#include <stdexcept>
#include <sqlite3.h>

using namespace std;

void createUserAccount() {
    string userName;
    cout << "Enter Username: ";
    cin >> userName;

    PasswordField pf(20); 
    string userPassword = pf.getline(); 

    string hashedPassword;
    try {
        hashedPassword = hashInputPassword(userPassword);
    } catch (const runtime_error& e) {
        cerr << "Error hashing password: " << e.what() << endl;
        return;
    }

    sqlite3* db = openDatabase();
    if (!db) {
        cerr << "Failed to open database." << endl;
        return;
    }

    string sql = "INSERT INTO user_data (userName, userPassword) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, userName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cout << "User account already exists!" << endl;
    } else {
        cout << "User account created successfully." << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void createAdminAccount() {
    string adminName;
    cout << "Enter Admin Username: ";
    cin >> adminName;

    PasswordField pf(20); 
    string adminPassword = pf.getline(); 

    string hashedPassword;
    try {
        hashedPassword = hashInputPassword(adminPassword);
    } catch (const runtime_error& e) {
        cerr << "Error hashing password: " << e.what() << endl;
        return;
    }

    sqlite3* db = openDatabase();
    if (!db) {
        cerr << "Failed to open database." << endl;
        return;
    }

    string sql = "INSERT INTO admin_data (adminName, adminPassword) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, adminName.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashedPassword.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        cout << "Admin account already exists!" << endl;
    } else {
        cout << "Admin account created successfully." << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
