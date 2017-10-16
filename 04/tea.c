#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum bool {true = 1, false = 0} bool;
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

void encryptTwoValues(unsigned int *value, unsigned int* key) {
  // This is where raw encryption takes place.
  unsigned int sum = 0;
  unsigned int delta = 0x9e3779b9;
  for(int i = 0; i < 32; i++) {
    value[0] += ((value[1] << 4) + key[0]) ^ (value[1] + sum) ^ ((value[1] >> 5) + key[1]);
    value[1] += ((value[0] << 4) + key[2]) ^ (value[0] + sum) ^ ((value[0] >> 5) + key[3]);
  }
}

void encryptStdStreamOnTheFly(unsigned int *key) {
  char inputChar;
  bool endOfFile = false;
  unsigned int *value = malloc(2 * sizeof(int));
  while(!endOfFile) {
    int i = 0;
    for(; i < 2 * sizeof(int); i++) {
      if(scanf("%c", &((unsigned char*)value)[i]) == EOF) {
        endOfFile = true;
        break;
      }
    }
    if(endOfFile) {
      // Pad with zeros to a full chunk
      for(; i < 2 * sizeof(int); i++) {
        ((unsigned char*)value)[i] = 0;
      }
    }
    fprintf(stderr, "(0x%08x, 0x%08x) -> ", value[0], value[1]);
    encryptTwoValues(value, key);
    fprintf(stderr, "(0x%08x, 0x%08x)\n", value[0], value[1]);
    printf("%08x%08x", value[0], value[1]);
  }
  free(value);
}

unsigned int *parseKey(char *rawKey) {
  unsigned int *key = calloc(4, sizeof(int));
  fprintf(stderr, "Note: Interpreting the key as\n");
  fprintf(stderr, "      0x");
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < sizeof(int); j++) {
      key[i] |= ((unsigned int)rawKey[j + i * 4]) << 8 * (sizeof(int) - 1 - j);
    }
    fprintf(stderr, "%08x", key[i]);
  }
  fprintf(stderr, "\n");
  return key;
}

void cleanupKey(unsigned int *key) {
  free(key);
  key = NULL;
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
    fprintf(stderr, "Error: Decrypting not implemented\n");
    // TODO: Implement decryption
    return 1;
  }
  fprintf(stderr, "Note: Finished!\n");
  cleanupKey(key);
  return 0;
}

