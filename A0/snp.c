#include <stdlib.h>
#include <stdio.h>

void sqrseq(int pos, int *seq, int lim, int *sqr, int sqrn) {
  int **nseql = (int**) malloc((lim - pos) * sizeof(int*));
  for(int i = pos; i < lim; i++) {
    nseql[i] = malloc(lim * sizeof(int));
    for(int j = 0; j < pos; j++) {
      nseql[i][j] = seq[j];
    }
    nseql[i][pos] = seq[i];
    int offset = -1;
    for(int j = pos + 1; j < lim; j++) {
      if(seq[i] == seq[j - 1])
        offset = 0;
      nseql[i][j] = seq[j + offset];
    }
    printf("SEQ");
    for(int j = 0; j < lim; j++) {
    printf(" (%d)", nseql[i][j]);
    }
    printf("\n");
  }
  free(seq);
  for(int i = pos; i < lim; i++) {
    free(nseql[i]);
  }
  free(nseql);
}

int main(int argc, char **argv) {
  if(argc < 2) {
    return 1;
  }
  int lim = atoi(argv[1]);
  if(lim < 2) {
    return 1;
  }
  int i = 1, i2 = 1;
  int *sqr = malloc(sizeof(int)), sqrn = 0;
  while(i2 <= 2 * lim - 1) {
    sqr = (int*) realloc(sqr, (sqrn + 1) * sizeof(int));
    sqr[sqrn++] = i2;
    i++;
    i2 = i * i;
  }
  int *seq = malloc(lim * sizeof(int));
  for(int i = 0; i < lim; i++) {
    seq[i] = i + 1;
  }
  sqrseq(0, seq, lim, sqr, sqrn);
  free(sqr);
  return 0;
}
