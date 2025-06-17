
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ID 32
#define MAX_VALOR 64
#define MAX_SENSORES 10000

typedef struct {
    long timestamp;
    char id_sensor[MAX_ID];
    char valor[MAX_VALOR];
} Leitura;

int comparar_por_timestamp_decrescente(const void *a, const void *b) {
    Leitura *la = (Leitura *)a;
    Leitura *lb = (Leitura *)b;
    return (lb->timestamp - la->timestamp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_entrada>\n", argv[0]);
        return 1;
    }

    FILE *entrada = fopen(argv[1], "r");
    if (!entrada) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    Leitura leituras[MAX_SENSORES];
    int total = 0, linha = 0;

    while (!feof(entrada)) {
        linha++;
        char buffer[256];
        if (!fgets(buffer, sizeof(buffer), entrada)) break;

        char id[MAX_ID], val[MAX_VALOR];
        long ts;
        int campos = sscanf(buffer, "%ld %s %s", &ts, id, val);

        if (campos != 3 || ts <= 0 || strlen(id) == 0 || strlen(val) == 0) {
            printf("Linha %d inválida: %s", linha, buffer);
            continue;
        }

        leituras[total].timestamp = ts;
        strcpy(leituras[total].id_sensor, id);
        strcpy(leituras[total].valor, val);
        total++;
        if (total >= MAX_SENSORES) break;
    }
    fclose(entrada);

    char sensores[MAX_SENSORES][MAX_ID];
    int total_sensores = 0;

    for (int i = 0; i < total; i++) {
        int existe = 0;
        for (int j = 0; j < total_sensores; j++) {
            if (strcmp(leituras[i].id_sensor, sensores[j]) == 0) {
                existe = 1;
                break;
            }
        }
        if (!existe) {
            strcpy(sensores[total_sensores], leituras[i].id_sensor);
            total_sensores++;
        }
    }

    for (int i = 0; i < total_sensores; i++) {
        Leitura lista_sensor[MAX_SENSORES];
        int count = 0;

        for (int j = 0; j < total; j++) {
            if (strcmp(leituras[j].id_sensor, sensores[i]) == 0) {
                lista_sensor[count++] = leituras[j];
            }
        }

        qsort(lista_sensor, count, sizeof(Leitura), comparar_por_timestamp_decrescente);

        char nome_arquivo[50];
        sprintf(nome_arquivo, "%s.txt", sensores[i]);

        FILE *saida = fopen(nome_arquivo, "w");
        if (!saida) {
            printf("Erro ao criar o arquivo para sensor %s\n", sensores[i]);
            continue;
        }

        for (int j = 0; j < count; j++) {
            fprintf(saida, "%ld %s %s\n", lista_sensor[j].timestamp,
                    lista_sensor[j].id_sensor,
                    lista_sensor[j].valor);
        }

        fclose(saida);
        printf("Arquivo '%s' criado com %d leituras.\n", nome_arquivo, count);
    }

    return 0;
}
