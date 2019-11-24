#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    int *kameny;
    int N;
    int *result;
} vstup;

void* comp(void *i) {
        vstup *in = (vstup *)i;
        int *graph;
        int max = 0;
        graph = malloc(in->N*sizeof(int));
        if (graph == NULL) {
            fputs("compNelze alokovat", stderr);
            exit(1);
        }
        memset(graph, -1, in->N*sizeof(int));
        int *pA, *pF, iA = 1, iF = 0;
        pA = malloc(in->N*sizeof(int));
        pF = malloc(in->N*sizeof(int));
        if (pA == NULL || pF == NULL) {
            fputs("Nelze alokovat", stderr);
            exit(1);
        }
        *pA = 0;
        char test = 0;
        for (int i = 0;; i++) {
            for (int j = 0; j < iA; j++) {
                int k = pA[j] + in->kameny[pA[j]] - max < 0?max:max <= pA[j]?1:pA[j] + in->kameny[pA[j]]-max;
                for (; k <= in->kameny[pA[j]]; k++) {
                    if (pA[j]+k == in->N) {
                        fprintf(stderr, "OK\n");
                        test = 1;
                        i++;
                        break;
                    }
                    if (graph[pA[j]+k] == -1 || graph[pA[j]+k] > i+1) {
                        graph[pA[j]+k] = i+1;
                        pF[iF++] = pA[j]+k;
                    }
                }
                if (test) {
                    break;
                }
                max = pA[j]+in->kameny[pA[j]]>max?pA[j]+in->kameny[pA[j]]:max;
            }
            if (test) {
               *(in->result) = i;
                break;
            }
            int *swp = pA;
            pA = pF;
            pF = swp;
            iA = iF;
            iF = 0;
        }
        free(pA);
        free(pF);
        free(graph);
        free(in->kameny);
        return NULL;
}
int main() {
    int T;
    scanf("%d", &T);
    int **data;
    int *results;
    pthread_t *vlakna;
    vstup *vstupy;
    data = malloc(T*sizeof(int*));
    results = malloc(T*sizeof(int));
    vlakna = malloc(T*sizeof(pthread_t));
    vstupy = malloc(T*sizeof(vstup));
    if (data == NULL || results == NULL || vlakna == NULL || vstupy == NULL) {
        fputs("hodneNelze alokovat", stderr);
        exit(1);
    }
    for (int i = 0; i < T; i++) {
        int N;
        int *kameny;
        vstup in;
        scanf("%d", &N);
        kameny = malloc(N*sizeof(int));
        if (kameny == NULL) {
            fputs("kamenyNelze alokovat", stderr);
            exit(1);
        }
        data[i] = kameny;
        for (int j = 0; j < N; j++) {
            scanf("%d", kameny+j);
        }
        in.kameny = kameny;
        in.N = N;
        in.result = results+i;
        vstupy[i] = in;
        pthread_create(vlakna+i, NULL, comp, (void *) &vstupy[i]);
    }
    for (int i = 0; i < T; i++) {
        pthread_join(vlakna[i], NULL);
        printf("%d\n", results[i]);
    }
    free(data);
    free(results);
    free(vlakna);
    free(vstupy);
    return 0;
}
