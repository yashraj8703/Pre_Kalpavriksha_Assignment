#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERDATA "userdata.txt"

typedef struct employee {
    int unique_id;
    char name[20];
    int age;
} employee;

void checkFileExistence() {
    FILE *userFile = fopen(USERDATA, "r");
    if (userFile == NULL) {
        userFile = fopen(USERDATA, "w");
        fclose(userFile);
    } else {
        fclose(userFile);
    }
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
        scanf("%d", &e.unique_id);
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
    scanf("%[^\n]s", e.name);
    getchar();
    printf("Enter the age of employee: ");
    scanf("%d", &e.age);
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
    scanf("%d", &id);
    while (fscanf(userFile, "%d,%19[^,],%d\n", &e.unique_id, e.name, &e.age) != -1) {
        if (e.unique_id == id) {
            found = 1;
            printf("Enter the new name: ");
            getchar();
            scanf("%[^\n]s", e.name);
            getchar();
            printf("Enter the new age: ");
            scanf("%d", &e.age);
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
    scanf("%d", &id);
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

int main() {
    checkFileExistence();
    int choice;
    do {
        printf("\n1.CREATE");
        printf("\n2.DISPLAY");
        printf("\n3.UPDATE");
        printf("\n4.DELETE");
        printf("\n0.EXIT");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);
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
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}