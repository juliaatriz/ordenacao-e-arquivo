#include <stdio.h>

#define MAX 100

int v[MAX];
int aux[MAX];
int n;

// Bubble Sort
void bubbleSort() {
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort
void insertionSort() {
    int i, j, chave;

    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }

        v[j + 1] = chave;
    }
}

// Selection Sort
void selectionSort() {
    int i, j, menor, temp;

    for (i = 0; i < n - 1; i++) {
        menor = i;

        for (j = i + 1; j < n; j++) {
            if (v[j] < v[menor]) {
                menor = j;
            }
        }

        temp = v[i];
        v[i] = v[menor];
        v[menor] = temp;
    }
}

// Merge Sort
void intercala(int inicio, int meio, int fim) {
    int i, j, k;

    i = inicio;
    j = meio + 1;
    k = inicio;

    while (i <= meio && j <= fim) {
        if (v[i] < v[j]) {
            aux[k] = v[i];
            i++;
        } else {
            aux[k] = v[j];
            j++;
        }

        k++;
    }

    while (i <= meio) {
        aux[k] = v[i];
        i++;
        k++;
    }

    while (j <= fim) {
        aux[k] = v[j];
        j++;
        k++;
    }

    for (i = inicio; i <= fim; i++) {
        v[i] = aux[i];
    }
}

void mergeSort(int inicio, int fim) {
    int meio;

    if (inicio < fim) {
        meio = (inicio + fim) / 2;

        mergeSort(inicio, meio);
        mergeSort(meio + 1, fim);

        intercala(inicio, meio, fim);
    }
}

// Quick Sort
void quickSort(int inicio, int fim) {
    int i, j, pivo, temp;

    i = inicio;
    j = fim;
    pivo = v[(inicio + fim) / 2];

    while (i <= j) {
        while (v[i] < pivo) {
            i++;
        }

        while (v[j] > pivo) {
            j--;
        }

        if (i <= j) {
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;

            i++;
            j--;
        }
    }

    if (inicio < j) {
        quickSort(inicio, j);
    }

    if (i < fim) {
        quickSort(i, fim);
    }
}

// Grava os números em um arquivo
void gravarArquivo(char nome[]) {
    FILE *arquivo;
    int i;

    arquivo = fopen(nome, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(arquivo, "%d\n", v[i]);
    }

    fclose(arquivo);
}

// Lê os números do arquivo
int lerArquivo() {
    FILE *arquivo;

    arquivo = fopen("dados.txt", "r");

    if (arquivo == NULL) {
        printf("Arquivo dados.txt nao encontrado!\n");
        return 0;
    }

    n = 0;

    while (n < MAX && fscanf(arquivo, "%d", &v[n]) == 1) {
        n++;
    }

    fclose(arquivo);

    return n;
}

// Mostra os números
void mostrarNumeros() {
    int i;

    for (i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }

    printf("\n");
}

// Escolhe o algoritmo e ordena os números
void ordenar() {
    int opcao;

    if (!lerArquivo()) {
        return;
    }

    printf("\nNumeros do arquivo:\n");
    mostrarNumeros();

    printf("\nEscolha o tipo de ordenacao:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Quick Sort\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            bubbleSort();
            break;

        case 2:
            insertionSort();
            break;

        case 3:
            selectionSort();
            break;

        case 4:
            mergeSort(0, n - 1);
            break;

        case 5:
            quickSort(0, n - 1);
            break;

        default:
            printf("Opcao invalida!\n");
            return;
    }

    printf("\nNumeros ordenados:\n");
    mostrarNumeros();

    gravarArquivo("ordenado.txt");

    printf("Resultado salvo em ordenado.txt!\n");
}

// Cria o arquivo com números desordenados
void criarArquivo() {
    int i;

    printf("Quantos numeros deseja guardar? (1 a %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Quantidade invalida!\n");
        n = 0;
        return;
    }

    printf("Digite os numeros fora de ordem:\n");

    for (i = 0; i < n; i++) {
        printf("Numero %d: ", i + 1);
        scanf("%d", &v[i]);
    }

    gravarArquivo("dados.txt");

    printf("Numeros gravados em dados.txt!\n");
}

// Altera um número e ordena novamente
void alterarNumero() {
    int posicao, novoValor;

    if (!lerArquivo()) {
        return;
    }

    printf("\nNumeros atuais:\n");
    mostrarNumeros();

    printf("Qual posicao deseja alterar? (1 a %d): ", n);
    scanf("%d", &posicao);

    if (posicao < 1 || posicao > n) {
        printf("Posicao invalida!\n");
        return;
    }

    printf("Digite o novo valor: ");
    scanf("%d", &novoValor);

    v[posicao - 1] = novoValor;

    gravarArquivo("dados.txt");

    printf("Valor alterado em dados.txt!\n");

    printf("\nAgora vamos ordenar novamente.\n");
    ordenar();
}

int main() {
    int opcao;

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Criar arquivo com numeros\n");
        printf("2 - Ler e ordenar os numeros\n");
        printf("3 - Alterar um numero e ordenar novamente\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarArquivo();
                break;

            case 2:
                ordenar();
                break;

            case 3:
                alterarNumero();
                break;

            case 0:
                printf("Programa encerrado!\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}