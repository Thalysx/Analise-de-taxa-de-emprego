#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_SIZE 150
#define NUM_ESTADOS 27

struct Estado {
    char regiao[20];
    char sigla[10];
    int populacao;
};

struct Estado estados[NUM_ESTADOS];

struct Regiao {
    char nome[50];
};

struct Regiao regioes[] = {
    {"Centro-Oeste"},
    {"Sul"},
    {"Sudeste"},
    {"Norte"},
    {"Nordeste"}
};

void pesquisarEstadoPorSigla(char sigla[]) {
    int i;
    for (i = 0; i < NUM_ESTADOS; i++) {
        if (strcmp(estados[i].sigla, sigla) == 0) {
            printf("\n");
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("Estado: %s\n", estados[i].sigla);
            printf("Regiao: %s\n", estados[i].regiao);
            printf("Populacao: %d\n", estados[i].populacao);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return;
        }
    }
    printf("Estado nao encontrado.\n");
}

void mostrarEstadosRegioesPopulacao() {
    int i;
    for (i = 0; i < NUM_ESTADOS; i++) {
        printf("\n");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf("Estado: %s\n", estados[i].sigla);
        printf("Regiao: %s\n", estados[i].regiao);
        printf("Populacao: %d\n", estados[i].populacao);
        printf("\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    }
}

int calcularPopulacaoRegiao(char regiao[]) {
    int populacaoTotal = 0;
    int i;
    for (i = 0; i < NUM_ESTADOS; i++) {
        if (strcmp(estados[i].regiao, regiao) == 0) {
            populacaoTotal += estados[i].populacao;
        }
    }
    return populacaoTotal;
}

int exibirMenu() {
    int opcao;
    printf("Selecione uma opcao:\n");
    printf("\n");
    printf("1. Encontrar o menor valor em um vetor\n");
    printf("2. Pesquisar estado por sigla\n");
    printf("3. Pesquisar estado por regiao\n");
    printf("4. Mostrar todos os estados, regioes e populacao\n");
    printf("5. Calcular a populacao total de uma regiao\n");
    printf("6. Sair\n");
    printf("\n");
    printf("Opcao: ");
    printf("\n");
    scanf("%d", &opcao);
    getchar(); // Limpar o buffer de entrada

    return opcao;
}

int encontrarMenorValor(int vetor[], int tamanho) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    int menor = vetor[0];
    for (int i = 1; i < tamanho; i++) {
        if (vetor[i] < menor) {
            menor = vetor[i];
             SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }
    return menor;
}

int main() {
    FILE* arquivo;
    char nome_arquivo[256];
    char linha[100];

    int arquivo_aberto = 0;
    int count = 0;
    int opcao;

    const char nomeArquivo[] = "daniel.csv";
    int vetor[] = {5, 3, 8, 1, 9};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);

    while (!arquivo_aberto) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        printf("                              --------------------------------------------------------\n");
        printf("                              | Digite o caminho completo do arquivo .csv            |\n");
        printf("                              | Exemplo: C:\\Users\\Administrator\\Downloads\\dados.csv  |\n");
        printf("                              --------------------------------------------------------\n");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("\n\n                              Digite aqui o caminho: ");

        fgets(nome_arquivo, sizeof(nome_arquivo), stdin);

        nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';

        arquivo = fopen(nome_arquivo, "r");

        if (arquivo == NULL) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("\n\n\n                              Erro ao abrir o arquivo! Insira uma nova localizacao.\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            printf("\n\n\n");
        } else {
            arquivo_aberto = 1;

            while (fgets(linha, sizeof(linha), arquivo) != NULL && count < MAX_SIZE) {
                char* token;
                token = strtok(linha, ",");
                strncpy(estados[count].regiao, token, sizeof(estados[count].regiao));

                token = strtok(NULL, ",");
                strncpy(estados[count].sigla, token, sizeof(estados[count].sigla));

                token = strtok(NULL, ",");
                estados[count].populacao = atoi(token);

                count++;
            }

            fclose(arquivo);
        }
    }

    opcao = exibirMenu();
    while (opcao != 6) {
        switch (opcao) {
            case 1:
                printf("Menor valor no vetor: %d\n", encontrarMenorValor(vetor, tamanho));
                break;
            case 2: {
                char sigla[10];
                printf("Digite a sigla do estado: ");
                fgets(sigla, sizeof(sigla), stdin);
                sigla[strcspn(sigla, "\n")] = '\0'; // Remove a nova linha do final da string
                pesquisarEstadoPorSigla(sigla);
                break;
            }
            case 3: {
                char regiao[20];
                printf("Digite a regiao: ");
                fgets(regiao, sizeof(regiao), stdin);
                regiao[strcspn(regiao, "\n")] = '\0'; // Remove a nova linha do final da string
                printf("\n");
                printf("Estados na regiao %s:\n", regiao);
                for (int i = 0; i < NUM_ESTADOS; i++) {
                    if (strcmp(estados[i].regiao, regiao) == 0) {
                        printf("\n");
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                        printf("Estado: %s\n", estados[i].sigla);
                        printf("Populacao: %d\n", estados[i].populacao);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                        printf("\n");
                    }
                }
                break;
            }
            case 4:
                mostrarEstadosRegioesPopulacao();
                break;
            case 5: {
                char regiao[20];
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("Digite a regiao: ");
                fgets(regiao, sizeof(regiao), stdin);
                regiao[strcspn(regiao, "\n")] = '\0'; // Remove a nova linha do final da string
                int populacaoTotal = calcularPopulacaoRegiao(regiao);
                printf("Populacao total da regiao %s: %d\n", regiao, populacaoTotal);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
            }
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        printf("\n");
        opcao = exibirMenu();
    }

    printf("Saindo...\n");

    return 0;
}
