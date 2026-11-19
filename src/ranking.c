#include <stdio.h>
#include "ranking.h"

/* le o top_scores.txt. Devolve quantos registros leu */
int lerRanking(struct Score lista[MAX_RANK]) {
    int total = 0;
    FILE *arq = fopen("top_scores.txt", "r");

    if (arq == NULL) return 0;
    while (total < MAX_RANK && fscanf(arq, "%d %d", &lista[total].pontos, &lista[total].tempo) == 2)
        total++;
    fclose(arq);
    return total;
}

void salvarScore(int pontos, int tempo) {
    struct Score lista[MAX_RANK + 1];
    int total = lerRanking(lista);
    int i, k;
    FILE *arq;

    lista[total].pontos = pontos;
    lista[total].tempo = tempo;
    total++;

    /* bubble sort, maior pontuacao primeiro */
    for (i = 0; i < total - 1; i++) {
        for (k = 0; k < total - 1 - i; k++) {
            if (lista[k].pontos < lista[k + 1].pontos) {
                struct Score temp = lista[k];
                lista[k] = lista[k + 1];
                lista[k + 1] = temp;
            }
        }
    }

    if (total > MAX_RANK) total = MAX_RANK;

    arq = fopen("top_scores.txt", "w");
    if (arq == NULL) return;
    for (i = 0; i < total; i++)
        fprintf(arq, "%d %d\n", lista[i].pontos, lista[i].tempo);
    fclose(arq);
}
