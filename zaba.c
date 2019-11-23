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
        fprintf(stderr, "RUN!\n");
        vstup *in = (vstup *)i;
        int *graph;
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
                for (int k = 1; k <= in->kameny[pA[j]]; k++) {
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
    vstupy = malloc(T*sizeof(vstupy));
    if (data == NULL || results == NULL || vlakna == NULL || vstupy == NULL) {
        fputs("hodneNelze alokovat", stderr);
        exit(1);
    }
    for (int i = 0; i < T; i++) {
        int N;
        int *kameny;
        vstup in;
        pthread_t f;
        scanf("%d", &N);
        kameny = malloc(N*sizeof(int));
        data[i] = kameny;
        if (kameny == NULL) {
            fputs("kamenyNelze alokovat", stderr);
            exit(1);
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", kameny+i);
        }
        in.kameny = kameny;
        in.N = N;
        in.result = results+i;
        vstupy[i] = in;
        pthread_create(&f, NULL, comp, (void *) vstupy+i);
        vlakna[i] = f;
        system("sleep 0.4");
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
