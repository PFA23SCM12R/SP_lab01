#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "readfile.h"

#define MAXNAME 64
#define MAXEMPLOYEES 1024

// Employee structure
struct employee {
    int id;
    char firstName[MAXNAME];
    char lastName[MAXNAME];
    float salary;
};

// Function prototypes
void printEmployee(const struct employee *empPtr);
void printDB(const struct employee *empList, int numEmployees);
void sortDB(struct employee *empList, int numEmployees);
void lookUpID(const struct employee *empList, int numEmployees);
void lookUpLastName(const struct employee *empList, int numEmployees);
void addEmployee(struct employee *empList, int *numEmployees);
void load_data(const char *filename, struct employee *empList, int *numEmployees);

// Function to print each employee
void printEmployee(const struct employee *empPtr) {
    printf("%-10s %-18s $%7.2f %10d\n", empPtr->firstName, empPtr->lastName, empPtr->salary, empPtr->id);
}

// Function to print the entire employee database
void printDB(const struct employee *empList, int numEmployees) {
    printf("%-10s %-18s %7s %10s\n", "NAME", "", "SALARY", "ID");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < numEmployees; i++) {
        printEmployee(&empList[i]);
    }
    printf("-------------------------------------------------\n");
    printf("Number of Employees = %d\n\n", numEmployees);
}

// Function to sort the database by employee ID
void sortDB(struct employee *empList, int numEmployees) {
    for (int i = 0; i < numEmployees - 1; i++) {
        for (int j = 0; j < numEmployees - i - 1; j++) {
            if (empList[j].id > empList[j + 1].id) {
                struct employee temp = empList[j];
                empList[j] = empList[j + 1];
                empList[j + 1] = temp;
            }
        }
    }
}

// Function to look up an employee by ID
void lookUpID(const struct employee *empList, int numEmployees) {
    int searchID;
    printf("Enter a 6-digit employee ID: ");
    scanf("%d", &searchID);
    bool found = false;

    for (int i = 0; i < numEmployees; i++) {
        if (empList[i].id == searchID) {
            printf("%-10s %-18s %7s %10s\n", "NAME", "", "SALARY", "ID");
            printf("-------------------------------------------------\n");
            printEmployee(&empList[i]);
            printf("-------------------------------------------------\n\n");
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Employee with that ID not found!\n\n");
    }
}

// Function to look up an employee by last name
void lookUpLastName(const struct employee *empList, int numEmployees) {
    char searchName[MAXNAME];
    printf("Enter the last name of the employee: ");
    scanf("%63s", searchName);
    bool found = false;

    for (int i = 0; i < numEmployees; i++) {
        if (strcasecmp(empList[i].lastName, searchName) == 0) {
            if (!found) {
                printf("%-10s %-18s %7s %10s\n", "NAME", "", "SALARY", "ID");
                printf("-------------------------------------------------\n");
            }
            printEmployee(&empList[i]);
            found = true;
        }
    }
    if (found) {
        printf("-------------------------------------------------\n\n");
    } else {
        printf("Employee with that last name not found!\n\n");
    }
}

// Function to add a new employee
void addEmployee(struct employee *empList, int *numEmployees) {
    struct employee newEmp;
    printf("Enter the new employee's details:\n");
    printf("First Name: ");
    scanf("%63s", newEmp.firstName);
    printf("Last Name: ");
    scanf("%63s", newEmp.lastName);
    printf("Salary: ");
    scanf("%f", &newEmp.salary);

    newEmp.id = empList[*numEmployees - 1].id + 1; // Assign a new ID
    empList[*numEmployees] = newEmp;
    (*numEmployees)++;
    printf("New employee added!\n\n");
}

// Function to load data from a file
void load_data(const char *filename, struct employee *empList, int *numEmployees) {
    if (open_file(filename) == -1) {
        printf("Error: Could not open file %s.\n", filename);
        return;
    }

    struct employee temp;
    while (read_int(&temp.id) == 0 &&
           read_string(temp.firstName, MAXNAME) == 0 &&
           read_string(temp.lastName, MAXNAME) == 0 &&
           read_float(&temp.salary) == 0) {

        if (temp.id < 100000 || temp.id > 999999 || temp.salary < 30000 || temp.salary > 150000) {
            printf("Skipping invalid entry: ID=%d, Name=%s %s, Salary=%.2f\n",
                   temp.id, temp.firstName, temp.lastName, temp.salary);
            continue;
        }

        empList[*numEmployees] = temp;
        (*numEmployees)++;

        if (*numEmployees >= MAXEMPLOYEES) {
            printf("Database full; cannot load more employees.\n");
            break;
        }
    }

    close_file();
}

// Main function
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    char *filename = argv[1];
    struct employee empList[MAXEMPLOYEES];
    int numEmployees = 0;

    // Load data from file
    load_data(filename, empList, &numEmployees);

    // Sort the database by ID after loading
    sortDB(empList, numEmployees);

    // Main menu loop
    int choice;
    while (true) {
        printf("Employee Database Menu:\n");
        printf("1. Print the Database\n");
        printf("2. Lookup by ID\n");
        printf("3. Lookup by Last Name\n");
        printf("4. Add an Employee\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                printDB(empList, numEmployees);
                break;
            case 2:
                lookUpID(empList, numEmployees);
                break;
            case 3:
                lookUpLastName(empList, numEmployees);
                break;
            case 4:
                addEmployee(empList, &numEmployees);
                sortDB(empList, numEmployees); // Keep sorted after adding
                break;
            case 5:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

