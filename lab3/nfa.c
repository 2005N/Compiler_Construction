#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STATES 10
#define MAX_SYMBOLS 2
#define MAX_TRANSITIONS 10

// Structure for NFA
typedef struct {
    int num_states;
    int num_symbols;
    int transitions[MAX_STATES][MAX_SYMBOLS][MAX_TRANSITIONS]; // Multiple transitions
    int num_transitions[MAX_STATES][MAX_SYMBOLS];              // Number of transitions per state and symbol
    bool final_states[MAX_STATES];
} NFA;

// Initialize NFA
void initialize_nfa(NFA *nfa, int num_states, int num_symbols) {
    nfa->num_states = num_states;
    nfa->num_symbols = num_symbols;
    for (int i = 0; i < MAX_STATES; i++) {
        nfa->final_states[i] = false;
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            nfa->num_transitions[i][j] = 0;
            for (int k = 0; k < MAX_TRANSITIONS; k++) {
                nfa->transitions[i][j][k] = -1;
            }
        }
    }
}

// Read NFA from file
void read_nfa_from_file(NFA *nfa, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    int num_states;
    fscanf(file, "%d", &num_states);
    initialize_nfa(nfa, num_states, MAX_SYMBOLS);

    char line[256];
    fgets(line, sizeof(line), file); // Skip the line with number of states
    fgets(line, sizeof(line), file); // Read the line containing final states

    // Read final states
    char *token = strtok(line, "{ },\n");
    while (token != NULL) {
        int final_state = atoi(token);
        nfa->final_states[final_state] = true;
        token = strtok(NULL, "{ },\n");
    }

    // Read transitions
    while (fgets(line, sizeof(line), file)) {
        int state;
        char symbol_0[128], symbol_1[128];
        sscanf(line, "%d %s %s", &state, symbol_0, symbol_1);

        // Parse transitions for symbol 0
        token = strtok(symbol_0, "{ },");
        while (token != NULL) {
            int next_state = atoi(token);
            int count = nfa->num_transitions[state][0];
            if (count < MAX_TRANSITIONS) {
                nfa->transitions[state][0][count] = next_state;
                nfa->num_transitions[state][0]++;
            }
            token = strtok(NULL, "{ },");
        }

        // Parse transitions for symbol 1
        token = strtok(symbol_1, "{ },");
        while (token != NULL) {
            int next_state = atoi(token);
            int count = nfa->num_transitions[state][1];
            if (count < MAX_TRANSITIONS) {
                nfa->transitions[state][1][count] = next_state;
                nfa->num_transitions[state][1]++;
            }
            token = strtok(NULL, "{ },");
        }
    }

    fclose(file);
}

// Recursive helper function to simulate NFA
bool simulate_nfa_recursive(NFA *nfa, int current_state, const char *input, int index) {
    if (input[index] == '\0') { // End of input
        return nfa->final_states[current_state];
    }

    int symbol = input[index] - '0'; // Convert character to integer (assumes binary input)
    if (symbol < 0 || symbol >= nfa->num_symbols) {
        printf("Invalid input symbol detected!\n");
        return false;
    }
    printf(" -> %d", current_state);
    // Check all transitions for the current state and symbol
    for (int i = 0; i < nfa->num_transitions[current_state][symbol]; i++) {
        int next_state = nfa->transitions[current_state][symbol][i];
        
        if (simulate_nfa_recursive(nfa, next_state, input, index + 1)) {
            return true;
        }
    }

    return false;
}

// Simulate NFA
bool simulate_nfa(NFA *nfa, const char *input) {
    return simulate_nfa_recursive(nfa, 0, input, 0); // Start from state 0
}

int main() {
    NFA nfa;
    read_nfa_from_file(&nfa, "input1.txt");

    char input[100];
    printf("Enter input string: ");
    scanf("%s", input);

    if (simulate_nfa(&nfa, input)) {
        printf("Input string is accepted by the NFA.\n");
    } else {
        printf("Input string is rejected by the NFA.\n");
    }

    return 0;
}

