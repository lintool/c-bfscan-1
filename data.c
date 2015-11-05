#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "constants.h"

void init_sharedata() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int i=0;
  fp = fopen(DATA_PATH "doc_id.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading tweetids from doc_id.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tweetids[i++] = atol(line);
    if (i % 1000000 == 0 ) printf("  %d tweetids...\n", i);
  }
  printf("Total of %d tweetids read\n\n", i);
  fclose(fp);

  i=0;
  fp = fopen(DATA_PATH "doc_length.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading doclengths from doc_length.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d lengths...\n", i);
  }
  printf("Total of %d doclengths read\n\n", i);
  fclose(fp);

  i=0;
  fp = fopen(DATA_PATH "cf_table.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading cfs from cf_table.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    cf[i++] = atoi(line);
    if (i % 1000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);
  fclose(fp);

  if (line) {
    free(line);
  }

  int c = 1;
  for (; c < SCORE_MAPPING_SIZE; c ++) {
    score_mapping[c] = log(c * SCORE_MAPPING_JUMP);
  }
}

void init_pos() {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int i=0;
  fp = fopen(DATA_PATH "all_terms.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading collection from all_terms.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection_pos[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms read\n\n", i);
  fclose(fp);

  init_sharedata();

  if (line) {
    free(line);
  }
}

void init_tf() {
  int adad = 2;
  long sdsd = 2;
  printf("size:%d\n", sizeof(adad));
  printf("size:%d\n", sizeof(sdsd));
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  int i=0;
  fp = fopen(DATA_PATH "all_terms_ordered.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading collection from all_terms_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    collection_tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d terms...\n", i);
  }
  printf("Total of %d terms ordered read\n\n", i);
  fclose(fp);

  i=0;
  fp = fopen(DATA_PATH "all_terms_tf.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }  
  printf("-> Reading tf from all_terms_tf.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    tf[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d tfs...\n", i);
  }
  printf("Total of %d tfs read\n\n", i);
  fclose(fp);

  i=0;
  fp = fopen(DATA_PATH "impact_score.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }  
  printf("-> Reading impact score from impact_score.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    impact_score[i++] = atoi(line);
    if (i % 10000000 == 0 ) printf("  %d impact scores...\n", i);
  }
  printf("Total of %d impact_score read\n\n", i);
  fclose(fp);

  i=0;
  int sum = 0;
  base[0] = 0;
  base_padding[0] = 0;
  fp = fopen(DATA_PATH "doc_length_ordered.txt", "r");
  if (fp == NULL) { printf("Error!\n"); exit(-1); }
  printf("-> Reading doclengths from doc_length_ordered.txt\n");
  while ((read = getline(&line, &len, fp)) != -1) {
    doclengths_ordered[i] = atoi(line);
    if (atoi(line) % BLOCK_SIZE == 0) {
      doclengths_ordered_padding[i] = atoi(line);
    } else {
      doclengths_ordered_padding[i] = atoi(line) + (BLOCK_SIZE - atoi(line) % BLOCK_SIZE);
    }
    if (i > 0) {
      base[i] = base[i - 1] + doclengths_ordered[i - 1];
      base_padding[i] = base_padding[i - 1] + doclengths_ordered_padding[i - 1];
    }
    sum += doclengths_ordered_padding[i++];
    if (i % 1000000 == 0 ) printf("  %d ordered lengths...\n", i);
  }
  printf("Total of %d doclengths ordered read\n\n", i);
  fclose(fp);

  collection_tf_padding = malloc(sum * sizeof(uint32_t));
  tf_padding = malloc(sum * sizeof(uint32_t));
  impact_score_padding = malloc(sum * sizeof(uint8_t));
  doc_pos = malloc(sum * sizeof(uint8_t));
  int base = 0;
  int i_padding = 0;
  int ii=0;
  int jj=0;
  int pos=0;
  for (ii = 0; ii < NUM_DOCS; ii ++) {
    for (jj = 0; jj < doclengths_ordered[ii]; jj ++) {
      collection_tf_padding[i_padding] = collection_tf[base + jj];
      tf_padding[i_padding] = tf[base + jj];
      impact_score_padding[i_padding] = impact_score[base + jj];
      doc_pos[i_padding] = pos % DOCS_BLOCK_SIZE;
      i_padding++;
    }
    for (jj = doclengths_ordered[ii]; jj < doclengths_ordered_padding[ii]; jj ++) {
      collection_tf_padding[i_padding] = 0;
      tf_padding[i_padding] = 0;
      impact_score_padding[i_padding] = 0;
      doc_pos[i_padding] = pos % DOCS_BLOCK_SIZE;
      i_padding++;
    }
    pos ++;
    base += doclengths_ordered[ii];
  }

  init_sharedata();

  if (line) {
    free(line);
  }
}