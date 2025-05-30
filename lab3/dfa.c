#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STATES 10
#define MAX_SYMBOLS 2
// Structure for DFA
typedef struct {
int num_states;
int num_symbols;
int transition[MAX_STATES][MAX_SYMBOLS];
bool final_states[MAX_STATES];
} DFA;
// Initialize DFA
void initialize_dfa(DFA *dfa, int num_states, int num_symbols) {
dfa->num_states = num_states;
dfa->num_symbols = num_symbols;
for (int i = 0; i < MAX_STATES; i++) {
dfa->final_states[i] = false;
for (int j = 0; j < MAX_SYMBOLS; j++) {
dfa->transition[i][j] = -1;
}
}
}

// Read DFA from file
void read_dfa_from_file(DFA *dfa, const char *filename) {
FILE *file = fopen(filename, "r");
if (!file) {
perror("Failed to open file");
exit(EXIT_FAILURE);
}
int num_states;
fscanf(file, "%d", &num_states);
initialize_dfa(dfa, num_states, MAX_SYMBOLS);
char line[256];
fgets(line, sizeof(line), file); // Skip the line with number of states
fgets(line, sizeof(line), file); // Read the line containing final states
//Read final states
char *token = strtok(line, "{ } , ");
while (token != NULL) {
int final_state = atoi(token);
dfa->final_states[final_state] = true;
token = strtok(NULL, " ");
}
// Read transitions
for (int i = 0; i < num_states; i++) {
int state;
fscanf(file, "%d", &state);
for (int symbol = 0; symbol < MAX_SYMBOLS; symbol++) {
int next_state;
fscanf(file, "%d", &next_state);
dfa->transition[state][symbol] = next_state;
}
}
fclose(file);
}
// Simulate DFA
bool simulate_dfa(DFA *dfa, const char *input) {
int current_state = 0; // Assume starting state is 0
printf("%d", current_state);
for (int i = 0; input[i] != '\0'; i++) {
int symbol = input[i] - '0'; 
if (symbol < 0 || symbol >= dfa->num_symbols) {
printf("Invalid input symbol detected!\n");
return false;
}
current_state = dfa->transition[current_state][symbol];
printf(" -> %d", current_state);
}
printf("\n");
return dfa->final_states[current_state]; 
}

int main() {
DFA dfa;
read_dfa_from_file(&dfa, "input.txt");
char input[100];
printf("Enter input string: ");
scanf("%s", input);
if (simulate_dfa(&dfa, input)) {
printf("Input string is accepted by the DFA.\n");
} else {
printf("Input string is rejected by the DFA.\n");
}
return 0;
}