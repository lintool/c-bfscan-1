#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "immintrin.h"
#include "include/constants.h"
#include "include/data.c"
#include "include/heap.c"

extern void init_tf(char *data_path);
int num_topics;
int num_docs;
int total_terms;

int main(int argc, const char* argv[]) {
  init_tf(argv[1]);

  int n, base, i, j, t;
  int cur;

  int jump = DOCS_BLOCK_SIZE;
  int indexsum; //, pos;

  __m256i collect_vec;
  int bits;
  int map[129];
  memset(map, 0, sizeof(map));
  map[128] = 7;
  map[64] = 6;
  map[32] = 5;
  map[16] = 4;
  map[8] = 3;
  map[4] = 2;
  map[2] = 1;
  // int score_pos;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  for (n = 0; n < num_topics; n ++) {
    heap h;
    heap_create(&h, 0, NULL);
    float* min_key;
    int* min_val;

    float scores[jump];
    float score;
    
    base = 0;
    if (topics[n][1] == 1) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }
  
        base += indexsum;
      }
    } else if (topics[n][1] == 2) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }
  
        base += indexsum;
      }
    } else if (topics[n][1] == 3) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        
        base += indexsum;
      }
    } else if (topics[n][1] == 4) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }

        base += indexsum;
      }
    } else if (topics[n][1] == 5) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }

        base += indexsum;
      }
    } else if (topics[n][1] == 6) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        
        base += indexsum;
      }
    } else if (topics[n][1] == 7) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
      __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }
      
        base += indexsum;
      }
    } else if (topics[n][1] == 8) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
      __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
      __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }
        
        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_8)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }

        base += indexsum;
      }
    } else if (topics[n][1] == 9) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
      __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
      __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);
      __m256i query_vec_9 = _mm256_set1_epi32(topics[n][10]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }
        
        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_8)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_9)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }
   
        base += indexsum;
      }
    } else if (topics[n][1] == 10) {
      __m256i query_vec_1 = _mm256_set1_epi32(topics[n][2]);
      __m256i query_vec_2 = _mm256_set1_epi32(topics[n][3]);
      __m256i query_vec_3 = _mm256_set1_epi32(topics[n][4]);
      __m256i query_vec_4 = _mm256_set1_epi32(topics[n][5]);
      __m256i query_vec_5 = _mm256_set1_epi32(topics[n][6]);
      __m256i query_vec_6 = _mm256_set1_epi32(topics[n][7]);
      __m256i query_vec_7 = _mm256_set1_epi32(topics[n][8]);
      __m256i query_vec_8 = _mm256_set1_epi32(topics[n][9]);
      __m256i query_vec_9 = _mm256_set1_epi32(topics[n][10]);
      __m256i query_vec_10 = _mm256_set1_epi32(topics[n][11]);

      for (i = 0; i + jump < num_docs; i += jump) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }
        
        indexsum = doclengths_ordered_padding[i] + doclengths_ordered_padding[i + 1] + doclengths_ordered_padding[i + 2] + doclengths_ordered_padding[i + 3] + doclengths_ordered_padding[i + 4] + doclengths_ordered_padding[i + 5] + doclengths_ordered_padding[i + 6] + doclengths_ordered_padding[i + 7] + doclengths_ordered_padding[i + 8] + doclengths_ordered_padding[i + 9];
        memset(scores, 0, sizeof(scores));
        for (j = 0; j < indexsum; j += 8) {
          cur = base + j;
          collect_vec = _mm256_loadu_si256(&collection_tf_padding[cur]);
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_1)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][2]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_2)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][3]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_3)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][4]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          } 
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_4)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][5]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_5)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][6]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_6)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][7]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_7)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][8]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_8)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][9]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_9)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][10]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
          bits = _mm256_movemask_ps(_mm256_castsi256_ps(_mm256_cmpeq_epi32(collect_vec, query_vec_10)));
          if (bits != 0) {
            int score_pos = cur + map[bits];
            int pos = doc_pos[cur >> 3];
            scores[pos] = scores[pos] + log(1 + tf_padding[score_pos] / (MU * (cf[topics[n][11]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i + pos] + MU));
          }
        }

        if (scores[0] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = scores[0];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[0] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = scores[0];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[1] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 1;
            float *scorez = malloc(sizeof(float)); *scorez = scores[1];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[1] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 1;
              float *scorez = malloc(sizeof(float)); *scorez = scores[1];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[2] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 2;
            float *scorez = malloc(sizeof(float)); *scorez = scores[2];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[2] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 2;
              float *scorez = malloc(sizeof(float)); *scorez = scores[2];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[3] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 3;
            float *scorez = malloc(sizeof(float)); *scorez = scores[3];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[3] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 3;
              float *scorez = malloc(sizeof(float)); *scorez = scores[3];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[4] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 4;
            float *scorez = malloc(sizeof(float)); *scorez = scores[4];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[4] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 4;
              float *scorez = malloc(sizeof(float)); *scorez = scores[4];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[5] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 5;
            float *scorez = malloc(sizeof(float)); *scorez = scores[5];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[5] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 5;
              float *scorez = malloc(sizeof(float)); *scorez = scores[5];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[6] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 6;
            float *scorez = malloc(sizeof(float)); *scorez = scores[6];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[6] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 6;
              float *scorez = malloc(sizeof(float)); *scorez = scores[6];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[7] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 7;
            float *scorez = malloc(sizeof(float)); *scorez = scores[7];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[7] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 7;
              float *scorez = malloc(sizeof(float)); *scorez = scores[7];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[8] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 8;
            float *scorez = malloc(sizeof(float)); *scorez = scores[8];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[8] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 8;
              float *scorez = malloc(sizeof(float)); *scorez = scores[8];
              heap_insert(&h, scorez, docid);
            }
          }
        }
        if (scores[9] > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i + 9;
            float *scorez = malloc(sizeof(float)); *scorez = scores[9];
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (scores[9] > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i + 9;
              float *scorez = malloc(sizeof(float)); *scorez = scores[9];
              heap_insert(&h, scorez, docid);
            }
          }
        }

        base += indexsum;
      }
    } else {
      for (i = 0; i < num_docs; i ++) {
        if (tweetids[i] > topics_time[n]) {
          base += doclengths_ordered_padding[i];
          continue;
        }

        score = 0;
        for (j = 0; j < doclengths_ordered_padding[i]; j ++) {
          for (t = 2; t < 2 + topics[n][1]; t ++) {
            if (collection_tf_padding[base + j] == topics[n][t]) {
              score += log(1 + tf_padding[base + j] / (MU * (cf[topics[n][t]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
            }
          }
        }

        if (score > 0) {
          int size = heap_size(&h);
          if (size < TOP_K) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score;
            heap_insert(&h, scorez, docid);
          } else {
            heap_min(&h, (void**)&min_key, (void**)&min_val);
            if (score > *min_key) {
              heap_delmin(&h, (void**)&min_key, (void**)&min_val);
              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score;
              heap_insert(&h, scorez, docid);
            }
          }
        }

        base += doclengths_ordered_padding[i];
      }
    }

    for (; i < num_docs; i++) {
      if (tweetids[i] > topics_time[n]) {
        base += doclengths_ordered_padding[i];
        continue;
      }

      score = 0;
      for (j = 0; j < doclengths_ordered_padding[i]; j ++) {
        for (t = 2; t < 2 + topics[n][1]; t ++) {
          if (collection_tf_padding[base + j] == topics[n][t]) {
            score += log(1 + tf_padding[base + j] / (MU * (cf[collection_tf_padding[base + j]] + 1) / (total_terms + 1))) + log(MU / (doclengths[i] + MU));
          }
        }
      }

      if (score > 0) {
        int size = heap_size(&h);
        if (size < TOP_K) {
          int *docid = malloc(sizeof(int)); *docid = i;
          float *scorez = malloc(sizeof(float)); *scorez = score;
          heap_insert(&h, scorez, docid);
        } else {
          heap_min(&h, (void**)&min_key, (void**)&min_val);
          if (score > *min_key) {
            heap_delmin(&h, (void**)&min_key, (void**)&min_val);
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score;
            heap_insert(&h, scorez, docid);
          }
        }
      }

      base += doclengths_ordered_padding[i];
    }

    int rank = TOP_K;
    while (heap_delmin(&h, (void**)&min_key, (void**)&min_val)) {
      // printf("MB%02d Q0 %ld %d %f AVXScan2_optimize\n", (n + 1), tweetids[*min_val], rank, *min_key);
      rank --;
    }

    heap_destroy(&h);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  // printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000) / num_topics);
  // printf("Throughput: %f qps\n", num_topics / time_spent);
}
