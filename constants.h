#include <stdint.h>
#define COLLECTION_POS_SIZE 203429861
#define COLLECTION_TF_SIZE 162603674
#define NUM_DOCS 16141812
#define NUM_TERMS 14327749
#define TOTAL_TERMS 203429861
#define DOC_UNIQUE_TERM_LENGTH 50
#define BLOCK_SIZE 8
#define DOCS_BLOCK_SIZE 6
#define NUM_DOCS_PADDING 16141812

#define MU 2500.0
#define SCORE_MAX 80764 // (1 + 140/(MU * (140 + 1) / (TOTAL_TERMS + 1))) * (MU / (1 + MU))
#define SCORE_MAPPING_JUMP 0.01
#define SCORE_MAPPING_SIZE (int)(SCORE_MAX / SCORE_MAPPING_JUMP) + 1
#define TOP_K 1000
#define NUM_TOPICS 49
// #define DATA_PATH "/fs/clip-twitter/ylwang/bfscan-statistics/All/"
#define DATA_PATH "/Users/ylwang/Desktop/Research-IR/Projects/SearchEfficiency/Data/All/"

int collection_pos[COLLECTION_POS_SIZE];
int collection_tf[COLLECTION_TF_SIZE];
unsigned char tf[COLLECTION_TF_SIZE];
unsigned char impact_score[COLLECTION_TF_SIZE];
uint32_t * collection_tf_padding;
uint8_t * impact_score_padding;
uint32_t * tf_padding;
unsigned char doclengths[NUM_DOCS];
unsigned char doclengths_ordered[NUM_DOCS];
unsigned char doclengths_ordered_padding[NUM_DOCS];
long tweetids[NUM_DOCS];
int cf[NUM_TERMS];
int base[NUM_DOCS];
int base_padding[NUM_DOCS];
uint8_t * doc_pos;
float score_mapping[SCORE_MAPPING_SIZE];
