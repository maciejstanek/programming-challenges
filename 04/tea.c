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
  unsigned int sum = 0;
  unsigned int delta = 0x9e3779b9;
  for(int i = 0; i < 32; i++) {
    sum += delta;
    value[0] += ((value[1] << 4) + key[0]) ^ (value[1] + sum) ^ ((value[1] >> 5) + key[1]);
    value[1] += ((value[0] << 4) + key[2]) ^ (value[0] + sum) ^ ((value[0] >> 5) + key[3]);
  }
}

void encryptStdStreamOnTheFly(unsigned int *key) {
  char inputChar;
  bool endOfFile = false;
  unsigned int value[2];
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

bool isHexChar(unsigned char c) {
  if(c >= 'A' && c <= 'F') {
    return true;
  }
  if(c >= 'a' && c <= 'f') {
    return true;
  }
  if(c >= '0' && c <= '9') {
    return true;
  }
  return false;
}

void decryptTwoValues(unsigned int *value, unsigned int* key) {
  unsigned int sum = 0xC6EF3720;
  unsigned int delta = 0x9e3779b9;
  for(int i = 0; i < 32; i++) {
    value[1] -= ((value[0] << 4) + key[2]) ^ (value[0] + sum) ^ ((value[0] >> 5) + key[3]);
    value[0] -= ((value[1] << 4) + key[0]) ^ (value[1] + sum) ^ ((value[1] >> 5) + key[1]);
    sum -= delta;
  }
}

int decryptStdStreamOnTheFly(unsigned int *key) {
  unsigned char inputChunk[2 * sizeof(int)];
  int status = 0;

  bool stopLoop = false;
  while(!stopLoop) {
    unsigned char inputHex[2 * 2 * sizeof(int)];
    for(int i = 0; i < 2 * 2 * sizeof(int); i++) {
      if(scanf("%c", &inputHex[i]) == EOF) {
        stopLoop = true;
        if (i > 0) {
          status = 1;
          fprintf(stderr, "Error: Wrong chunk size. Ciphertext is\n");
          fprintf(stderr, "       required to have a size equal to\n");
          fprintf(stderr, "       a mutiple of %lu hexadecimal characters.\n", 2 * 2 * sizeof(int));
        }
        break;
      }
      if(!isHexChar(inputHex[i])) {
        stopLoop = true;
        status = 1;
        fprintf(stderr, "Error: Ciphertext has to be written using\n");
        fprintf(stderr, "       hexadecimal characters only.\n");
        break;
      }
    }
    if(!stopLoop) {
      unsigned char hexBuffer[2 * sizeof(int) + 1];
      hexBuffer[2 * sizeof(int)] = '\0';
      unsigned int *parsedValues = malloc(2 * sizeof(int));
      for(int i = 0; i < 2; i++) {
        // Copy the buffer to evaluate it as a hex
        strncpy(hexBuffer, &inputHex[2 * sizeof(int) * i], 2 * sizeof(int));
        sscanf(hexBuffer, "%08x", &parsedValues[i]);
      }
      decryptTwoValues(parsedValues, key);
      for(int i = 0; i < 2 * 2 * sizeof(int); i++) {
        printf("%c", ((unsigned char*)parsedValues)[i]);
      }
      free(parsedValues);
    }
  }
  return status;
}

int main(int argc, char **argv) {
  int status = 0;
  printBanner();
  status = parseArgs(argc, argv);
  if(status) {
    return status;
  }
  unsigned int *key = parseKey(argv[2]);
  if(algorithmDirection == ENCODE) {
    fprintf(stderr, "Note: Encrypting...\n");
    encryptStdStreamOnTheFly(key);
  } else {
    fprintf(stderr, "Note: Decrypting...\n");
    status = decryptStdStreamOnTheFly(key);
  }
  fprintf(stderr, "Note: Finished!\n");
  cleanupKey(key);
  return status;
}

