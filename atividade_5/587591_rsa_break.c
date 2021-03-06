/* Giovana Vieira de Morais	587591 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long eea(unsigned long long r0, unsigned long long r1, signed long long *inv);
unsigned long long s_m(unsigned long long x, unsigned long long H, unsigned long long n);
unsigned long long sieve(unsigned long long N);

/* A única linha da entrada contém três inteiros N, E, e C, onde 15 <= N <= 10^9 
, 1 <= E < N e 1 <= C < N, de forma que N e E constituem a chave pública do algoritmo 
RSA descrita acima e C é uma mensagem criptografada com essa chave pública. */
void main() 
{
	unsigned long long r0, r1, gcd, inv;
	unsigned long long N, E, C, M;
	unsigned long long p, q, phi_n, d;
	long long P;

	scanf("%llu %llu %llu", &N, &E, &C);
	if (N < 15 || E < 1 || C < 1 || C > N) {
		printf("Erro: entrada inválida\n");
		return;
	}
	
	// primeiro, procuramos pelos primos p e q
	p = sieve(N);
	p = 13;
	q = N/p;

	phi_n = (p-1)*(q-1);

	// chave secreta
	eea(phi_n, E, &inv);
	// decifra a mensagem
	M = s_m(C, inv, N);
	printf("%llu\n", M);
}

unsigned long long eea(unsigned long long r0, unsigned long long r1, signed long long *inv)
{
	signed long long int *t;
	unsigned long long int *q, *r;
	unsigned long long int gcd;
    int i = 1;
	int tam = 20;

	t = (signed long long *) malloc(tam * sizeof(unsigned long long));
	q = (unsigned long long *) malloc(tam * sizeof(unsigned long long));
	r = (unsigned long long *) malloc(tam * sizeof(unsigned long long));

	t[0] = 0;
	t[1] = 1;
	r[0] = r0;
	r[1] = r1;

	while (r[i] != 0) {
		// como o tamanho dos vetores é pequeno, talvez precise realocar
		if (i % tam == 19) {
			tam *= 2;
			t = (signed long long *) realloc(t, tam * sizeof(signed long long));
			q = (unsigned long long *) realloc(q, tam * sizeof(unsigned long long));
			r = (unsigned long long *) realloc(r, tam * sizeof(unsigned long long));
		}
		
		i++;
		r[i] 	= r[i-2] % r[i-1];
		q[i-1] 	= (r[i-2]-r[i])/r[i-1];
		t[i]	= t[i-2]-q[i-1]*t[i-1];
	}

	gcd = r[i-1];
	*inv = t[i-1];

	// se o inverso for negativo, soma n
	while (*inv < 0) 
		*inv += r0;

	free(t);
	free(q);
	free(r);
	return gcd;
}

unsigned long long s_m(unsigned long long x, unsigned long long H, unsigned long long n)
{
	unsigned long long r;
	unsigned long long tmp;

	r = 1;
	while (H > 0){
		// dessa forma, pega bit a bit do expoente H
		if (H % 2 == 1) 
			r = r*x % n;	
		H >>= 1;
		x = x*x % n;
	}
	return r;
}

unsigned long long sieve(unsigned long long N) 
{
	unsigned long long primes[N];
	unsigned long long thresh = sqrt(N);
	unsigned long long P;

	// inicialização do vetor pra aplicação do crivo de Eratóstenes
	for (int i = 2; i < N; i++) 
		primes[i] = i;

	for (int i = 2; i <= thresh; i++) {
		if (primes[i] == i && N % i == 0) {
			P = primes[i];
		}
		// remove os múltiplos de i da lista de primos
		for (int j = i+i; j <= N; j += i)
			primes[j] = 0;
	}

	return P;
}	
