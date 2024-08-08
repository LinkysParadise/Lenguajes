
#include <stdio.h>
#include <string.h>

int main() {
    char line[] = "q0 q1 q2  q3";
    char* token = strtok(line, " ");

    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " ");
    }

    return 0;
}
//texto que añadí

