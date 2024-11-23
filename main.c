#include "calendar.h"
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_EVENTS 100

// Helper Function to Calculate the Day of the Week
int calculateDayOfWeek(int day, int month, int year) {
    int adjustedYear = (month <= 2) ? year - 1 : year;
    int adjustedMonth = (month <= 2) ? month + 12 : month;
    int K = adjustedYear % 100;
    int J = adjustedYear / 100;
    int dayOfWeek = (day + 13 * (adjustedMonth + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    return (dayOfWeek + 6) % 7; // Adjust to make Sunday = 0, Monday = 1, etc.
}

// Function Implementations
void viewCalendar(int month, int year) {
    printf("\n   Calendar for %02d/%d\n", month, year);
    printf(" Su Mo Tu We Th Fr Sa\n");
    int daysInMonth[] = {31, (year % 4 == 0 && year % 100 != 0) || year % 400 == 0 ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int startDay = calculateDayOfWeek(1, month, year);

    for (int i = 0; i < startDay; i++) printf("   ");
    for (int day = 1; day <= daysInMonth[month - 1]; day++) {
        printf("%3d", day);
        if ((day + startDay) % 7 == 0) printf("\n");
    }
    printf("\n");
}

void presentCalendar() {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int currentMonth = tm_info->tm_mon + 1;
    int currentYear = tm_info->tm_year + 1900;
    viewCalendar(currentMonth, currentYear);
}

void addTask(Task *task) {
    printf("Enter task description: ");
    getchar(); // Consume leftover newline
    fgets(task->description, sizeof(task->description), stdin);
    task->description[strcspn(task->description, "\n")] = '\0';

    printf("Enter task date (dd-mm-yyyy): ");
    scanf("%s", task->date);

    printf("Enter task priority (1 = High, 2 = Medium, 3 = Low): ");
    scanf("%d", &task->priority);

    printf("Task added successfully!\n");
}

void editTask(Task tasks[], int numTasks) {
    if (numTasks == 0) {
        printf("No tasks available to edit.\n");
        return;
    }

    for (int i = 0; i < numTasks; i++) {
        printf("%d. %s (Date: %s, Priority: %d)\n", i + 1, tasks[i].description, tasks[i].date, tasks[i].priority);
    }

    printf("Enter the task number to edit: ");
    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > numTasks) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter new description: ");
    getchar();
    fgets(tasks[choice - 1].description, sizeof(tasks[choice - 1].description), stdin);
    tasks[choice - 1].description[strcspn(tasks[choice - 1].description, "\n")] = '\0';

    printf("Enter new date (dd-mm-yyyy): ");
    scanf("%s", tasks[choice - 1].date);

    printf("Enter new priority (1 = High, 2 = Medium, 3 = Low): ");
    scanf("%d", &tasks[choice - 1].priority);

    printf("Task updated successfully!\n");
}

void showUpcomingTasks(Task tasks[], int numTasks) {
    printf("Upcoming tasks:\n");
    for (int i = 0; i < numTasks; i++) {
        printf("- %s on %s (Priority: %d)\n", tasks[i].description, tasks[i].date, tasks[i].priority);
    }
}

void addEvent(Event *event) {
    printf("Enter event title: ");
    getchar();
    fgets(event->title, sizeof(event->title), stdin);
    event->title[strcspn(event->title, "\n")] = '\0';

    printf("Enter event date (dd-mm-yyyy): ");
    scanf("%s", event->date);

    printf("Enter event description: ");
    getchar();
    fgets(event->description, sizeof(event->description), stdin);
    event->description[strcspn(event->description, "\n")] = '\0';

    printf("Event added successfully!\n");
}

void showEvents(Event events[], int numEvents, char filterDate[]) {
    printf("Events for %s:\n", filterDate);
    for (int i = 0; i < numEvents; i++) {
        if (strcmp(events[i].date, filterDate) == 0) {
            printf("- %s: %s\n", events[i].title, events[i].description);
        }
    }
}

void editEvent(Event events[], int numEvents) {
    if (numEvents == 0) {
        printf("No events available to edit.\n");
        return;
    }

    for (int i = 0; i < numEvents; i++) {
        printf("%d. %s on %s\n", i + 1, events[i].title, events[i].date);
    }

    printf("Enter the event number to edit: ");
    int choice;
    scanf("%d", &choice);

    if (choice < 1 || choice > numEvents) {
        printf("Invalid choice.\n");
        return;
    }

    printf("Enter new title: ");
    getchar();
    fgets(events[choice - 1].title, sizeof(events[choice - 1].title), stdin);
    events[choice - 1].title[strcspn(events[choice - 1].title, "\n")] = '\0';

    printf("Enter new date (dd-mm-yyyy): ");
    scanf("%s", events[choice - 1].date);

    printf("Enter new description: ");
    getchar();
    fgets(events[choice - 1].description, sizeof(events[choice - 1].description), stdin);
    events[choice - 1].description[strcspn(events[choice - 1].description, "\n")] = '\0';

    printf("Event updated successfully!\n");
}

void addDiaryEntry(char date[], char content[]) {
    FILE *file = fopen("diary.txt", "a");
    if (file == NULL) {
        printf("Error opening diary file.\n");
        return;
    }
    fprintf(file, "Date: %s\nContent: %s\n\n", date, content);
    fclose(file);
    printf("Diary entry added successfully!\n");
}

void viewDiaryEntry(char date[]) {
    FILE *file = fopen("diary.txt", "r");
    if (file == NULL) {
        printf("Error opening diary file.\n");
        return;
    }

    char fileDate[11], fileContent[200];
    int found = 0;
    while (fscanf(file, "Date: %10s\nContent: %[^\n]\n\n", fileDate, fileContent) != EOF) {
        if (strcmp(fileDate, date) == 0) {
            printf("Diary entry for %s:\n%s\n", fileDate, fileContent);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("No diary entry found for %s.\n", date);
    }
}

int main() {
    Task tasks[MAX_TASKS];
    Event events[MAX_EVENTS];
    int numTasks = 0, numEvents = 0;
    int choice;

    do {
        printf("\n--- Calendar Menu ---\n");
        printf("1. Show Calendar for a Specific Month\n");
        printf("2. Show Calendar for Current Month\n");
        printf("3. Add Task\n");
        printf("4. Edit Task\n");
        printf("5. Show Upcoming Tasks\n");
        printf("6. Add Event\n");
        printf("7. Show Event \n");
        printf("8. Edit Event\n");
        printf("9. Add Diary Entry\n");
        printf("10. View Diary Entry\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int month, year;
                printf("Enter month and year (MM YYYY): ");
                scanf("%d %d", &month, &year);
                viewCalendar(month, year);
                break;
            }
            case 2:
                presentCalendar();
                break;
            case 3:
                addTask(&tasks[numTasks++]);
                break;
            case 4:
                editTask(tasks, numTasks);
                break;
            case 5:
                showUpcomingTasks(tasks, numTasks);
                break;
            case 6:
                addEvent(&events[numEvents++]);
                break;
            case 7: {
                char filterDate[11];
                printf("Enter date to filter events (dd-mm-yyyy): ");
                scanf("%s", filterDate);
                showEvents(events, numEvents, filterDate);
                break;
            }
            case 8:
                editEvent(events, numEvents);
                break;
            case 9: {
                char date[11], content[200];
                printf("Enter date (dd-mm-yyyy): ");
                scanf("%s", date);
                printf("Enter diary content: ");
                getchar();
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = '\0';
                addDiaryEntry(date, content);
                break;
            }
            case 10: {
                char date[11];
                printf("Enter date to view diary (dd-mm-yyyy): ");
                scanf("%s", date);
                viewDiaryEntry(date);
                break;
            }
            case 11:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 11);

    return 0;
}
