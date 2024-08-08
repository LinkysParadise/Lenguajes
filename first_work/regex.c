#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_ALPHABET 30
#define MAX_TRANSITIONS 1000

typedef struct {
    char state[10];
} State;

typedef struct {
    char symbol;
} Symbol;

typedef struct {
    State currentState;
    char symbol;
    State nextState;
} Transition;

State states[MAX_STATES]; // Conjunto de estados
Symbol alphabet[MAX_ALPHABET]; //Alfabeto Sigma
State initialState; //Estado inicial (q0)
State finalStates[MAX_STATES]; // Conjunto de estados finales
Transition transitions[MAX_TRANSITIONS]; // Conjunto de transiciones

int numStates = 0, numAlphabet = 0, numFinalStates = 0, numTransitions = 0;

void trimNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}



void readConfiguration(char* filename) {
    FILE *file = fopen(filename, "r"); // Abrir en modo de lectura 

    //Case file doesn't exists or Error in opening
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    char line[600];

    // Read states
    fgets(line, sizeof(line), file);
    trimNewline(line); 
    char* token = strtok(line, " ");
    while (token != NULL) {
        printf("States: %s \n",token);
        strcpy(states[numStates++].state, token);
        token = strtok(NULL, " ");
    }

    // Read alphabet
    fgets(line, sizeof(line), file);
    trimNewline(line); 
    token = strtok(line, " ");
    while (token != NULL) {
        printf("Symbols: %c \n",token[0]);
        alphabet[numAlphabet++].symbol = token[0];
        token = strtok(NULL, " ");
    }

    // Read initial state
    fgets(line, sizeof(line), file);
    trimNewline(line); 
    sscanf(line, "%s", initialState.state);
    printf("Initial State: %s \n",initialState.state);


    // Read final states
    fgets(line, sizeof(line), file);
    trimNewline(line); 
    token = strtok(line, " ");
    while (token != NULL) {
        printf("Final States: %s \n",token);
        strcpy(finalStates[numFinalStates++].state, token);
        token = strtok(NULL, " ");
    }
    printf("Transicions \n");


    // Read transitions
    while (fgets(line, sizeof(line), file)) {
        trimNewline(line); 
        Transition t;
        sscanf(line, "%s %c %s", t.currentState.state, &t.symbol, t.nextState.state);
        printf("Actual : %s, Symbol: %c, Next: %s \n",t.currentState.state, t.symbol, t.nextState.state);
        transitions[numTransitions++] = t;
    }

    fclose(file);
}
int isFinalState(State LastState) {
    printf("LastState: %s\n", LastState.state);
    for (int i = 0; i < numFinalStates; i++) { 
        printf("FinalState: %s\n", finalStates[i].state);
        printf("%d \n", strcmp(finalStates[i].state, LastState.state));
        if (strcmp(finalStates[i].state, LastState.state) == 0) {
            printf("Lo logré\n");
            return 1;
        }
    }
    printf("Fracasé\n");

    return 0;
}

State getNextState(State currentState, char symbol) {
    for (int i = 0; i < numTransitions; i++) {
        if (strcmp(transitions[i].currentState.state, currentState.state) == 0 && transitions[i].symbol == symbol) {
            return transitions[i].nextState;
        }
    }
    State emptyState;
    printf("Devolveré un empty");
    strcpy(emptyState.state, ""); // Return an empty state if no transition is found
    return emptyState;
}

int isAccepted(char* word) {
    State currentState = initialState;
    for (int i = 0; i < strlen(word); i++) {
        printf("CurrentState: %s \n", currentState.state);
        printf("CurrentLetter: %c \n", word[i]);
        currentState = getNextState(currentState, word[i]);
        printf("I'm going to: %s \n", currentState.state);
        if (strcmp(currentState.state, "") == 0) {
            return 0; // Transition not found
        }
    }
    return isFinalState(currentState);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Llamado incorrecto, se hace de la forma: %s <config_file> <word>\n", argv[0]);
        return 1;
    }

    char* configFile = argv[1];
    char* word = argv[2];

    readConfiguration(configFile);

    if (isAccepted(word)) {
        printf("The word '%s' is accepted by the DFA.\n", word);
    } else {
        printf("The word '%s' is not accepted by the DFA.\n", word);
    }

    return 0;
}
