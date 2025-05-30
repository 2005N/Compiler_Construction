#include <stdio.h>
#include <ctype.h>
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

// Function to retract a character back to the input stream
void retract() {
    ungetc(getchar(), stdin);
}

// Function to handle lexical errors
void fail() {
    printf("Lexical error: invalid relational operator.\n");
    exit(1);
}

// Function to recognize relational operators
token getRelop() {
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
                else {
                    retract();
                    state = 4;
                }
                break;
            case 2:
                return newToken("relop", "LE");
            case 3:
                return newToken("relop", "NE");
            case 4:
                return newToken("relop", "LT");
            case 5:
                return newToken("relop", "EQ");
            case 6:
                c = getchar();
                if (c == '=') state = 7;
                else {
                    retract();
                    state = 8;
                }
                break;
            case 7:
                return newToken("relop", "GE");
            case 8:
                return newToken("relop", "GT");
            default:
                fail();
                break;
        }
    }
}

int main() {
    printf("Enter a relational operator: ");
    token result = getRelop();
    printf("Token Type: %s, Token Value: %s\n", result.type, result.value);
    return 0;
}
