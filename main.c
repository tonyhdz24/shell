#include <stdio.h>
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
void miso_parse(char *line);
void miso_parse(char *line) {
  char *token;

  token = strtok(line, " ");
  while (token != NULL) {
    printf("\n%s", token);
    
  }
};

// 1.) Read - Read the command from standard input
// 2.) Parse - Separate the command string into a program and arguments
// 3.) Execute - Run the parsed command

//* Main Shell Loop
void miso_loop();
void miso_loop() {
  // This line variable will contain the entire command input
  char line[LINE_LENGTH];
  // cmd will contain just the command
  char cmd[LINE_LENGTH / 2];

  printf("$ ");
  // Read the command from standard input
  miso_read(line);
  //? DEBUG - We now have the user input line
  printf("%s\n", line);
  // Separate the command string into a program and arguments
  miso_parse(line);
  // miso_exe();
};

int main() {
  int shellStatus = 1;
  // Main shell loop
  while (shellStatus) {
    miso_loop();
  }

  return 0;
};
