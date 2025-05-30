#include <stdio.h>
#include <stdlib.h>
#define YES 1
#define NO 0

// Token structure definition
typedef struct {
    char type[10];
    char value[3];
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
    printf("Lexical error: invalid assignment operator.\n");
    exit(1);
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

int main() {
    printf("Enter an assignment operator: ");
    token result = getAssignmentOp();
    printf("Token Type: %s, Token Value: %s\n", result.type, result.value);
    return 0;
}
