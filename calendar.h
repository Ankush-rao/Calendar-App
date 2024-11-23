#ifndef CALENDAR_H
#define CALENDAR_H

#include <stdio.h>
#include <time.h>

// Data Structures
typedef struct Task {
    char description[100];
    char date[11];    // Format: "dd-mm-yyyy"
    int priority;     // Priority: 1 = High, 2 = Medium, 3 = Low
} Task;

typedef struct Event {
    char title[100];
    char description[200];
    char date[11];    // Format: "dd-mm-yyyy"
} Event;

// Function Prototypes

// 1. Show Calendar for a Specific Month
void viewCalendar(int month, int year);

// 2. Show Calendar for Current Month
void presentCalendar();

// 3. Add Task
void addTask(Task *task);

// 4. Edit Task
void editTask(Task tasks[], int numTasks);

// 5. Show Upcoming Tasks
void showUpcomingTasks(Task tasks[], int numTasks);

// 6. Add Event
void addEvent(Event *event);

// 7. Show Event for a Specific Date/Month/Year
void showEvents(Event events[], int numEvents, char filterDate[]);

// 8. Edit Event
void editEvent(Event events[], int numEvents);

// 9. Add Diary Entry
void addDiaryEntry(char date[], char content[]);

// 10. View Diary Entry
void viewDiaryEntry(char date[]);

#endif
