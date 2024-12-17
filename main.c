#include <stdio.h>     // For printf(), fprintf(), perror(), fgets()
#include <stdlib.h>    // For malloc(), free(), exit()
#include <string.h>    // For strcmp(), strtok(), strlen()
#include <sys/types.h> // For pid_t
#include <sys/wait.h>  // For waitpid()
#include <unistd.h>    // For fork(), execvp(), and chdir()
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
}

//* Parts of the Shell loop
// miso_read - Reads the command from standard input
//           - Uses fgets to get user input
//           - Only gets an input string 80 chars long
//           - Calls strTrim to format input
void miso_read(char *line);
void miso_read(char *line) {
  fgets(line, LINE_LENGTH, stdin);
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
  int tokenLength = 10;

  char *token;
  char delim[] = " \t\r\n\a";
  int position = 0;

  token = strtok(line, delim);

  // Tokenizing the string
  while (token != NULL) {
    if (position >= tokenLength - 1) {
      tokenLength *= 2;
      tokens = realloc(tokens, tokenLength * sizeof(char *));
    }
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

// 1.) Read - Read the command from standard input
// 2.) Parse - Separate the command string into a program and arguments
// 3.) Execute - Run the parsed command

// buitlin shell commands
int miso_cd(char **args);
int miso_help(char **args);
int miso_exit(char **args);
/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {"cd", "help", "exit"};
int (*builtin_func[])(char **) = {&miso_cd, &miso_help, &miso_exit};

int miso_num_builtins() { return sizeof(builtin_str) / sizeof(char *); }
// Built in function implementations

/*
  Built-in function: miso_cd
  --------------------------
  Changes the current working directory to the one specified in the arguments.

  Parameters:
    - args: An array of strings (command + arguments).
      - args[0]: The command itself ("cd").
      - args[1]: The target directory.

  Functionality:
    - If no argument is provided (`args[1] == NULL`), it prints an error.
    - If `chdir` fails (e.g., the directory doesn't exist), it prints an error
  using `perror`.

  Return:
    - Returns 1 to indicate the shell should continue running.

  Example:
    - Input: "cd /home"
      - args[0] = "cd"
      - args[1] = "/home"
      - chdir("/home") changes the current working directory to "/home".
*/
int miso_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "miso: expected argument to \"cd\"\n ");
  } else {
    if (chdir(args[1]) != 0) {
      perror("miso");
    }
  }
  return 1;
}

int miso_help(char **args) {
  int i;
  printf("Antonio Hernandez's MISO\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i = 0; i < miso_num_builtins(); i++) {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}
int miso_exit(char **args) { return 0; }

// mis0_exe - Executes the commands
int miso_exe(char **args);
int miso_exe(char **args) {
  int i;

  if (args[0] == NULL) {
    // An empty command was entered.
    return 1;
  }

  for (i = 0; i < miso_num_builtins(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return miso_launch(args);
};

//* Main Shell Loop
void miso_loop();
void miso_loop() {
  int status; // Keep track of the current status of the shell
  int tokenLength = 5;
  // This line variable will contain the entire command input
  char line[LINE_LENGTH];
  do {
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
    // for (int i = 0; tokens[i] != NULL; i++) {
    //   printf("%s\n", tokens[i]);
    // }
    // Line Now Parsed and commands are ready to be executed

    status = miso_exe(tokens);

    free(tokens);
    /* code */
  } while (status);
};

int main() {
  printf("Welcome to Antonio Hernandez's MISO Shell!\n");
  miso_loop(); // Run the shell loop
  return 0;
}
