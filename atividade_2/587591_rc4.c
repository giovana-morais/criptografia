#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 256 

void swap(unsigned int *i, unsigned int *j);

void main() {
    unsigned int M[N];          // mensagem em hexa
    unsigned int *C;           // texto cifrado
    unsigned int S[N], T[N];   // tabelas de inicialização e permutação
    int i, k, t, j = 0;
    int tamanho = 0;
    FILE *arquivo;
    char *K = "mruavedp";   // chave hard-coded 
    
    arquivo = fopen("rc4.txt", "r");

    while (!feof(arquivo)) {
        fscanf(arquivo, "%2x", &M[tamanho]);
        tamanho++;
    }
    fclose(arquivo);
    tamanho--;

    // inicialização da tabela S
    for (i = 0; i < N; i++) {
        S[i] = i;
        T[i] = K[i % strlen(K)];
    }

    // permuta o vetor de estado interno
    for (i = 0; i < N; i++) {
        j = (j + S[i] + T[i]) % N;
        swap(&S[i], &S[j]);
    }

    i = 0; j = 0;
    C = malloc(sizeof(unsigned int) * tamanho);
    
    for (k = 0; k < tamanho; k++) {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        t = (S[i] + S[j]) % N;
        C[k] = M[k] ^ S[t];
    }

    printf("Mensagem cifrada:\n");
    for (i = 0; i < tamanho; i++) {
        printf("%2c", C[i]);
    }
    printf("\n");
}

void swap(unsigned int *i, unsigned int *j) {
    int aux;

    aux = *i;
    *i = *j;
    *j = aux;
}
