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
    printf("Lexical error: invalid arithmetic operator.\n");
    exit(1);
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

int main() {
    printf("Enter an arithmetic operator: ");
    token result = getArithmeticOp();
    printf("Token Type: %s, Token Value: %s\n", result.type, result.value);
    return 0;
}
