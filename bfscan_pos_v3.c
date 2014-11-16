#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "topics2011_reordered.h"
#include "constants.h"

extern void init_pos();

int main(int argc, const char* argv[]) {
  init_pos();

  int i=0, j=0;

  clock_t begin, end;
  double time_spent;
  begin = clock();

  int base = 0;
  float score1, score2;

  int n;

  for (n=0; n<42; n+=2) {
    base = 0;

    heap h1;
    heap_create(&h1,0,NULL);
    heap h2;
    heap_create(&h2,0,NULL);

    float* min_key;
    int* min_val;

    // int tf = 0;
    if ( topics2011[n][1] == 2 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1 ++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2 ++;
          if (collection_pos[base+j] == topics2011[n+1][2]) tf3 ++;
          if (collection_pos[base+j] == topics2011[n+1][3]) tf4 ++;
        }
        if (tf1 > 0) score1+=log10(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf2 > 0) score1+=log10(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf3 > 0) score2+=log10(1 + tf3/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf4 > 0) score2+=log10(1 + tf4/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
          }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
          }
        }

        base += doclengths[i];
      }
    } else
    if ( topics2011[n][1] == 3 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        int tf5 = 0;
        int tf6 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1 ++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2 ++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3 ++;
          if (collection_pos[base+j] == topics2011[n+1][2]) tf4 ++;
          if (collection_pos[base+j] == topics2011[n+1][3]) tf5 ++;
          if (collection_pos[base+j] == topics2011[n+1][4]) tf6 ++;
        }
        if (tf1 > 0) score1+=log10(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf2 > 0) score1+=log10(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf3 > 0) score1+=log10(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf4 > 0) score2+=log10(1 + tf4/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf5 > 0) score2+=log10(1 + tf5/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf6 > 0) score2+=log10(1 + tf6/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][4]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][4]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
        }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
        }
        }

        base += doclengths[i];
      }
    } else
    if ( topics2011[n][1] == 4 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        int tf5 = 0;
        int tf6 = 0;
        int tf7 = 0;
        int tf8 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1 ++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2 ++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3 ++;
          if (collection_pos[base+j] == topics2011[n][5]) tf4 ++;
          if (collection_pos[base+j] == topics2011[n+1][2]) tf5 ++;
          if (collection_pos[base+j] == topics2011[n+1][3]) tf6 ++;
          if (collection_pos[base+j] == topics2011[n+1][4]) tf7 ++;
          if (collection_pos[base+j] == topics2011[n+1][5]) tf8 ++;
        }
        if (tf1 > 0) score1+=log10(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf2 > 0) score1+=log10(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf3 > 0) score1+=log10(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf4 > 0) score1+=log10(1 + tf4/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf5 > 0) score2+=log10(1 + tf5/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf6 > 0) score2+=log10(1 + tf6/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf7 > 0) score2+=log10(1 + tf7/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf8 > 0) score2+=log10(1 + tf8/(MU * (cf[topics2011[n+1][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][4]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][5]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][4]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][5]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));


        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
        }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
        }
        }

        base += doclengths[i];
      }
    }else
    if ( topics2011[n][1] == 5 ) {
      for (i=0; i<NUM_DOCS; i++) {
        score1 = 0;
        score2 = 0;

        int tf1 = 0;
        int tf2 = 0;
        int tf3 = 0;
        int tf4 = 0;
        int tf5 = 0;
        int tf6 = 0;
        int tf7 = 0;
        int tf8 = 0;
        int tf9 = 0;
        int tf10 = 0;
        for (j=0; j<doclengths[i]; j++) {
          if (collection_pos[base+j] == topics2011[n][2]) tf1 ++;
          if (collection_pos[base+j] == topics2011[n][3]) tf2 ++;
          if (collection_pos[base+j] == topics2011[n][4]) tf3 ++;
          if (collection_pos[base+j] == topics2011[n][5]) tf4 ++;
          if (collection_pos[base+j] == topics2011[n][6]) tf5 ++;
          if (collection_pos[base+j] == topics2011[n+1][2]) tf6 ++;
          if (collection_pos[base+j] == topics2011[n+1][3]) tf7 ++;
          if (collection_pos[base+j] == topics2011[n+1][4]) tf8 ++;
          if (collection_pos[base+j] == topics2011[n+1][5]) tf9 ++;
          if (collection_pos[base+j] == topics2011[n+1][6]) tf10 ++;
        }
        if (tf1 > 0) score1+=log10(1 + tf1/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf2 > 0) score1+=log10(1 + tf2/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf3 > 0) score1+=log10(1 + tf3/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf4 > 0) score1+=log10(1 + tf4/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf5 > 0) score1+=log10(1 + tf5/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf6 > 0) score2+=log10(1 + tf6/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf7 > 0) score2+=log10(1 + tf7/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf8 > 0) score2+=log10(1 + tf8/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf9 > 0) score2+=log10(1 + tf9/(MU * (cf[topics2011[n+1][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        if (tf10 > 0) score2+=log10(1 + tf10/(MU * (cf[topics2011[n+1][6]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));


        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][2]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));
        
        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][3]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][4]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][5]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n][6]) tf ++;
        // }
        // if (tf > 0) score1+=log10(1 + tf/(MU * (cf[topics2011[n][6]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][2]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][2]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][3]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][3]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][4]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][4]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][5]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][5]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        // tf = 0;
        // for (j=0; j<doclengths[i]; j++) {
        //   if (collection_pos[base+j] == topics2011[n+1][6]) tf ++;
        // }
        // if (tf > 0) score2+=log10(1 + tf/(MU * (cf[topics2011[n+1][6]] + 1) / (TOTAL_TERMS + 1))) + log10(MU / (doclengths[i] + MU));

        if (score1 > 0) {
          int size = heap_size(&h1);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score1;
            heap_insert(&h1, scorez, docid);
          } else {
            heap_min(&h1, (void**)&min_key, (void**)&min_val);

            if (score1 > *min_key) {
              heap_delmin(&h1, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score1;
              heap_insert(&h1, scorez, docid);
            }
        }
        }

        if (score2 > 0) {
          int size = heap_size(&h2);

          if ( size < TOP_K ) {
            int *docid = malloc(sizeof(int)); *docid = i;
            float *scorez = malloc(sizeof(float)); *scorez = score2;
            heap_insert(&h2, scorez, docid);
          } else {
            heap_min(&h2, (void**)&min_key, (void**)&min_val);

            if (score2 > *min_key) {
              heap_delmin(&h2, (void**)&min_key, (void**)&min_val);

              int *docid = malloc(sizeof(int)); *docid = i;
              float *scorez = malloc(sizeof(float)); *scorez = score2;
              heap_insert(&h2, scorez, docid);
            }
        }
        }

        base += doclengths[i];
      }
    }

    int rank = TOP_K;
    while (heap_delmin(&h1, (void**)&min_key, (void**)&min_val)) {
      printf("%d Q0 %ld %d %f bfscan_pos_v3\n", topics2011[n][0], tweetids[*min_val], rank, *min_key);
      rank--;
    }
    heap_destroy(&h1);

    rank = TOP_K;
    while (heap_delmin(&h2, (void**)&min_key, (void**)&min_val)) {
      printf("%d Q0 %ld %d %f bfscan_pos_v3\n", topics2011[n+1][0], tweetids[*min_val], rank, *min_key);
      rank--;
    }
    heap_destroy(&h2);
  }

  end = clock();
  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Total time = %f ms\n", time_spent * 1000);
  printf("Time per query = %f ms\n", (time_spent * 1000)/42);
  printf("Throughput: %f qps\n", 42/time_spent);
}