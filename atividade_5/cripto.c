/* Giovana Vieira de Morais	597591 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long eea(unsigned long long r0, unsigned long long r1, unsigned long long *inv);
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

	scanf("%llu %llu %llu", &N, &C, &E);
	if (N < 15 || E < 1 || C < 1 || C > N) {
		printf("Erro: entrada inválida\n");
		return;
	}
	
	// primeiro, procuramos pelos primos p e q
	p = sieve(N);
	q = E/p;

	phi_n = (p-1)*(q-1);

	// chave secreta
	d = eea(phi_n, E, &inv);

	// decifra a mensagem
	M = s_m(C, d, N);
	printf("%llu\n", M);
}

// TODO: testar os casos de número negativo pq talvez possa dar pau por ser
// unsigned long long
unsigned long long eea(unsigned long long r0, unsigned long long r1, unsigned long long *inv)
{
	unsigned long long int *s, *t, *q, *r;
	unsigned long long int gcd, ret_q, ret_s;
        int i = 1;
	int tam = 20;

	s = (unsigned long long *) malloc(tam * sizeof(unsigned long long));
	t = (unsigned long long *) malloc(tam * sizeof(unsigned long long));
	q = (unsigned long long *) malloc(tam * sizeof(unsigned long long));
	r = (unsigned long long *) malloc(tam * sizeof(unsigned long long));

	s[0] = 1;
	s[1] = 0;
	t[0] = 0;
	t[1] = 1;
	r[0] = r0;
	r[1] = r1;

	do {
		// como o tamanho dos vetores é pequeno, talvez precise realocar
		if (i % tam == 19) {
			tam *= 2;
			s = (unsigned long long *) realloc(s, tam * sizeof(unsigned long long));
			t = (unsigned long long *) realloc(t, tam * sizeof(unsigned long long));
			q = (unsigned long long *) realloc(q, tam * sizeof(unsigned long long));
			r = (unsigned long long *) realloc(r, tam * sizeof(unsigned long long));
		}
		
		i++;
		r[i] 	= r[i-2] % r[i-1];
		q[i-1] 	= (r[i-2]-r[i])/r[i-1];
		s[i]	= s[i-2]-q[i-1]*s[i-1];
		t[1]	= t[i-2]-q[i-1]*t[i-1];
	} while (r[i] != 0);


	gcd = r[i-1];
	*inv = t[i-1];

	// se o inverso for negativo, soma n
	do {
		*inv += r1;
	} while (*inv < 0);

	free(s);
	free(t);
	free(q);
	free(r);

	return gcd;
}

unsigned long long q_m(unsigned long long x, unsigned long long H, unsigned long long n)
{
	unsigned long long r;
	unsigned long long tmp;
	unsigned long long mask = 1;

	mask <<= 63;
	r = x;
	
	for (int i = 63; i >= 0; i--) {
		r = r*r % n;
		if (H & mask) 
			r = r*x % n;
		mask >>= 1;
	}

	return r;
}

unsigned long long sieve(unsigned long long N) 
{
	unsigned long long *primes;
	unsigned long long thresh = sqrt(N);
	unsigned long long P;

	primes = (unsigned long long *) malloc(thresh * sizeof(unsigned long long));

	// inicialização do vetor pra aplicação do crivo de Eratóstenes
	for (int i = 2; i < thresh; i++) 
		primes[i] = i;

	for (int i = 2; i < thresh; i++) {
		if (primes[i] == i) 
			P = primes[i];
		// remove os múltiplos de i da lista de primos
		for (int j = i+i; j < thresh; j += i)
			primes[j] = 0;
	}

	return P;
}	
