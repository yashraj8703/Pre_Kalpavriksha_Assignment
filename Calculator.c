#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VALID_SIZE 100

void remove_newline(char *str) {
    for (int i = 0; i < VALID_SIZE; i++) {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            break;
        }
    }
}

int get_string_length(char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

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

int precedence(char op) {
    if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    }
    return 0;
}

void remove_spaces(char *str) {
    int len = get_string_length(str);
    int newIndex = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || 
            str[i] == '\r' || str[i] == '\v' || str[i] == '\f') {
            continue;  
        }
        str[newIndex++] = str[i];  
    }
    str[newIndex] = '\0';  
}

int validate_expression(char *str) {
    
    if (get_string_length(str) == 0) {
        printf("Error: Invalid expression.\n");
        return 0;
    }

    int lastCharWasOperator = 0;
    for (int i = 0; i < get_string_length(str); i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '+' && 
            str[i] != '-' && str[i] != '*' && str[i] != '/') {
            printf("Error: Invalid character '%c'.\n", str[i]);
            return 0;  
        }

       
        if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && lastCharWasOperator) {
            printf("Error: Invalid expression (consecutive operators).\n");
            return 0;  
        }

       
        lastCharWasOperator = (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/');
    }

  
    int lastIndex = get_string_length(str) - 1;
    if (str[lastIndex] == '+' || str[lastIndex] == '-' || 
        str[lastIndex] == '*' || str[lastIndex] == '/') {
        str[lastIndex] = '\0';  
    }

    return 1; 
}

int calculator(char* validUserInputs) {
    int len = strlen(validUserInputs);
    int i = 0;
    int values[VALID_SIZE];
    char operators[VALID_SIZE];
    int valuesTop = -1, operatorsTop = -1;

    while (i < len) {
        
        if (validUserInputs[i] >= '0' && validUserInputs[i] <= '9') {
    int num = 0;
    while (i < len && validUserInputs[i] >= '0' && validUserInputs[i] <= '9') {
        num = num * 10 + (validUserInputs[i] - '0');
        i++;
    }
    values[++valuesTop] = num;
}
        
        else if (validUserInputs[i] == '+' || validUserInputs[i] == '-' || validUserInputs[i] == '*' || validUserInputs[i] == '/') {
            while (operatorsTop >= 0 && precedence(validUserInputs[i]) <= precedence(operators[operatorsTop])) {
                int num2 = values[valuesTop--];
                int num1 = values[valuesTop--];
                char op = operators[operatorsTop--];
                values[++valuesTop] = calculate(num1, num2, op);
            }
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
    
    printf("Enter a mathematical expression: ");
    fgets(userInputs, VALID_SIZE, stdin);

    remove_newline(userInputs);
       
    remove_spaces(userInputs);

    if (!validate_expression(userInputs)) {
        return 0;  
    }
    int result = calculator(userInputs);
    printf("%d\n", result);

    return 0;
}
