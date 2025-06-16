#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SENSORES 10
#define MAX_ID 32

typedef enum {INT, FLOAT, BOOL, STR} TipoDado;

long gerar_timestamp_aleatorio(long inicio, long fim) {
    return inicio + rand() % (fim - inicio + 1);
}

void gerar_valor(char *buffer, TipoDado tipo) {
    switch (tipo) {
        case INT: sprintf(buffer, "%d", rand() % 1000); break;
        case FLOAT: sprintf(buffer, "%.2f", (rand() % 10000) / 100.0); break;
        case BOOL: sprintf(buffer, "%s", rand() % 2 ? "true" : "false"); break;
        case STR:
            for (int i = 0; i < 8; i++)
                buffer[i] = 'A' + rand() % 26;
            buffer[8] = '\0';
            break;
    }
}

int main() {
    srand(time(NULL));

    long inicio, fim;
    printf("Digite timestamp de início: ");
    scanf("%ld", &inicio);
    printf("Digite timestamp de fim: ");
    scanf("%ld", &fim);

    int num_sensores;
    printf("Número de sensores: ");
    scanf("%d", &num_sensores);

    char ids[MAX_SENSORES][MAX_ID];
    TipoDado tipos[MAX_SENSORES];

    for (int i = 0; i < num_sensores; i++) {
        printf("ID do sensor %d: ", i+1);
        scanf("%s", ids[i]);
        int t;
        printf("Tipo (0=int, 1=float, 2=bool, 3=string): ");
        scanf("%d", &t);
        tipos[i] = t;
    }

    FILE *saida = fopen("arquivo_teste.txt", "w");
    if (!saida) {
        perror("Erro ao criar arquivo");
        return 1;
    }

    for (int i = 0; i < num_sensores; i++) {
        for (int j = 0; j < 2000; j++) {
            long ts = gerar_timestamp_aleatorio(inicio, fim);
            char valor[64];
            gerar_valor(valor, tipos[i]);
            fprintf(saida, "%ld %s %s\n", ts, ids[i], valor);
        }
    }

    fclose(saida);
    printf("Arquivo 'arquivo_teste.txt' gerado.\n");
    return 0;
}
