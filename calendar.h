#ifndef CALENDAR_H
#define CALENDAR_H

#include <time.h>

// Task structure to store task data
struct Task {
    char description[100];  // Task description
    char date[11];          // Date of the task in dd-mm-yyyy format
    int priority;           // Priority level (1 = high, 2 = medium, 3 = low)
};

// Event structure to store event data
struct Event {
    char title[100];        // Event title
    char date[15];          // Event date (formatted as dd-mm-yyyy)
    char description[200];  // Event description
};

// Diary structure to store diary entry data
struct Diary {
    char date[11];          // Date of the diary entry in dd-mm-yyyy format
    char content[200];      // Diary content
};

// Function declarations
void showDate();                          // Show the current date
void addTask(struct Task *task);          // Add a task
void editTask(struct Task tasks[], int numTasks);  // Edit a task
void showUpcomingTasks(struct Task tasks[], int numTasks); // Show tasks for the next 7 days
void addEvent(struct Event *event);       // Add an event
void editEvent(struct Event events[], int numEvents);  // Edit an event
void showEvents(struct Event events[], int numEvents);  // Show all events
void showUpcomingEvents(struct Event events[], int numEvents);  // Show upcoming events
void showEventsInMonth(struct Event events[], int numEvents, int month, int year);  // Show events in a specific month
void addDiaryEntry(char date[], char content[]);  // Add a diary entry
void viewDiaryEntry(char date[]);  // View a diary entry
void getDateInput(char *date);            // Get task or event date input (dd-mm-yyyy)
void viewCalendar(int month, int year, struct Task tasks[], int numTasks, struct Event events[], int numEvents); // Show calendar for a given month and year
void presentCalendar(struct Task tasks[], int numTasks, struct Event events[], int numEvents); // Show the current month calendar
int isDateWithinRange(char *date, char *startDate, char *endDate);  // Check if a date is within range
int calculateDayOfWeek(int day, int month, int year); // Calculate the day of the week for the 1st of the month

#endif
