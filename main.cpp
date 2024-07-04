#include <iostream>
#include <iomanip> 
#include <bits/stdc++.h>
#include "Login.h"
#include "CreateUserAccount.h"
#include "AdminPanel.h"
#include "JoinEvents.h"
#include "UserProfile.h"
#include "EventSearch.h"
#include "Comment.h"
#include "Notification.h"
#include "AdminReports.h"
#include "EventReminder.h"
#include "EventFeedback.h"

using namespace std;

void centerOutput(const string& text) {
    int width = 100; 
    int padding = (width - text.length()) / 2;
    cout << setw(padding + text.length()) << text << endl;
}

void showUserMenu() {
    centerOutput("======================");
    centerOutput(" User Menu");
    centerOutput("======================");
    cout << "1. Events" << endl;
    cout << "2. Profile" << endl;
    cout << "3. Notifications" << endl;
    cout << "4. Comments & Feedback" << endl;
    cout << "5. Logout" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

void showEventsSubMenu() {
    centerOutput("======================");
    centerOutput(" Events Menu");
    centerOutput("======================");
    cout << "1. Browse Events" << endl;
    cout << "2. Join Event" << endl;
    cout << "3. Cancel Registration" << endl;
    cout << "4. View Joined Events" << endl;
    cout << "5. Search Events by Name" << endl;
    cout << "6. Search Events by Date" << endl;
    cout << "7. Set Event Reminder" << endl;
    cout << "8. View Event Reminders" << endl;
    cout << "9. Back" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

void showProfileSubMenu() {
    centerOutput("======================");
    centerOutput(" Profile Menu");
    centerOutput("======================");
    cout << "1. Update Profile" << endl;
    cout << "2. Back" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

void showNotificationsSubMenu() {
    centerOutput("======================");
    centerOutput(" Notifications Menu");
    centerOutput("======================");
    cout << "1. View Upcoming Events" << endl;
    cout << "2. View Event Changes" << endl;
    cout << "3. Back" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

void showCommentsFeedbackSubMenu() {
    centerOutput("======================");
    centerOutput(" Comments & Feedback Menu");
    centerOutput("======================");
    cout << "1. Leave Comment on Event" << endl;
    cout << "2. View Comments on Event" << endl;
    cout << "3. Leave Event Feedback" << endl;
    cout << "4. View Event Feedback" << endl;
    cout << "5. Back" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

void showAdminMenu() {
    centerOutput("======================");
    centerOutput(" Admin Menu");
    centerOutput("======================");
    cout << "1. Event Management" << endl;
    cout << "2. Reports" << endl;
    cout << "3. Logout" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

void showEventManagementSubMenu() {
    centerOutput("======================");
    centerOutput(" Event Management Menu");
    centerOutput("======================");
    cout << "1. Create Event" << endl;
    cout << "2. Edit Event" << endl;
    cout << "3. Delete Event" << endl;
    cout << "4. View Event Registrations" << endl;
    cout << "5. Back" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

void showReportsSubMenu() {
    centerOutput("======================");
    centerOutput(" Reports Menu");
    centerOutput("======================");
    cout << "1. Generate Event Report" << endl;
    cout << "2. Generate User Activity Report" << endl;
    cout << "3. Back" << endl;
    centerOutput("======================");
    cout << "Enter your choice: ";
}

int main() {
    while (true) {
        int choice;
        centerOutput("======================");
        centerOutput(" Main Menu");
        centerOutput("======================");
        cout << "1. Login" << endl;
        cout << "2. Create Account" << endl;
        cout << "3. Exit" << endl;
        centerOutput("======================");
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int loginChoice;
                centerOutput("1. Login as User");
                centerOutput("2. Login as Admin");
                cout << "Choose an option: ";
                cin >> loginChoice;

                if (loginChoice == 1) {
                    int userAttempts = 0;
                    while (userAttempts < 3) { 
                        if (loginUser()) {
                            int userChoice;
                            int userID = -1;
                            while (true) {
                                showUserMenu();
                                cin >> userChoice;

                                if (userChoice == 5) break;

                                switch (userChoice) {
                                    case 1: {
                                        int eventChoice;
                                        while (true) {
                                            showEventsSubMenu();
                                            cin >> eventChoice;
                                            if (eventChoice == 9) break;

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
                                                    searchEventByName(); 
                                                    break;
                                                case 6:
                                                    searchEventByDate();  
                                                    break;
                                                case 7: {
                                                    int eventID;
                                                    cout << "Enter Event ID to set reminder: ";
                                                    cin >> eventID;
                                                    setEventReminder(userID, eventID);  
                                                    break;
                                                }
                                                case 8:
                                                    viewEventReminders(userID);  
                                                    break;
                                                default:
                                                    cout << "Invalid choice.\n";
                                            }
                                        }
                                        break;
                                    }
                                    case 2: {
                                        int profileChoice;
                                        while (true) {
                                            showProfileSubMenu();
                                            cin >> profileChoice;
                                            if (profileChoice == 2) break;

                                            switch (profileChoice) {
                                                case 1:
                                                    changeUserProfile(userID); 
                                                    break;
                                                default:
                                                    cout << "Invalid choice.\n";
                                            }
                                        }
                                        break;
                                    }
                                    case 3: {
                                        int notificationChoice;
                                        while (true) {
                                            showNotificationsSubMenu();
                                            cin >> notificationChoice;
                                            if (notificationChoice == 3) break;

                                            switch (notificationChoice) {
                                                case 1: {
                                                    string message;
                                                    cout << "Enter notification message: ";
                                                    cin.ignore();
                                                    getline(cin, message);
                                                    addNotification(userID, message);  
                                                    break;
                                                }
                                                case 2:
                                                    viewNotifications(userID);  
                                                    break;
                                                default:
                                                    cout << "Invalid choice.\n";
                                            }
                                        }
                                        break;
                                    }
                                    case 4: {
                                        int commentFeedbackChoice;
                                        while (true) {
                                            showCommentsFeedbackSubMenu();
                                            cin >> commentFeedbackChoice;
                                            if (commentFeedbackChoice == 5) break;

                                            switch (commentFeedbackChoice) {
                                                case 1: {
                                                    int eventID;
                                                    cout << "Enter Event ID to comment: ";
                                                    cin >> eventID;
                                                    addComment(userID, eventID);  
                                                    break;
                                                }
                                                case 2: {
                                                    int eventID;
                                                    cout << "Enter Event ID to view comments: ";
                                                    cin >> eventID;
                                                    viewComments(eventID);  
                                                    break;
                                                }
                                                case 3: {
                                                    int eventID;
                                                    cout << "Enter Event ID to leave feedback: ";
                                                    cin >> eventID;
                                                    provideFeedback(userID, eventID);  
                                                    break;
                                                }
                                                case 4: {
                                                    int eventID;
                                                    cout << "Enter Event ID to view feedback: ";
                                                    cin >> eventID;
                                                    viewFeedback(eventID);  
                                                    break;
                                                }
                                                default:
                                                    cout << "Invalid choice.\n";
                                            }
                                        }
                                        break;
                                    }
                                    default:
                                        cout << "Invalid choice.\n";
                                }
                            }
                            break;
                        } else {
                            userAttempts++;
                            if (userAttempts < 3) {
                                cout << "Login failed. Please try again." << endl;
                            } else {
                                cout << "Maximum login attempts exceeded. Returning to main menu." << endl;
                            }
                        }
                    }
                } else if (loginChoice == 2) {
                    int adminAttempts = 0;
                    while (adminAttempts < 3) { 
                        if (loginAdmin()) {
                            int adminChoice;
                            while (true) {
                                showAdminMenu();
                                cin >> adminChoice;

                                if (adminChoice == 3) break;

                                switch (adminChoice) {
                                    case 1: {
                                        int eventManagementChoice;
                                        while (true) {
                                            showEventManagementSubMenu();
                                            cin >> eventManagementChoice;
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
                                        break;
                                    }
                                    case 2: {
                                        int reportChoice;
                                        while (true) {
                                            showReportsSubMenu();
                                            cin >> reportChoice;
                                            if (reportChoice == 3) break;

                                            switch (reportChoice) {
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
                                        break;
                                    }
                                    default:
                                        cout << "Invalid choice.\n";
                                }
                            }
                            break;
                        } else {
                            adminAttempts++;
                            if (adminAttempts < 3) {
                                cout << "Login failed. Please try again." << endl;
                            } else {
                                cout << "Maximum login attempts exceeded. Returning to main menu." << endl;
                            }
                        }
                    }
                }
                break;
            }
            case 2: {
                int accountChoice;
                centerOutput("1. Create User Account");
                centerOutput("2. Create Admin Account");
                cout << "Choose an option: ";
                cin >> accountChoice;

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
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}
