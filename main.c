#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[]) {

  // Beginning of REPL
  while (1) {
    printf("~ ");

    // Allocate Memory for User Input
    char *inputStr = malloc(100 * sizeof(char));
    if (inputStr == NULL) {
      perror("Unable to allocate memory");
      exit(1);
    }
    // Getting user input
    if (fgets(inputStr, 100, stdin) != NULL) {
      // removes traling \n from string
      inputStr[strcspn(inputStr, "\n")] = '\0';
    };

    char *cmd = malloc(50 * sizeof(char));
    char *arg = malloc(50 * sizeof(char));

    int inputStrLength = strlen(inputStr);
    int c = 0;

    // Parse command
    for (c; inputStr[c] != ' '; c++) {
      cmd[c] = inputStr[c];
    }
    cmd[c] = '\0';
    c++;
    // Parse Argument
    int argIndex = 0;
    for (c; inputStr[c] != '\0'; c++) {
      arg[argIndex] = inputStr[c];
      argIndex++;
    }
    arg[c] = '\0';

    //* Handling Commands
    if (strcmp(cmd, "exit") == 0) {
      printf("***Good-Bye***\n");
      exit(0);
    } else if (strcmp(cmd, "echo") == 0) {
      printf("%s \n", arg);
    } else if (strcmp(cmd, "type") == 0) {
      printf("%s is a shell builtin", cmd);
    } else {
      printf("%s: command not found\n", inputStr);
    }
    // free allocated memory
    free(cmd);
    free(arg);
    free(inputStr);
  }
  return 0;
}
