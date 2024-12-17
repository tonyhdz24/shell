#include <bits/waitflags.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 81

// Removes trailing newline of a string replacing it with a null character
void strTrim(char *);

void strTrim(char *str) {
  int strlength = strlen(str);
  // IF input str is vailid(has length greater than 1) scan string until newline
  // character is reached
  if (strlength > 0 && str[strlength - 1] == '\n') {
    // Replace trailing newLine character with null character
    str[strlength - 1] = '\0';
  }
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
  // Null terminating tokens Array
  tokens[position] = NULL;
};
int miso_launch(char **args) {
  pid_t pid, wpid; // Variables to hold process IDs
  int status;      // Stores child's exit status

  // Create a new process using fork()
  pid = fork();

  if (pid == 0) {
    // ====== CHILD PROCESS ======
    // The child process will execute the command specified in `args[0]`

    // Replace current process image with a new program
    if (execvp(args[0], args) == -1) {
      perror("miso");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // ====== ERROR FORKING ======
    // If fork() fails (e.g., system resources are low), print an error
    perror("miso");
  } else {
    // ====== PARENT PROCESS ======
    // The parent process will wait for the child process to finish execution

    do {
      // Wait for the child process to change state
      // - `pid`: the process ID of the child to wait for
      // - `&status`: where the child's status will be stored
      // - `WUNTRACED`: also return if the child is stopped (not terminated)
      wpid = waitpid(pid, &status, WUNTRACED);

      // Loop while the child:
      // - Has not exited normally (WIFEXITED(status))
      // - Has not been terminated by a signal (WIFSIGNALED(status)
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}

// mis0_exe - Executes the commands
void miso_exe(char **tokens);
void miso_exe(char **tokens) {};

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
  char **tokens = malloc(tokenLength * sizeof(char *));
  // Initializing elements in token array to NULL
  for (int i = 0; i < tokenLength; i++) {
    tokens[i] = NULL;
  }

  // Separate the command string into a program and arguments
  miso_parse(tokens, line);

  // Tokens is not properly populated with the tokenized input string!!!
  for (int i = 0; tokens[i] != NULL; i++) {
    printf("%s\n", tokens[i]);
  }
  // Line Now Parsed and commands are ready to be executed

  miso_exe(tokens);

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
