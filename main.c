#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 81

// Removes trailing newline of a string
void strTrim(char *);
void strTrim(char *str) {
  int idx = 0;
  // Scan string until we reach the end '\0'
  while (str[idx] != '\0') {
    idx++;
  }
  // Newline char is right before but now become the end
  str[idx - 1] = '\0';
};

//* Parts of the Shell loop
// miso_read - Reads the command from standard input
//           - Uses fgets to get user input
//           - Only gets an input string 80 chars long
//           - Calls strTrim to format input
void miso_read(char *line);
void miso_read(char *line) {
  fgets(line, 80, stdin);
  // Removing the trailing newline character
  strTrim(line);
};

// miso_parse - Parse/Tokenize the input string separating the command string
//              into a program and arguments
//            - White spaces will be used as delimiters
void miso_parse(char **tokens, char *line);
void miso_parse(char **tokens, char *line) {
  // TODO:
  // This function will revieve a tokens array and an input string. It will take
  // the input and tokenize it storing each token in the tokens array.
  char *token;
  char delim[] = " \t\r\n\a";
  int position = 0;

  token = strtok(line, " ");

  // Tokenizing the string
  while (token != NULL) {
    tokens[position++] = token;
    token = strtok(NULL, " ");
  }
};

// 1.) Read - Read the command from standard input
// 2.) Parse - Separate the command string into a program and arguments
// 3.) Execute - Run the parsed command

//* Main Shell Loop
void miso_loop();
void miso_loop() {
  int tokenLength = 5;
  // This line variable will contain the entire command input
  char line[LINE_LENGTH];

  // Beginning of SHELL loop
  printf("$ ");

  // Read the command from standard input
  miso_read(line);

  // Tokens will be a dynamic array of strings
  char **tokens = malloc(5 * sizeof(char *));
  // Separate the command string into a program and arguments
  miso_parse(tokens, line);
  printf("\nINPUT LINE HAS BEEN PARSED\n");
  for (int i = 0; *tokens[i] != '\0'; i++) {
    printf("%s\n", tokens[i]);
  }

  // miso_exe();

  free(tokens);
};

int main() {
  int shellStatus = 1;
  // Main shell loop
  while (shellStatus) {
    miso_loop();
  }

  return 0;
};
