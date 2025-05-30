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

// Function to recognize signed integers and real numbers
token getNum() {
    int state = 0;
    char c;
    char buffer[50];
    int i = 0;

    while (YES) {
        switch (state) {
            case 0:
                c = getchar();
                if (c == '+' || c == '-') {
                    buffer[i++] = c;
                    state = 1;
                } else if (isdigit(c)) {
                    buffer[i++] = c;
                    state = 2;
                } else {
                    fail();
                }
                break;

            case 1:
                c = getchar();
                if (isdigit(c)) {
                    buffer[i++] = c;
                    state = 2;
                } else {
                    fail();
                }
                break;

            case 2:
                c = getchar();
                if (isdigit(c)) {
                    buffer[i++] = c;
                } else if (c == '.') {
                    buffer[i++] = c;
                    state = 3;
                } else {
                    ungetc(c, stdin);
                    buffer[i] = '\0';
                    return newToken("Integer", buffer);
                }
                break;

            case 3:
                c = getchar();
                if (isdigit(c)) {
                    buffer[i++] = c;
                    state = 4;
                } else {
                    fail();
                }
                break;

            case 4:
                c = getchar();
                if (isdigit(c)) {
                    buffer[i++] = c;
                } else {
                    ungetc(c, stdin);
                    buffer[i] = '\0';
                    return newToken("Real num", buffer);
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
    
    if (isdigit(c) || c == '+' || c == '-') {
        result = getNum();
    } else {
        fail();
    }

    printf("Token Type: %s, Token Value: %s\n", result.type, result.value);
    return 0;
}

