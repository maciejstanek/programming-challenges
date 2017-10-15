#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {ENCODE, DECODE} algorithmDirection;

void printUsage() {
  printf("\n");
  printf("Usage: ./a.out <encode|decode> <key>\n");
  printf("\n");
  printf("       Pass plain text or encoded text\n");
  printf("       via 'stdin'. The program outputs\n");
  printf("       to 'stdout'. Ciphertext is in hex\n");
  printf("       numbers - not raw binary.\n");
}

void printBanner() {
  printf("TEA - a Tiny Encryption Algorithm\n");
}

char *readPlainText() {
  int stringLength = 1;
  char *string = malloc(sizeof(char));
  char inputChar;
  while(scanf("%c", &inputChar) != EOF) {
    // TODO: Change this uneffective way of allocating memory
    string[stringLength - 1] = inputChar;
    string = realloc(string, ++stringLength * sizeof(char));
  }
  string[stringLength] = '\0';
  return string;
}

int parseArgs(int argc, char **argv) {
  if(argc == 1) {
    printUsage();
    return 0;
  }
  if(argc != 3) {
    printf("Wrong number of arguments.\n");
    printUsage();
    return 1;
  }
  if(strcmp(argv[1], "encode") == 0) {
    algorithmDirection = ENCODE;
  } else if(strcmp(argv[1], "decode") == 0) {
    algorithmDirection = DECODE;
  } else {
    printf("Wrong algorithm direction.\n");
    printf("Allowed are 'encode' and 'decode'.\n");
    printUsage();
    return 1;
  }
  // TODO
  return 0;
}

int main(int argc, char **argv) {
  printBanner();
  if(parseArgs(argc, argv)) {
    return 1;
  }
  if(algorithmDirection == ENCODE) {
    printf("ENCODING\n");
    char *plainText = readPlainText();
    printf("(%s)\n", plainText);
    printf("(%d)\n", (unsigned)strlen(plainText));
  } else {
    printf("DECODING\n");
  }
  return 0;
}

