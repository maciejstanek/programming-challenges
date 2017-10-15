#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {ENCODE, DECODE} algorithmDirection;

void printUsage() {
  fprintf(stderr, "\n");
  fprintf(stderr, "Usage: ./a.out <encrypt|decrypt> <key>\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "       Pass plain text or encrypted text\n");
  fprintf(stderr, "       via 'stdin'. The program outputs\n");
  fprintf(stderr, "       to 'stdout'. Ciphertext is in hex\n");
  fprintf(stderr, "       numbers - not raw binary.\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "       The key is required to be exactly\n");
  fprintf(stderr, "       %lu characters long. This means that\n", 4 * sizeof(int));
  fprintf(stderr, "       the key has %lu bits. All the characters\n", 4 * sizeof(int) * 8);
  fprintf(stderr, "       exceeding this length are trimmed.\n");
}

void printBanner() {
  fprintf(stderr, "+-------------------------------------+\n");
  fprintf(stderr, "|                                     |\n");
  fprintf(stderr, "|   TEA - Tiny Encryption Algorithm   |\n");
  fprintf(stderr, "|                                     |\n");
  fprintf(stderr, "+-------------------------------------+\n");
  fprintf(stderr, "\n");
  fprintf(stderr, "Note: https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm\n");
}

void encryptTwoValues(unsigned int *value1, unsigned int *value2, unsigned int* key) {
  // This is where raw encryption takes place.
  // TODO
}

void encryptStdStreamOnTheFly(unsigned int *key) {
  char inputChar;
  unsigned char inputBuffer[2 * sizeof(int)];
  enum {true = 1, false = 0} endOfFile = false;
  while(!endOfFile) {
    int i = 0;
    for(; i < 2 * sizeof(int); i++) {
      if(scanf("%c", &inputBuffer[i]) == EOF) {
        endOfFile = true;
        break;
      }
    }
    if(endOfFile) {
      // Pad with zeros to a full chunk
      for(; i < 2 * sizeof(int); i++) {
        inputBuffer[i] = 0;
      }
    }
    unsigned int value[2];
    for(int i = 0; i < 2; i++) {
      value[i] = 0;
      for(int j = 0; j < sizeof(int); j++) {
        value[i] |= inputBuffer[i * sizeof(int) + j] << 8 * (sizeof(int) - 1 - j);
      }
    }
    fprintf(stderr, "(0x%08x, 0x%08x) -> ", value[0], value[1]);
    encryptTwoValues(&value[0], &value[1], key);
    fprintf(stderr, "(0x%08x, 0x%08x)\n", value[0], value[1]);
  }
}

unsigned int *parseKey(char *rawKey) {
  unsigned int *key = calloc(4, sizeof(int));
  fprintf(stderr, "Note: Interpreting the key as\n");
  fprintf(stderr, "      0x");
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < sizeof(int); j++) {
      key[i] |= ((unsigned int)rawKey[j]) << 8 * (sizeof(int) - 1 - j);
    }
    fprintf(stderr, "%08x", key[i]);
  }
  fprintf(stderr, "\n");
}

int parseArgs(int argc, char **argv) {
  if(argc == 1) {
    printUsage();
    return 1;
  }
  if(argc != 3) {
    fprintf(stderr, "Error: Wrong number of arguments.\n");
    printUsage();
    return 1;
  }
  if(strcmp(argv[1], "encrypt") == 0) {
    algorithmDirection = ENCODE;
  } else if(strcmp(argv[1], "decrypt") == 0) {
    algorithmDirection = DECODE;
  } else {
    fprintf(stderr, "Error: Wrong algorithm direction.\n");
    printUsage();
    return 1;
  }
  if(strlen(argv[2]) < 4 * sizeof(int)) {
    fprintf(stderr, "Error: Wrong key size.\n");
    printUsage();
    return 1;
  }
  return 0;
}

int main(int argc, char **argv) {
  printBanner();
  if(parseArgs(argc, argv)) {
    return 1;
  }
  unsigned int *key = parseKey(argv[2]);
  if(algorithmDirection == ENCODE) {
    fprintf(stderr, "Note: Encrypting...\n");
    encryptStdStreamOnTheFly(key);
  } else {
    fprintf(stderr, "Note: Decrypting...\n");
  }
  return 0;
}

