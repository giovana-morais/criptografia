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
ponto a_d(ponto P, int H, int n);

int eea(int r0, int r1);
int checa_negativo(int num, int mod);


void main()
{
	/* n	: escalar multiplicativo
	 * a	: parâmetro da curva
	 * p	: primo
	 * x e y: coordenadas do ponto G
	 */
	int n, a, p;
	ponto G, R;

	// teste
	G.x = 2;
	G.y = 10;

	n = 2; a = 3; p = 13;
	
}

// TODO: tentar fazer sem os vetores
int eea(int r0, int r1)
{
	if (r0 < r1){
		int aux;
		aux = r0;
		r0 = r1;
		r1 = aux;
	}
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
		// TODO: prestar atenção nisso aqui
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


ponto a_d(ponto P, int H, int n)
{
	int  r;
	ponto T;
	T.x = P.x;
	T.y = P.y;

	while (H > 0){
		// dessa forma, pega bit a bit do expoente H
		if (H % 2 == 1)
			P = soma(T, P, n);
			// r = r*x % n;
		H >>= 1;
		T = dobro(T, x, n);
		//x = x*x % n;
	}
	return T;
}


ponto soma(ponto G, ponto Q, int p)
{
	int lambda, tmp;
	int num, denom;
	ponto R;

	num = (G.y - Q.y) % p;
	checa_negativo(num, p);

	tmp = G.x - G.y;
	tmp = checa_negativo(tmp, p);
	denom = eea(tmp, p);
	lambda = (denom * num) % p;

	R.x = (lambda*lambda - Q.x - G.x) % p;
	R.x = checa_negativo(R.x, p);
	R.y = (lambda * (Q.x - R.x) - Q.y) % p;
	R.y = checa_negativo(R.y, p);

	printf("soma: (%d, %d)\n", R.x, R.y);
	return R;
}

ponto dobro(ponto G, int p, int a)
{
	int lambda;
	int denom, num;
	ponto R;

	denom = (3 * (G.x*G.x) + a) % p;
	denom = checa_negativo(denom, p);
	num = eea(2*(G.y) % p, p);

	lambda = (denom * num) % p;

	R.x = (lambda*lambda - G.x - G.x) % p;
	R.x = checa_negativo(R.x, p);
	R.y = (lambda * (G.x - R.x) - G.y) % p;
	R.y = checa_negativo(R.y, p);
	printf("dobro: (%d, %d)\n", R.x, R.y);

	return R;
}

int checa_negativo(int num, int mod)
{
	while (num < 0) {
		num += mod;
	}

	return num;
}
