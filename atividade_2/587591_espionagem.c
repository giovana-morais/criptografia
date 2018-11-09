#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MASCARA_AGENCIA  4278190080   // 11111111000000000000000000000000
#define MASCARA_VALOR 65535   // 00000000000000001111111111111111

void le_contas(int num_contas, long int *prox_contas);
void printa_contas(int num_contas, long int *prox_contas, int flag_mascarada);

void aplica_chave(int num_contas, long int *prox_contas, unsigned int chave);

void main(){
    long int conta_decifrada, conta_cifrada;
    int num_contas;
    long int chave, temp;
    long int *prox_contas;

    // INICIALIZAÇÃO DO PROGRAMA E VARIÁVEIS //
    // printf("Digite a conta decifrada:\t");
    scanf("%ld", &conta_decifrada);
    // printf("Digite a mesma conta cifrada:\t");
    scanf("%ld", &conta_cifrada);
    // printf("Digite a quantidade de contas que ainda serão digitadas:\t");
    scanf("%d", &num_contas);
    prox_contas = malloc(sizeof(long int) * num_contas);

    le_contas(num_contas, prox_contas);
   
    // APLICAÇÃO DA LÓGICA //
    // K = conta_decifrada XOR conta_cifrada
    //chave = conta_decifrada ^ conta_cifrada;
    aplica_chave(num_contas, prox_contas, conta_decifrada^conta_cifrada);

    //printf("Conta base decifrada mascarada \t%ld\n", conta_decifrada&MASCARA_AGENCIA);

    unsigned int sub;
    for (int i = 0; i < num_contas; i++){
        sub = ((conta_decifrada & MASCARA_AGENCIA) ^
                (prox_contas[i]&MASCARA_AGENCIA)); 

        if ((conta_decifrada&MASCARA_AGENCIA ^ prox_contas[i]&MASCARA_AGENCIA) == 0){
            // printf("[%d] %u\n", i, prox_contas[i]&MASCARA_AGENCIA);
            printf("%ld\n", prox_contas[i]&MASCARA_VALOR);
        }
    }
}

void printa_contas(int num_contas, long int *prox_contas, int flag_mascarada){
    if (flag_mascarada){
        for (int i = 0; i < num_contas; i++)
            printf("Conta %d decifrada mascarada:\t%ld\n", i, prox_contas[i]&MASCARA_AGENCIA);
    } else {
        for (int i = 0; i < num_contas; i++)
            printf("Conta %d decifrada:\t%ld\n", i, prox_contas[i]);
    }
}

void le_contas(int num_contas, long int *prox_contas){
    for (int i = 0; i < num_contas; i++){
        scanf("%ld", &prox_contas[i]);
    }
}

void aplica_chave(int num_contas, long int *prox_contas, unsigned int chave){
    for (int i = 0; i < num_contas; i++)
        // salva no vetor as contas já decifradas
        prox_contas[i] = (prox_contas[i] ^ chave);
}
