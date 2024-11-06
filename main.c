#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char const *argv[]) {
  /* code */
  int isOn = 1;

  // Beginning of REPL
  while (isOn) {
    printf("~ ");
    // Getting user input
    char *inputStr = malloc(20 * sizeof(char));
    char *cmd = malloc(20 * sizeof(char));
    fgets(inputStr, sizeof(inputStr), stdin);
    // removes traling \n from string
    inputStr[strcspn(inputStr, "\n")] = '\0';

    int inputStrLength = strlen(inputStr);
    printf("Size of input => %d", inputStrLength);
    // Parse command
    for (int i = 0; i < 4; i++) {
      printf("%c\n", inputStr[i]);
    }

    //* Handling Commands
    // exit command
    // if (strcmp(inputStr, "exit 0") == 0) {
    //   printf("***Good-Bye***\n");
    //   isOn = 0;
    // } else if (strcmp(inputStr, "echo") == 0) {
    //   printf("%s", inputStr);
    // } else {
    //   printf("%s: command not found\n", inputStr);
    // }
  }

  return 0;
}
