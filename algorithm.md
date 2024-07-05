# College Event Management System Algorithm

## 1. Start

## 2. Main Menu
- Display options: 
    1. User Login
    2. Admin Login
    3. Exit

## 3. If User selects "User Login":
- Authenticate user
- If authentication is successful:
    - Display User Menu
    - Else, prompt error and return to Main Menu

## 4. User Menu
- Display options:
    1. View Events
    2. View Event Details by Date
    3. View Events by Name
    4. View Upcoming Events
    5. Search Events by Date
    6. Search Events by Name
    7. Give Event Feedback
    8. Leave Comment on Event
    9. View Feedback on Event
    10. Logout

- Based on user selection:
    - If 1: Display all events
    - If 2: Prompt for date and display event details
    - If 3: Prompt for event name and display event details
    - If 4: Display upcoming events
    - If 5: Prompt for date and search events
    - If 6: Prompt for event name and search events
    - If 7: Prompt for event name and allow feedback
    - If 8: Prompt for event name and allow comments
    - If 9: Prompt for event name and display feedback
    - If 10: Logout and return to Main Menu

## 5. If User selects "Admin Login":
- Authenticate admin
- If authentication is successful:
    - Display Admin Menu
    - Else, prompt error and return to Main Menu

## 6. Admin Menu
- Display options:
    1. Manage Events
    2. View Reports
    3. Logout

- Based on admin selection:
    - If 1: Display Event Management Options
    - If 2: Display Report Options
    - If 3: Logout and return to Main Menu

## 7. Event Management Options
- Display options:
    1. Add Event
    2. Delete Event
    3. Update Event
    4. View Event Participation
    5. Create Event
    6. Update Event

- Based on admin selection:
    - If 1: Prompt for event details and add event
    - If 2: Prompt for event ID/name and delete event
    - If 3: Prompt for event ID/name and update details
    - If 4: Display event participation details
    - If 5: Prompt for event details and create event
    - If 6: Prompt for event ID/name and update event

## 8. View Reports Options
- Display options:
    1. Generate Event Report
    2. Generate User Participation Report

- Based on admin selection:
    - If 1: Generate and display event report
    - If 2: Generate and display user participation report

## 9. If User selects "Exit":
- Exit the system

## 10. End
