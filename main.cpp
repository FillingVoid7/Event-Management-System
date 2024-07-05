#include <iostream>
#include <limits>
#include <unistd.h> // for sleep
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

void showUserMenu();
void handleUserMenu(int userID);
void showEventsSubMenu();
void handleEventsSubMenu(int userID);
void showProfileSubMenu();
void handleProfileSubMenu(int userID);
void showNotificationsSubMenu();
void handleNotificationsSubMenu(int userID);
void showCommentsFeedbackSubMenu();
void handleCommentsFeedbackSubMenu(int userID);
void showAdminMenu();
void handleAdminMenu();
void showEventManagementSubMenu();
void handleEventManagementSubMenu();
void showReportsSubMenu();
void handleReportsSubMenu();
int getValidatedChoice(int min, int max);
void showMainMenu();
void handleMainMenu();

int main() {
  
    handleMainMenu();
    return 0;
    
}

void showUserMenu() {
    cout << "\nUser Menu:\n";
    cout << "1. Events\n";
    cout << "2. Profile\n";
    cout << "3. Notifications\n";
    cout << "4. Comments & Feedback\n";
    cout << "5. Logout\n";
    cout << "Enter your choice: ";
}

void handleUserMenu(int userID) {
    while (true) {
        showUserMenu();
        int userChoice = getValidatedChoice(1, 5);

        if (userChoice == 5) break;

        switch (userChoice) {
            case 1:
                handleEventsSubMenu(userID);
                break;
            case 2:
                handleProfileSubMenu(userID);
                break;
            case 3:
                handleNotificationsSubMenu(userID);
                break;
            case 4:
                handleCommentsFeedbackSubMenu(userID);
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
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

void handleEventsSubMenu(int userID) {
    while (true) {
        showEventsSubMenu();
        int eventChoice = getValidatedChoice(1, 9);

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
}

void showProfileSubMenu() {
    cout << "\nProfile Menu:\n";
    cout << "1. Update Profile\n";
    cout << "2. Change Password\n";
    cout << "3. Back\n";
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

void showNotificationsSubMenu() {
    cout << "\nNotifications Menu:\n";
    cout << "1. View Upcoming Events\n";
    cout << "2. View Event Changes\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
}

void handleNotificationsSubMenu(int userID) {
    while (true) {
        showNotificationsSubMenu();
        int notificationChoice = getValidatedChoice(1, 3);

        if (notificationChoice == 3) break;

        switch (notificationChoice) {
            case 1:
                // Handle viewing upcoming events
                break;
            case 2:
                // Handle viewing event changes
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
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

void handleCommentsFeedbackSubMenu(int userID) {
    while (true) {
        showCommentsFeedbackSubMenu();
        int commentFeedbackChoice = getValidatedChoice(1, 5);

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
}

void showAdminMenu() {
    cout << "\nAdmin Menu:\n";
    cout << "1. Event Management\n";
    cout << "2. Reports\n";
    cout << "3. Logout\n";
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
    cout << "\nEvent Management Menu:\n";
    cout << "1. Create Event\n";
    cout << "2. Edit Event\n";
    cout << "3. Delete Event\n";
    cout << "4. View Event Registrations\n";
    cout << "5. Back\n";
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
    cout << "\nReports Menu:\n";
    cout << "1. Generate Event Report\n";
    cout << "2. Generate User Activity Report\n";
    cout << "3. Back\n";
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
            cout << "Invalid choice. Please enter a number between " << min << " and " << max << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return choice;
}

void showMainMenu() {
    cout << "1. Login\n";
    cout << "2. Create Account\n";
    cout << "3. Exit\n";
    cout << endl;
    cout << "Choose an option: ";
}

void handleMainMenu() {
    while (true) {
       
        showMainMenu();
        int choice = getValidatedChoice(1, 3);

        switch (choice) {
            case 1: {
                sleep(1);
                std::cout << "\033[2J\033[H";
                int loginChoice;
                cout << "1. Login as User\n2. Login as Admin\n Choose an option: ";
                loginChoice = getValidatedChoice(1, 2);

                // login as user
                if (loginChoice == 1) {
                    int userID = loginUser();
                    //cout << userID; => -1
                    if (userID != -1) {
                        handleUserMenu(userID);
                    } else {
                        cout << "User Login failed.\n";
                    }
                } else if (loginChoice == 2) {
                    if (loginAdmin()) {
                        handleAdminMenu();
                    } else {
                        cout << " Admin Login failed.\n";
                    }
                }
                break;
            
                 
                // cout << "1. Login as User\n2. Login as Admin\nChoose an option: ";
                // loginChoice = getValidatedChoice(1, 2);

                // if (loginChoice == 1) {

                //     int userID = loginAdmin(); 
                //     if(userID != -1 ){
                //         handleUserMenu(userID);
                //     }else {
                //         cout << "Login failed.\n";
                //     }
                    
                // } else if (loginChoice == 2 && loginAdmin()) {
                //     handleAdminMenu();
                // } else {
                //     cout << "Login failed.\n";
                // }
                // break;
            }
            case 2: {
                int accountChoice;
                cout << "1. Create User Account\n2. Create Admin Account\nChoose an option: ";
                accountChoice = getValidatedChoice(1, 2);

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
            case 3:{
                cout << "Exiting the program.\n";
                return;
            }
            default:
                cout << "Invalid choice.\n";
        }
    }
}
