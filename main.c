#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "calendar.h"

// Function to show current date
void showDate() {
    time_t t;
    struct tm *tm_info;
    char buffer[26];

    time(&t);
    tm_info = localtime(&t);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d", tm_info);
    printf("Current date: %s\n", buffer);
}

// Function to add a task
void addTask(struct Task *task) {
    printf("Enter task description: ");
    getchar(); // Consume newline character left by previous input
    fgets(task->description, sizeof(task->description), stdin);
    task->description[strcspn(task->description, "\n")] = 0; // Remove newline from the string

    printf("Enter task date (dd-mm-yyyy): ");
    scanf("%s", task->date);

    printf("Enter task priority (1 = high, 2 = medium, 3 = low): ");
    scanf("%d", &task->priority);

    printf("Task added successfully!\n");
}

// Function to add an event
void addEvent(struct Event *event) {
    printf("Enter event title: ");
    getchar(); // Consume newline character left by previous input
    fgets(event->title, sizeof(event->title), stdin);
    event->title[strcspn(event->title, "\n")] = 0; // Remove newline from the string

    printf("Enter event date (dd-mm-yyyy): ");
    scanf("%s", event->date);

    printf("Enter event description: ");
    getchar(); // Consume newline character
    fgets(event->description, sizeof(event->description), stdin);
    event->description[strcspn(event->description, "\n")] = 0; // Remove newline from the string

    printf("Event added successfully!\n");
}

// Function to add a diary entry
void addDiaryEntry(char date[], char content[]) {
    FILE *file = fopen("diary.txt", "a");  // Open file in append mode
    if (file == NULL) {
        printf("Error opening diary file.\n");
        return;
    }

    fprintf(file, "Date: %s\n", date);
    fprintf(file, "Entry: %s\n\n", content);
    fclose(file);

    printf("Diary entry added successfully!\n");
}

// Function to view a diary entry for a specific date
void viewDiaryEntry(char date[]) {
    FILE *file = fopen("diary.txt", "r");  // Open file in read mode
    if (file == NULL) {
        printf("Error opening diary file.\n");
        return;
    }

    char fileDate[11], fileContent[200];
    int found = 0;  // Flag to indicate if entry is found

    // Read the file line by line
    while (fscanf(file, "Date: %10s\nEntry: %[^\n]\n\n", fileDate, fileContent) != EOF) {
        // Compare the file date with the input date
        if (strcmp(fileDate, date) == 0) {
            printf("Diary entry for %s:\n", fileDate);
            printf("Entry: %s\n", fileContent);
            found = 1;
            break;  // Exit the loop once the entry is found
        }
    }

    if (!found) {
        printf("No diary entry found for the date %s.\n", date);
    }

    fclose(file);  // Close the file after reading
}

// Function to view the calendar for a specific month and year
void viewCalendar(int month, int year, struct Task tasks[], int numTasks, struct Event events[], int numEvents) {
    // Your code to display the calendar (previously shared logic for calculating days)
}

// Function to show the present month's calendar
void presentCalendar(struct Task tasks[], int numTasks, struct Event events[], int numEvents) {
    time_t t;
    struct tm *tm_info;
    int month, year;

    time(&t);
    tm_info = localtime(&t);

    month = tm_info->tm_mon + 1;  // tm_mon starts from 0 for January, so we add 1
    year = tm_info->tm_year + 1900;  // tm_year counts years since 1900

    viewCalendar(month, year, tasks, numTasks, events, numEvents);
}

// Function to show upcoming tasks
void showUpcomingTasks(struct Task tasks[], int numTasks) {
    // Your code to show upcoming tasks (tasks within the next 7 days)
}

// Function to show upcoming events
void showUpcomingEvents(struct Event events[], int numEvents) {
    // Your code to show upcoming events (events within the next 30 days)
}

// Function to show all events in a specific month
void showEventsInMonth(struct Event events[], int numEvents, int month, int year) {
    // Your code to show events in a specific month
}

// Function to get date input
void getDateInput(char *date) {
    printf("Enter date (dd-mm-yyyy): ");
    scanf("%s", date);
}

// Function to edit a task
void editTask(struct Task tasks[], int numTasks) {
    // Your code for editing tasks (choose from existing tasks and modify)
}

// Function to calculate the day of the week for a specific date
int calculateDayOfWeek(int day, int month, int year) {
    // Code for calculating the day of the week (using Zeller's Congruence or any preferred method)
}

int main() {
    int choice;
    struct Task tasks[100];
    struct Event events[100];
    int numTasks = 0, numEvents = 0;

    do {
        printf("\nMenu:\n");
        printf("1. Show Calendar\n");
        printf("2. Present Calendar\n");
        printf("3. Add Task\n");
        printf("4. Show Upcoming Tasks\n");
        printf("5. Add Event\n");
        printf("6. Show Upcoming Events\n");
        printf("7. Show Events for Specific Month\n");
        printf("8. Add Diary Entry\n");
        printf("9. View Diary Entry\n");
        printf("10. Edit Task\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int month, year;
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                viewCalendar(month, year, tasks, numTasks, events, numEvents);
                break;
            }
            case 2:
                presentCalendar(tasks, numTasks, events, numEvents);
                break;
            case 3:
                addTask(&tasks[numTasks]);
                numTasks++;
                break;
            case 4:
                showUpcomingTasks(tasks, numTasks);
                break;
            case 5:
                addEvent(&events[numEvents]);
                numEvents++;
                break;
            case 6:
                showUpcomingEvents(events, numEvents);
                break;
            case 7: {
                int month, year;
                printf("Enter month (1-12): ");
                scanf("%d", &month);
                printf("Enter year: ");
                scanf("%d", &year);
                showEventsInMonth(events, numEvents, month, year);
                break;
            }
            case 8: {
                char date[11], content[200];
                printf("Enter date (dd-mm-yyyy): ");
                scanf("%s", date);
                printf("Enter diary entry: ");
                getchar();  // Consume leftover newline
                fgets(content, sizeof(content), stdin);
                addDiaryEntry(date, content);
                break;
            }
            case 9: {
                char date[11];
                printf("Enter the date (dd-mm-yyyy) to view the diary entry: ");
                scanf("%s", date);
                viewDiaryEntry(date);
                break;
            }
            case 10:
                editTask(tasks, numTasks);
                break;
            case 11:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 11);

    return 0;
}
