#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VALID_SIZE 100

int calculate(int num1, int num2, char op) {
    if (op == '+') {
        return num1 + num2;
    } else if (op == '-') {
        return num1 - num2;
    } else if (op == '*') {
        return num1 * num2;
    } else if (op == '/') {
        if (num2 == 0) {
            printf("Error: Division by zero.\n");
            exit(1);
        }
        return num1 / num2;
    } else {
        printf("Error: Invalid operator '%c'.\n", op);
        exit(1);
    }
}

int calculator(char* validUserInputs) {
    int len = strlen(validUserInputs);
    int i = 0;
    int values[VALID_SIZE];
    char operators[VALID_SIZE];
    int valuesTop = -1, operatorsTop = -1;
    while (i < len) {
        if (isdigit(validUserInputs[i])) {
            int num = 0;
            while (i < len && isdigit(validUserInputs[i])) {
                num = num * 10 + (validUserInputs[i] - '0');
                i++;
            }
            values[++valuesTop] = num;
        }
        else if (validUserInputs[i] == '*' || validUserInputs[i] == '/') {
            char op = validUserInputs[i];
            i++; 
            int num = 0;
            while (i < len && isdigit(validUserInputs[i])) {
                num = num * 10 + (validUserInputs[i] - '0');
                i++;
            }
            int lastNum = values[valuesTop--];
            values[++valuesTop] = calculate(lastNum, num, op);
        }
        else if (validUserInputs[i] == '+' || validUserInputs[i] == '-') {
            operators[++operatorsTop] = validUserInputs[i];
            i++;
        }
        else {
            printf("Error: Invalid expression.\n");
            exit(1);
        }
    }
    while (operatorsTop >= 0) {
        int num2 = values[valuesTop--];
        int num1 = values[valuesTop--];
        char op = operators[operatorsTop--];
        values[++valuesTop] = calculate(num1, num2, op);
    }

    return values[valuesTop];
}

int main() {
    char userInputs[VALID_SIZE];
    
    printf("Enter a mathematical expression : ");
    fgets(userInputs, VALID_SIZE, stdin);
    for (int i = 0; i < VALID_SIZE; i++) {
        if (userInputs[i] == '\n' || userInputs[i] == '\r') {
            userInputs[i] = '\0';
            break;
        }
    }
    int len = strlen(userInputs);
    int newIndex = 0;

    for (int i = 0; i < len; i++) {
        if (isspace(userInputs[i])) {
            continue;
        }
        userInputs[newIndex++] = userInputs[i];
    }
    userInputs[newIndex] = '\0';
    if (strlen(userInputs) == 0) {
        printf("Error: Invalid expression.\n");
        return 0;
    }
    for (int i = 0; i < strlen(userInputs); i++) {
        if (!isdigit(userInputs[i]) && userInputs[i] != '+' && 
            userInputs[i] != '-' && userInputs[i] != '*' && userInputs[i] != '/') {
            printf("Error: Invalid expression.\n");
            return 0;
        }
    }

    int lastIndex = strlen(userInputs) - 1;
    if (userInputs[lastIndex] == '+' || userInputs[lastIndex] == '-' || 
        userInputs[lastIndex] == '*' || userInputs[lastIndex] == '/') {
        userInputs[lastIndex] = '\0';
    }
    int result = calculator(userInputs);
    printf("%d\n", result);
    return 0;
}