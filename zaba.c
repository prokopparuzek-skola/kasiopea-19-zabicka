#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int T;
    scanf("%d", &T);
    for (; T > 0; T--) {
        int N;
        int *kameny, *graph;
        scanf("%d", &N);
        kameny = malloc(N*sizeof(int));
        if (kameny == NULL) {
            puts("Nelze alokovat");
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", kameny+i);
        }
        graph = malloc(N*sizeof(int));
        if (graph == NULL) {
            puts("Nelze alokovat");
        }
        memset(graph, -1, N*sizeof(int));
        int *pA, *pF, iA = 1, iF = 0;
        pA = malloc(N*sizeof(int));
        pF = malloc(N*sizeof(int));
        if (pA == NULL || pF == NULL) {
            puts("Nelze alokovat");
        }
        *pA = 0;
        char test = 0;
        for (int i = 0;; i++) {
            for (int j = 0; j < iA; j++) {
                for (int k = 1; k <= kameny[pA[j]]; k++) {
                    if (pA[j]+k == N) {
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
                printf("%d\n", i);
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
        free(kameny);
    }
    return 0;
}
