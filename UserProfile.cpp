#include "UserProfile.h"
#include "Database.h"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

void changeUserProfile(int userID) {
    string currentUsername, currentPassword;
    cout << "Enter current Username: ";
    cin >> currentUsername;
    cout << "Enter current Password: ";
    cin >> currentPassword;

    sqlite3* db = openDatabase();
    if (!db) {
        cerr << "Cannot open database.\n";
        return;
    }

    string query = "SELECT userName, userPassword FROM user_data WHERE userID = ?";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, userID);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        string dbUsername = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        string dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

        if (currentUsername == dbUsername && currentPassword == dbPassword) {
            sqlite3_finalize(stmt);
            
            int choice;
            cout << "Do you want to change (1) Username or (2) Password? Enter 1 or 2: ";
            cin >> choice;

            if (choice == 1) {
                string newUserName;
                cout << "Enter new Username: ";
                cin >> newUserName;

                query = "UPDATE user_data SET userName = ? WHERE userID = ?";
                rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                    return;
                }

                sqlite3_bind_text(stmt, 1, newUserName.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 2, userID);

                rc = sqlite3_step(stmt);
                if (rc != SQLITE_DONE) {
                    cerr << "Error updating username: " << sqlite3_errmsg(db) << endl;
                } else {
                    cout << "Username updated successfully.\n";
                }
                sqlite3_finalize(stmt);
            } else if (choice == 2) {
                string newUserPassword;
                cout << "Enter new Password: ";
                cin >> newUserPassword;

                query = "UPDATE user_data SET userPassword = ? WHERE userID = ?";
                rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
                if (rc != SQLITE_OK) {
                    cerr << "Error preparing statement: " << sqlite3_errmsg(db) << endl;
                    sqlite3_close(db);
                    return;
                }

                sqlite3_bind_text(stmt, 1, newUserPassword.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(stmt, 2, userID);

                rc = sqlite3_step(stmt);
                if (rc != SQLITE_DONE) {
                    cerr << "Error updating password: " << sqlite3_errmsg(db) << endl;
                } else {
                    cout << "Password updated successfully.\n";
                }
                sqlite3_finalize(stmt);
            } else {
                cout << "Invalid choice.\n";
            }
        } else {
            cout << "Incorrect current username or password.\n";
        }
    } else {
        cout << "Error verifying user: no rows found.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
