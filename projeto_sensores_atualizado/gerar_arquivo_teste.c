
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SENSORES 10
#define MAX_ID 32

typedef enum {INT, FLOAT, BOOL, STR, INVALIDO} TipoDado;

TipoDado interpretar_tipo(char *tipo_str) {
    if (strcmp(tipo_str, "CONJ_Z") == 0) return INT;
    if (strcmp(tipo_str, "CONJ_Q") == 0) return FLOAT;
    if (strcmp(tipo_str, "BINARIO") == 0) return BOOL;
    if (strcmp(tipo_str, "TEXTO") == 0) return STR;
    return INVALIDO;
}

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
        default: strcpy(buffer, "INVALID"); break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s <timestamp_inicio> <timestamp_fim> <sensor:tipo> ...\n", argv[0]);
        return 1;
    }

    srand(time(NULL));
    long inicio = atol(argv[1]);
    long fim = atol(argv[2]);

    if (inicio <= 0 || fim <= 0 || fim <= inicio) {
        printf("Timestamps inválidos.\n");
        return 1;
    }

    FILE *saida = fopen("arquivo_teste.txt", "w");
    if (!saida) {
        perror("Erro ao criar arquivo");
        return 1;
    }

    for (int i = 3; i < argc; i++) {
        char *token = strtok(argv[i], ":");
        char *tipo_str = strtok(NULL, ":");

        if (!token || !tipo_str) {
            printf("Formato inválido no argumento: %s\n", argv[i]);
            continue;
        }

        TipoDado tipo = interpretar_tipo(tipo_str);
        if (tipo == INVALIDO) {
            printf("Tipo inválido para sensor '%s': %s\n", token, tipo_str);
            continue;
        }

        for (int j = 0; j < 2000; j++) {
            long ts = gerar_timestamp_aleatorio(inicio, fim);
            char valor[64];
            gerar_valor(valor, tipo);
            fprintf(saida, "%ld %s %s\n", ts, token, valor);
        }
    }

    fclose(saida);
    printf("Arquivo 'arquivo_teste.txt' gerado.\n");
    return 0;
}
