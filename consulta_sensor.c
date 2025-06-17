
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define MAX_ID 32
#define MAX_VALOR 64
#define MAX_LEITURAS 10000

typedef struct {
    long timestamp;
    char id_sensor[MAX_ID];
    char valor[MAX_VALOR];
} Leitura;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <sensor> <timestamp>\n", argv[0]);
        return 1;
    }

    char nome_arquivo[50];
    sprintf(nome_arquivo, "%s.txt", argv[1]);
    long alvo = atol(argv[2]);

    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Erro ao abrir arquivo do sensor");
        return 1;
    }

    Leitura leituras[MAX_LEITURAS];
    int total = 0;

    while (fscanf(arquivo, "%ld %s %s", &leituras[total].timestamp, leituras[total].id_sensor, leituras[total].valor) == 3) {
        total++;
    }
    fclose(arquivo);

    int esquerda = 0, direita = total - 1, melhor = -1;
    long menor_dif = LONG_MAX;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        long diff = labs(leituras[meio].timestamp - alvo);

        if (diff < menor_dif) {
            menor_dif = diff;
            melhor = meio;
        }

        if (leituras[meio].timestamp > alvo)
            esquerda = meio + 1;
        else
            direita = meio - 1;
    }

    if (melhor != -1) {
        printf("Leitura mais próxima:\n%ld %s %s\n",
               leituras[melhor].timestamp,
               leituras[melhor].id_sensor,
               leituras[melhor].valor);
    }

    return 0;
}
