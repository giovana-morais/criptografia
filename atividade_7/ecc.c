/* Giovana Vieira de Morais	587591 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	int x;
	int y;
} ponto;

ponto dobro(ponto G, int p, int a);
ponto soma(ponto G, ponto Q, int p);
ponto a_d(ponto P, int H, int n, int a);

int eea(int r0, int r1);
int checa_negativo(int num, int mod);
int checa_infinito(ponto P);

void main()
{
	/* n	: escalar multiplicativo
	 * a	: parâmetro da curva
	 * p	: primo
	 * x e y: coordenadas do ponto G
	 */
	int n, a, p;
	ponto G, R;


	scanf("%d", &n);
	while (n != 0) {
		scanf("%d %d %d %d", &a, &p, &G.x, &G.y);
		R = a_d(G, n, p, a);
		printf("===================================================\n");
		printf("n: %d\n", n);
		printf("R: (%d, %d)\n", R.x, R.y);
		scanf("%d", &n);

	}
	
}

// TODO: tentar fazer sem os vetores
int eea(int r0, int r1)
{
	int *t;
	int *q, *r;
	int gcd;
	int i = 1;
	int tam = 20;
	int inv;

	t = (int *) malloc(tam * sizeof(int));
	q = (int *) malloc(tam * sizeof(int));
	r = (int *) malloc(tam * sizeof(int));

	t[0] = 0;
	t[1] = 1;
	r[0] = r0;
	r[1] = r1;

	while (r[i] != 0) {
		// como o tamanho dos vetores é pequeno, talvez precise realocar
		if (i % tam == 19) {
			tam *= 2;
			t = (int *) realloc(t, tam * sizeof(int));
			q = (int *) realloc(q, tam * sizeof(int));
			r = (int *) realloc(r, tam * sizeof(int));
		}

		i++;
		r[i]	= r[i-2] % r[i-1];
		q[i-1]	= (r[i-2]-r[i])/r[i-1];
		t[i]	= t[i-2]-q[i-1]*t[i-1];
	}

	gcd = r[i-1];

	if (gcd != 1)
		inv = -1;
	else {
		inv = t[i-1];
		// se o inverso for negativo, soma n
		while (inv < 0)
			inv += r0;
	}

	free(t);
	free(q);
	free(r);

	return inv;
}


ponto a_d(ponto P, int H, int n, int a)
{
	int mask = 1 << sizeof(int)*8-1;
	int aux = 0;
	ponto N, Q;

	N = P;
	Q.x = 0; Q.y = 0;
	
	while (H > 0){
		if (H % 2 == 1) 
			Q = soma(Q, N, n);
		N = dobro(N, n, a);
		H >>= 1;
	}

	return Q;
}


ponto soma(ponto G, ponto Q, int p)
{
	int lambda, tmp;
	int num, denom;
	ponto R;

	// se ambos os pontos são infinitos ou se são inversos
	if (	(checa_infinito(G) && checa_infinito(Q)) || 
		(G.x == Q.x && (G.y == ((p-Q.y)%p) || Q.y == ((p-G.y)%p)))) {
		R.x = 0;
		R.y = 0;
	} else if (checa_infinito(Q)) {
		R.x = G.x;
		R.y = G.y;
	} else if (checa_infinito(G)) {
		R.x = Q.x;
		R.y = Q.y;
	} else {
		num = (G.y - Q.y) % p;
		num = checa_negativo(num, p);

		denom = eea(p, checa_negativo(G.x - Q.x, p));
		lambda = (denom * num) % p;
		R.x = (lambda*lambda % p) + (-Q.x - G.x % p);
		R.x = checa_negativo(R.x, p);
		R.y = (lambda * (Q.x - R.x) - Q.y) % p;
		R.y = checa_negativo(R.y, p);

	}
	return R;
}

ponto dobro(ponto G, int p, int a)
{
	int lambda;
	int denom, num;
	ponto R;

	if (checa_infinito(G)) {
		R.x = 0;
		R.y = 0;
	} else {
		denom = (3 * (G.x*G.x) + a) % p;
		num = eea(p, 2*(G.y) % p);

		lambda = (denom * num) % p;

		R.x = (lambda*lambda - G.x - G.x) % p;
		R.x = checa_negativo(R.x, p);
		R.y = (lambda * (G.x - R.x) - G.y) % p;
		R.y = checa_negativo(R.y, p);
	}
	return R;
}

int checa_negativo(int num, int mod)
{
	while (num < 0) {
		num += mod;
	}

	return num;
}

int checa_infinito(ponto P) 
{
	if (!P.x && !P.y)
		return 1;
	return 0;
}
