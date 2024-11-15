#include <stdio.h>
#define LINE_LENGTH  81

int main(int argc, char const *argv[]){

  // Main shell loop
  miso_loop();

  return 0;
}


// Main Shell Loop
// Parts of the Shell loop
// 1.) Read
// 2.) Parse
// 3.) Execute
void miso_loop(){
  // This line variable will contain the command input
  char line[81];
  miso_read();
  miso_parse();
  miso_exe();
}