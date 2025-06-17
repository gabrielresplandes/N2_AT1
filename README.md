# Projeto: Sistema de Processamento de Sensores Industriais

## Descrição
Este projeto simula uma planta industrial inteligente que coleta dados de sensores distribuídos na linha de produção. As leituras são registradas de forma desorganizada em um único arquivo bruto. Este sistema é composto por 3 programas desenvolvidos em linguagem C:

---

## Programa 1 – Organização dos Dados (`organizar_dados.c`)

### Objetivo
- Separar as leituras por sensor
- Ordenar por timestamp (formato Unix Epoch)
- Criar um arquivo `.txt` para cada sensor com os dados organizados

### Entrada
- Arquivo bruto com linhas no formato:
  ```
  <TIMESTAMP> <ID_SENSOR> <VALOR>
  ```

### Saída
- Arquivos como `sensor_temp.txt`, `sensor_motor.txt`, etc.

### Execução
```bash
./organizar_dados arquivo_teste.txt
```

---

## Programa 2 – Consulta por Instante (`consulta_sensor.c`)

### Objetivo
- Encontrar a leitura mais próxima de um `timestamp` fornecido para um determinado sensor
- Utiliza busca binária para alto desempenho

### Entrada
- Nome do sensor (sem extensão .txt)
- Timestamp desejado (em Unix Epoch)

### Execução
```bash
./consulta_sensor sensor_temp 1700000000
```

---

## Programa 3 – Geração de Arquivo de Teste (`gerar_arquivo_teste.c`)

### Objetivo
- Gerar 2000 leituras aleatórias para cada sensor fornecido
- Valores são compatíveis com os tipos indicados (int, float, bool, string)
- Timestamps aleatórios dentro de um intervalo definido

### Tipos suportados
- Inteiros (ex: `42`)
- Reais (ex: `34.56`)
- Booleanos (`true`, `false`)
- Strings (ex: `ABCDEFGH`)

### Execução
```bash
./gerar_arquivo_teste
```

O programa solicita interativamente:
- Timestamp inicial
- Timestamp final
- Lista de sensores com seus tipos

---

## Compilação (Linux/Windows com GCC)
```bash
gcc organizar_dados.c -o organizar_dados
gcc consulta_sensor.c -o consulta_sensor
gcc gerar_arquivo_teste.c -o gerar_arquivo_teste
```

---

## Funções Extras

### Conversão de data/hora para timestamp
```c
time_t converter_para_timestap(int dia, int mes, int ano, int hora, int min, int seg);
```

### Geração de timestamp aleatório entre duas datas
```c
time_t gerar_timestamp_aleatorio(struct tm * inicial, struct tm * final);
```

---

## Arquivo incluso para teste
- `arquivo_teste.txt`: já gerado com 2000 leituras reais, contendo sensores:
  - `sensor_temp` (float)
  - `sensor_hum` (int)
  - `sensor_motor` (bool)
  - `sensor_codigo` (string)

---

## Autor
Aluno responsável: Gabriel Morais Resplandes Sirqueira
Instituição: [Universidade Católica de Brasília]

