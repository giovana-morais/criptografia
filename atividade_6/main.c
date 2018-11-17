/* Giovana Vieira de Morais	587591 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


void encript(mpz_t *y, mpz_t x, mpz_t e, mpz_t n);
void decript(mpz_t *x, mpz_t y, mpz_t d, mpz_t n);

void main() 
{
	// entrada é composta de:
	// 	base da entrada (decimal ou hexa)
	// 	módulo
	// 	expoente público ou expoente privado
	// 	texto claro ou texto cifrado

	mpz_t base, n, e; 
	mpz_t plain_txt, cipher_txt;
	int opt;
	unsigned long long tmp_ui;
	char tmp_str[2048];

	do {
		printf("Digite uma 1 para cifrar um texto, 2 para decifrar e 0 para sair\n");
		scanf("%d", &opt);

		if (opt == 1)
			printf("CIFRAGEM\n");
		else if (opt == 2)
			printf("DECIFRAGEM\n");
		else {
			printf("Encerrando execução\n");
			break;
		}

		scanf("%llu", &tmp_ui);
		mpz_init_set_ui(base, tmp_ui);

		scanf("%s", &tmp_str);
		mpz_init_set_str(n, tmp_str, 10);
		//memset(tmp_str, 0, sizeof(tmp_str));

		if (opt == 1) {
			scanf("%s", &tmp_str);
			mpz_init_set_str(e, tmp_str, 10);
			//memset(tmp_str, 0, sizeof(tmp_str));

			scanf("%s", &tmp_str);
			mpz_init_set_str(plain_txt, tmp_str, 10);
		
			mpz_init(cipher_txt);
			encript(&cipher_txt, plain_txt, e, n);

			printf("Base: ");
			mpz_out_str(stdout,10,base);
			printf("\n");
			printf("Chave pública: (");
			mpz_out_str(stdout,10,n);
			printf(", ");
			mpz_out_str(stdout,10,e);
			printf(")\n");
			printf("Texto claro: ");
			mpz_out_str(stdout,10,plain_txt);
			printf("\n");
			printf("Texto cifrado: ");
			mpz_out_str(stdout,10,cipher_txt);
			printf("\n");
		} else {
			scanf("%s", &tmp_str);
			mpz_init_set_str(e, tmp_str, 10);
			//memset(tmp_str, 0, sizeof(tmp_str));

			scanf("%s", &tmp_str);
			mpz_init_set_str(cipher_txt, tmp_str, 10);
		
			mpz_init(plain_txt);
			decript(&plain_txt, cipher_txt, e, n);

			printf("Base: ");
			mpz_out_str(stdout,10,base);
			printf("\n");
			printf("Chave privada: ");
			mpz_out_str(stdout,10,e);
			printf("\n");
			printf("Texto claro: ");
			mpz_out_str(stdout,10,plain_txt);
			printf("\n");
			printf("Texto cifrado: ");
			mpz_out_str(stdout,10,cipher_txt);
			printf("\n");
		}  


		mpz_clear(base);
		mpz_clear(n);
		mpz_clear(e);
		mpz_clear(plain_txt);
		mpz_clear(cipher_txt);
	} while(opt != 0);
}

void encript(mpz_t *y, mpz_t x, mpz_t e, mpz_t n)
{
	mpz_powm(*y, x, e, n);
}

void decript(mpz_t *x, mpz_t y, mpz_t d, mpz_t n)
{
	mpz_powm(*x, y, d, n);
}
