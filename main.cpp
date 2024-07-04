#include <iostream>
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

void showUserMenu() {
    cout << "\nUser Menu:\n";
    cout << "1. Events\n";
    cout << "2. Profile\n";
    cout << "3. Notifications\n";
    cout << "4. Comments & Feedback\n";
    cout << "5. Logout\n";
    cout << "Enter your choice: ";
}

void showEventsSubMenu() {
    cout << "\nEvents Menu:\n";
    cout << "1. Browse Events\n";
    cout << "2. Join Event\n";
    cout << "3. Cancel Registration\n";
    cout << "4. View Joined Events\n";
    cout << "5. Search Events by Name\n";
    cout << "6. Search Events by Date\n";
    cout << "7. Set Event Reminder\n";
    cout << "8. View Event Reminders\n";
    cout << "9. Back\n";
    cout << "Enter your choice: ";
}

void showProfileSubMenu() {
    cout << "\nProfile Menu:\n";
    cout << "1. Update Profile\n";
    cout << "2. Change Password\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
}

void showNotificationsSubMenu() {
    cout << "\nNotifications Menu:\n";
    cout << "1. View Upcoming Events\n";
    cout << "2. View Event Changes\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
}

void showCommentsFeedbackSubMenu() {
    cout << "\nComments & Feedback Menu:\n";
    cout << "1. Leave Comment on Event\n";
    cout << "2. View Comments on Event\n";
    cout << "3. Leave Event Feedback\n";
    cout << "4. View Event Feedback\n";
    cout << "5. Back\n";
    cout << "Enter your choice: ";
}

void showAdminMenu() {
    cout << "\nAdmin Menu:\n";
    cout << "1. Event Management\n";
    cout << "2. Reports\n";
    cout << "3. Logout\n";
    cout << "Enter your choice: ";
}

void showEventManagementSubMenu() {
    cout << "\nEvent Management Menu:\n";
    cout << "1. Create Event\n";
    cout << "2. Edit Event\n";
    cout << "3. Delete Event\n";
    cout << "4. View Event Registrations\n";
    cout << "5. Back\n";
    cout << "Enter your choice: ";
}

void showReportsSubMenu() {
    cout << "\nReports Menu:\n";
    cout << "1. Generate Event Report\n";
    cout << "2. Generate User Activity Report\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
}

int main() {
    while (1) {
        int choice;
        cout << "1. Login\n2. Create Account\n3. Exit\nChoose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int loginChoice;
                cout << "1. Login as User\n2. Login as Admin\nChoose an option: ";
                cin >> loginChoice;

                if (loginChoice == 1 && loginUser()) {
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
                } else if (loginChoice == 2 && loginAdmin()) {
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
                                int reportsChoice;
                                while (true) {
                                    showReportsSubMenu();
                                    cin >> reportsChoice;
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
                                break;
                            }
                            default:
                                cout << "Invalid choice.\n";
                        }
                    }
                } else {
                    cout << "Login failed.\n";
                }
                break;
            }
            case 2: {
                int accountChoice;
                cout << "1. Create User Account\n2. Create Admin Account\nChoose an option: ";
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
