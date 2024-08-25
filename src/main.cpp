#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <limits>
#include <sys/ioctl.h>
#include <chrono>
#include <thread> 
#include "Database.h"
#include "Login.h"
#include "CreateUserAccount.h"
#include "AdminPanel.h"
#include "JoinEvents.h"
#include "UserProfile.h"
#include "AdminReports.h"
using namespace std;

void showUserMenu(int userId);
void handleUserMenu(int userID);

void showEventsSubMenu();
void handleEventsSubMenu(int userID);

void showProfileSubMenu();
void handleProfileSubMenu(int userID);

void showAdminMenu();
void handleAdminMenu();

void showEventManagementSubMenu();
void handleEventManagementSubMenu();

void showReportsSubMenu();
void handleReportsSubMenu();

int getValidatedChoice(int min, int max);

void showMainMenu();
void handleMainMenu();

void drawCenteredBorder(int width, char borderChar);
int getTerminalWidth();  

int getTerminalWidth() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        return 80;
    }
    return w.ws_col;
}

void centerText(const string& text, char borderChar) {
    int width = getTerminalWidth();
    int len = text.length();
    int pad = (width - len) / 2;
    string border(width, borderChar);
    cout << border << endl;
    cout << string(pad, ' ') << text << string(width - pad - len, ' ') << endl;
    cout << border << endl;
}

void drawCenteredBorder(int width, char borderChar) {
    cout << string(width, borderChar) << endl;
}

void pauseForSeconds(int seconds) {
    this_thread::sleep_for(std::chrono::seconds(seconds));
}

int main() {
    initializeDatabase();
    handleMainMenu();
    return 0;
}

void showUserMenu(int userId) {
    sleep(1);
    cout << "\033[2J\033[H";
    cout << "\033[32m"; 
    centerText("User Menu", '-');
    cout << " UserId: " << userId << endl;
    cout << "1. Events" << endl;
    cout << "2. Profile" << endl;
    cout << "3. Logout" << endl;
    centerText("", '-'); 
    cout << "\033[0m";
    cout << "Enter your choice: ";
}

void handleUserMenu(int userID) {
    while (true) {
        showUserMenu(userID);
        int userChoice = getValidatedChoice(1, 3);

        if (userChoice == 3) break;

        switch (userChoice) {
            case 1:
                handleEventsSubMenu(userID);
                break;
            case 2:
                handleProfileSubMenu(userID);
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

void showEventsSubMenu() {
    sleep(1);
    cout << "\033[2J\033[H";
    cout << "\033[32m"; 
    centerText("Events Menu", '-');
    cout << "1. Browse Events" << endl;
    cout << "2. Join Event" << endl;
    cout << "3. Cancel Registration" << endl;
    cout << "4. View Joined Events" << endl;
    cout << "5. Browse events by Category" << endl;
    cout << "6. Join events by Category" << endl;
    cout << "7. Back" << endl;
    centerText("", '-'); 
    cout << "\033[0m"; 
    cout << "Enter your choice: ";
}

void handleEventsSubMenu(int userID) {
    while (true) {
        showEventsSubMenu();
        int eventChoice = getValidatedChoice(1, 7);

        if (eventChoice == 7) break;

        switch (eventChoice) {
            case 1:
                browseEvents();
                break;
            case 2:
                joinEvent(userID);
                break;
            case 3:
                cancelEventRegistration(userID);
                break;
            case 4:
                listJoinedEvents(userID);
                break;
            case 5:
                browseEventsByCategory();
                break;
            case 6:
                joinEventByCategory(userID);
                break;
            default:
                cout << "Invalid choice.\n";
                continue;
        }
         pauseForSeconds(7); 
    }
}

void showProfileSubMenu() {
    sleep(1);
    cout << "\033[2J\033[H";
    cout << "\033[32m";  
    centerText("Profile Menu", '-');
    cout << "1. Update Profile" << endl;
    cout << "2. Change Password" << endl;
    cout << "3. Back" << endl;
    centerText("", '-'); 
    cout << "\033[0m"; 
    cout << "Enter your choice: ";
}

void handleProfileSubMenu(int userID) {
    while (true) {
        showProfileSubMenu();
        int profileChoice = getValidatedChoice(1, 3);

        if (profileChoice == 3) break;

        switch (profileChoice) {
            case 1:
                updateUserProfile(userID);
                break;
            case 2:
                changeUserPassword(userID);
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

void showAdminMenu() {
    sleep(1);
    cout << "\033[2J\033[H";  
    cout << "\033[32m";
    centerText("Admin Menu", '-');
    cout << "1. Event Management" << endl;
    cout << "2. Reports" << endl;
    cout << "3. Logout" << endl;
    centerText("", '-'); 
    cout << "\033[0m"; 
    cout << "Enter your choice: ";
}

void handleAdminMenu() {
    while (true) {
        showAdminMenu();
        int adminChoice = getValidatedChoice(1, 3);

        if (adminChoice == 3) break;

        switch (adminChoice) {
            case 1:
                handleEventManagementSubMenu();
                break;
            case 2:
                handleReportsSubMenu();
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

void showEventManagementSubMenu() {
    sleep(1);
    cout << "\033[2J\033[H"; 
    cout << "\033[32m"; 
    centerText("Event Management Menu", '-');
    cout << "1. Create Event" << endl;
    cout << "2. Edit Event" << endl;
    cout << "3. Delete Event" << endl;
    cout << "4. View Event Registrations" << endl;
    cout << "5. Back" << endl;
    centerText("", '-'); 
    cout << "\033[0m";  
    cout << "Enter your choice: ";
}

void handleEventManagementSubMenu() {
    while (true) {
        showEventManagementSubMenu();
        int eventManagementChoice = getValidatedChoice(1, 5);

        if (eventManagementChoice == 5) break;

        switch (eventManagementChoice) {
            case 1:
                createEvent();
                break;
            case 2:
                editEvent();
                break;
            case 3:
                deleteEvent();
                break;
            case 4:
                viewEventRegistrations();
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

void showReportsSubMenu() {
    sleep(1);
    cout << "\033[2J\033[H";  
    cout << "\033[32m";  
    centerText("Reports Menu", '-');
    cout << "1. Generate Event Report" << endl;
    cout << "2. Generate User Activity Report" << endl;
    cout << "3. Back" << endl;
    centerText("", '-'); 
    cout << "\033[0m";  
    cout << "Enter your choice: ";
}

void handleReportsSubMenu() {
    while (true) {
        showReportsSubMenu();
        int reportsChoice = getValidatedChoice(1, 3);

        if (reportsChoice == 3) break;

        switch (reportsChoice) {
            case 1: {
                int eventID;
                cout << "Enter Event ID to generate report: ";
                cin >> eventID;
                generateEventReport(eventID);
                break;
            }
            case 2: {
                int userID;
                cout << "Enter User ID to generate activity report: ";
                cin >> userID;
                generateUserActivityReport(userID);
                break;
            }
            default:
                cout << "Invalid choice.\n";
        }
    }
}

int getValidatedChoice(int min, int max) {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail() || choice < min || choice > max) {
            cout << "Invalid input. Please enter a number between " << min << " and " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return choice;
}

void showMainMenu() {
    cout << "\033[2J\033[H";  
    cout << "\033[32m";  
    centerText("Main Menu", '-');
    cout << "1. Login" << endl;
    cout << "2. Create Account" << endl;
    cout << "3. Exit" << endl;
    centerText("", '-'); 
    cout << "\033[0m";  
    cout << "Enter your choice: ";
}

void handleMainMenu() {
    while (true) {
        showMainMenu();
        int choice = getValidatedChoice(1, 3);

        switch (choice) {
            case 1: {
                sleep(1);
                cout << "\033[2J\033[H";  
                cout << "\033[32m";  
                centerText("Login Menu", '-');
                cout << "1. Login as User" << endl;
                cout << "2. Login as Admin" << endl;
                cout << "3. Back" << endl;
                centerText("", '-'); 
                cout << "\033[0m"; 
                cout << "Choose an option: ";
                int loginChoice = getValidatedChoice(1, 3);

                if (loginChoice == 1) {
                    int userID = loginUser();
                    if (userID != -1) {
                        sleep(1);
                        cout << "\033[2J\033[H"; 
                        cout << "UserId: " << userID << endl;
                        handleUserMenu(userID);
                    } else {
                        cout << "\033[31mUser Login failed.\033[0m\n"; 
                        sleep(2);
                        cout << "\033[2J\033[H";  
                    }
                } else if (loginChoice == 2) {
                    if (loginAdmin() != -1) {
                        handleAdminMenu();
                    } else {
                        cout << "\033[31mAdmin Login failed.\033[0m\n"; // Red color
                        sleep(2);
                        cout << "\033[2J\033[H"; 
                    }
                } else if (loginChoice == 3) {
                    sleep(1);
                    cout << "\033[2J\033[H";  
                    break;
                }
                break;
            }
            case 2: {
                sleep(1);
                cout << "\033[2J\033[H"; 
                cout << "\033[32m";  
                centerText("Account Creation Menu", '-');
                cout << "1. Create User Account" << endl;
                cout << "2. Create Admin Account" << endl;
                cout << "3. Back" << endl;
                centerText("", '-'); 
                cout << "\033[0m"; 
                cout << "Choose an option: ";
                int accountChoice = getValidatedChoice(1, 3);

                if (accountChoice == 3) break;

                switch (accountChoice) {
                    case 1:
                        createUserAccount();
                        break;
                    case 2:
                        createAdminAccount();
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            }
            case 3:
                cout << "Exiting the program.\n";
                sleep(1);
                cout << "\033[2J\033[H";
                return;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
