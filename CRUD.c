#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define USERDATA "userdata.txt"
#define MAX_INPUT_LEN 100

typedef struct employee {
    int unique_id;
    char name[20];
    int age;
} employee;

void createFileIfNotExists() {
    FILE *userFile = fopen(USERDATA, "r");
    if (userFile == NULL) {
        userFile = fopen(USERDATA, "w");
        fclose(userFile);
    } else {
        fclose(userFile);
    }
}

int isValidName(char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0; 
        }
    }
    return 1; 
}

int isValidAge(int age) {
    return (age > 0);  
}

int isValidId(int id) {
    return (id > 0);  
}

void create() {
    employee e;
    FILE *userFile;
    int id_exists = 0;

    userFile = fopen(USERDATA, "r");
    if (userFile != NULL) {
        int existing_id;
        char existing_name[20];
        int existing_age;
        printf("Enter the unique_id of employee: ");
        while (scanf("%d", &e.unique_id) != 1 || !isValidId(e.unique_id)) {
            printf("Invalid ID. Please enter a valid positive integer ID: ");
            clearInputBuffer();
        }
        while (fscanf(userFile, "%d,%19[^,],%d\n", &existing_id, existing_name, &existing_age) != -1) {
            if (existing_id == e.unique_id) {
                id_exists = 1;
                break;
            }
        }
        fclose(userFile);
    }
    if (id_exists) {
        printf("ID already exists.\n");
        return;
    }
    userFile = fopen(USERDATA, "a");
    if (userFile == NULL) {
        return;
    }
    getchar();  
    printf("Enter the name of employee: ");
    while (fgets(e.name, sizeof(e.name), stdin) != NULL) {
        e.name[strcspn(e.name, "\n")] = '\0';  
        if (isValidName(e.name)) {
            break;
        } else {
            printf("Invalid name. Please enter a valid name: ");
        }
    }
    printf("Enter the age of employee: ");
    while (scanf("%d", &e.age) != 1 || !isValidAge(e.age)) {
        printf("Invalid age. Please enter a valid positive integer age: ");
        clearInputBuffer();
    }
    fprintf(userFile, "%d,%s,%d\n", e.unique_id, e.name, e.age);
    printf("Employee created.\n");
    fclose(userFile);
}

void display() {
    FILE *userFile = fopen(USERDATA, "r");
    char mystring[100];
    if (userFile == NULL) {
        return;
    }
    printf("\nEmployee Data:\n");
    while (fgets(mystring, sizeof(mystring), userFile)) {
        printf("%s", mystring);
    }
    fclose(userFile);
}

void update() {
    FILE *userFile, *tempFile;
    employee e;
    int id, found = 0;

    userFile = fopen(USERDATA, "r");
    if (userFile == NULL) {
        return;
    }
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(userFile);
        return;
    }
    printf("Enter unique_id to update: ");
    while (scanf("%d", &id) != 1 || !isValidId(id)) {
        printf("Invalid ID. Please enter a valid positive integer ID: ");
        clearInputBuffer();
    }
    while (fscanf(userFile, "%d,%19[^,],%d\n", &e.unique_id, e.name, &e.age) != -1) {
        if (e.unique_id == id) {
            found = 1;
            printf("Enter the new name: ");
            getchar();
            while (fgets(e.name, sizeof(e.name), stdin) != NULL) {
                e.name[strcspn(e.name, "\n")] = '\0';  // Remove newline at end of string
                if (isValidName(e.name)) {
                    break;
                } else {
                    printf("Invalid name. Please enter a valid name: ");
                }
            }
            printf("Enter the new age: ");
            while (scanf("%d", &e.age) != 1 || !isValidAge(e.age)) {
                printf("Invalid age. Please enter a valid positive integer age: ");
                clearInputBuffer();
            }
        }
        fprintf(tempFile, "%d,%s,%d\n", e.unique_id, e.name, e.age);
    }
    fclose(userFile);
    fclose(tempFile);
    if (found) {
        remove(USERDATA);
        rename("temp.txt", USERDATA);
        printf("Employee updated.\n");
    } else {
        remove("temp.txt");
        printf("ID not found.\n");
    }
}

void delete() {
    FILE *userFile, *tempFile;
    employee e;
    int id, found = 0;

    userFile = fopen(USERDATA, "r");
    if (userFile == NULL) {
        return;
    }
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        fclose(userFile);
        return;
    }
    printf("Enter unique_id to delete: ");
    while (scanf("%d", &id) != 1 || !isValidId(id)) {
        printf("Invalid ID. Please enter a valid positive integer ID: ");
        clearInputBuffer();
    }
    while (fscanf(userFile, "%d,%19[^,],%d\n", &e.unique_id, e.name, &e.age) != -1) {
        if (e.unique_id == id) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%d,%s,%d\n", e.unique_id, e.name, e.age);
    }
    fclose(userFile);
    fclose(tempFile);
    if (found) {
        remove(USERDATA);
        rename("temp.txt", USERDATA);
        printf("Employee deleted.\n");
    } else {
        remove("temp.txt");
        printf("ID not found.\n");
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getChoice() {
    int choice;
    while (1) {
        printf("\nEnter Your Choice: ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("Invalid choice. Please enter a correct choice.\n");
        } else {
            break;
        }
    }
    return choice;
}

int main() {
    createFileIfNotExists();
    int choice;
    do {
        printf("\n1.CREATE");
        printf("\n2.DISPLAY");
        printf("\n3.UPDATE");
        printf("\n4.DELETE");
        printf("\n0.EXIT");

        choice = getChoice();  

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                update();
                break;
            case 4:
                delete();
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a correct choice.\n");
        }
    } while (choice != 0);
    return 0;
}
