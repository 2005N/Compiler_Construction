#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define YES 1
#define NO 0

// Token structure definition
typedef struct {
    char type[15];
    char value[50];
} token;

// Function to create a new token
token newToken(const char *type, const char *value) {
    token t;
    snprintf(t.type, sizeof(t.type), "%s", type);
    snprintf(t.value, sizeof(t.value), "%s", value);
    return t;
}

// Function to handle lexical errors
void fail() {
    printf("Lexical error: invalid input.\n");
    exit(1);
}

// Function to recognize relational operators
token getRelationalOp() {
    int state = 0;
    char c;
    while (YES) {
        switch (state) {
            case 0:
                c = getchar();
                if (c == '<') state = 1;
                else if (c == '=') state = 5;
                else if (c == '>') state = 6;
                else fail();
                break;
            case 1:
                c = getchar();
                if (c == '=') state = 2;
                else if (c == '>') state = 3;
                else state = 4;
                break;
            case 2:
                return newToken("relop", "LE");
            case 3:
                return newToken("relop", "NE");
            case 4:
                ungetc(c, stdin);
                return newToken("relop", "LT");
            case 5:
                return newToken("relop", "EQ");
            case 6:
                c = getchar();
                if (c == '=') state = 7;
                else state = 8;
                break;
            case 7:
                return newToken("relop", "GE");
            case 8:
                ungetc(c, stdin);
                return newToken("relop", "GT");
            default:
                fail();
                break;
        }
    }
}

// Function to recognize arithmetic operators
token getArithmeticOp() {
    int state = 0;
    char c;
    while (YES) {
        switch (state) {
            case 0:
                c = getchar();
                if (c == '+') state = 1;
                else if (c == '-') state = 2;
                else if (c == '*') state = 3;
                else if (c == '/') state = 4;
                else if (c == '%') state = 5;
                else fail();
                break;
            case 1:
                return newToken("arithop", "+");
            case 2:
                return newToken("arithop", "-");
            case 3:
                return newToken("arithop", "*");
            case 4:
                return newToken("arithop", "/");
            case 5:
                return newToken("arithop", "%");
            default:
                fail();
                break;
        }
    }
}

// Function to recognize assignment operators
token getAssignmentOp() {
    int state = 0;
    char c;
    while (YES) {
        switch (state) {
            case 0:
                c = getchar();
                if (c == ':') state = 1;
                else if (c == '+') state = 3;
                else if (c == '-') state = 5;
                else if (c == '*') state = 7;
                else if (c == '/') state = 9;
                else if (c == '%') state = 11;
                else fail();
                break;
            case 1:
                c = getchar();
                if (c == '=') state = 2;
                else fail();
                break;
            case 2:
                return newToken("assignop", ":=");
            case 3:
                c = getchar();
                if (c == '=') state = 4;
                else fail();
                break;
            case 4:
                return newToken("assignop", "+=");
            case 5:
                c = getchar();
                if (c == '=') state = 6;
                else fail();
                break;
            case 6:
                return newToken("assignop", "-=");
            case 7:
                c = getchar();
                if (c == '=') state = 8;
                else fail();
                break;
            case 8:
                return newToken("assignop", "*=");
            case 9:
                c = getchar();
                if (c == '=') state = 10;
                else fail();
                break;
            case 10:
                return newToken("assignop", "/=");
            case 11:
                c = getchar();
                if (c == '=') state = 12;
                else fail();
                break;
            case 12:
                return newToken("assignop", "%=");
            default:
                fail();
                break;
        }
    }
}

// Function to recognize separators
token getSeparator() {
    char c = getchar();
    if (c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}') {
        char value[2] = {c, '\0'};
        return newToken("separator", value);
    }
    fail();
}

// Function to recognize identifiers
token getId() {
    int state = 0;
    char c;
    char buffer[50];
    int i = 0;

    while (YES) {
        switch (state) {
            case 0:
                c = getchar();
                if (islower(c)) {
                    buffer[i++] = c;
                    state = 1;
                } else {
                    fail();
                }
                break;

            case 1:
                c = getchar();
                if (isalnum(c)) {
                    buffer[i++] = c;
                } else {
                    ungetc(c, stdin);
                    buffer[i] = '\0';
                    return newToken("Identifier", "ID");
                }
                break;

            default:
                fail();
                break;
        }
    }
}

int main() {
    printf("Enter input: ");
    token result;

    char c = getchar();
    ungetc(c, stdin);

    if (c == '<' || c == '=' || c == '>') {
        result = getRelationalOp();
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        result = getArithmeticOp();
    } else if (c == ':' || c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        result = getAssignmentOp();
    } else if (c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}') {
        result = getSeparator();
    } else if (islower(c)) {
        result = getId();
    } else {
        fail();
    }

    printf("Token Type: %s, Token Value: %s\n", result.type, result.value);
    return 0;
}
