#include <stdio.h>
#include <stdlib.h>

unsigned long long eea(unsigned long long r0, unsigned long long r1, unsigned long long *inv);
long long unsigned s_m(long long unsigned x, unsigned long long H, unsigned long long n);

/* A única linha da entrada contém três inteiros N, E, e C, onde 15 <= N <= 10^9 
, 1 <= E < N e 1 <= C < N, de forma que N e E constituem a chave pública do algoritmo 
RSA descrita acima e C é uma mensagem criptografada com essa chave pública. */
void main() 
{
	unsigned long long r0, r1, gcd, inv;
	unsigned long long N, E, C, M;

	scanf("%llu %llu %llu", &N, %C, &E);
	if (N < 15 || E < 1 || C < 1 || C > N) {
		printf("Erro: entrada inválida\n");
		return;
	}
}

// TODO: tratar caso do retorno negativo
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
	free(s);
	free(t);
	free(q);
	free(r);

	return gcd;
}

long long unsigned s_m(long long unsigned x, unsigned long long H, unsigned long long n)
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
