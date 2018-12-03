/* Giovana Vieira de Morais	587591 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sieve(unsigned long long N);
void dobro(int *xg, int *yg, int p);
void soma(int *xg, int *yg, int xq, int yq, int p);
int s_m(int x, int H, int n);
int eea(int r0, int r1);

void main()
{
	/* n	: escalar multiplicativo
	 * a	: parâmetro da curva
	 * p	: primo
	 * x e y: coordenadas do ponto G
	 */
	int n, a, p, x, y;

	// teste
	n = 3; a = 3; o = 13; x = 2; y = 10;


}

// TODO: testar os casos em que o resultado de xg - xq é negativo
// TODO: tentar fazer sem os vetores
int eea(int r0, int r1)
{
	int *t;
	int *q, *r;
	int gcd;
	int i = 1;
	int tam = 20;

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

int s_m(int xp, int yp, int H, int n)
{
	int  r;
	int xt, yt;
	xt = xp; yt = yp;

	r = 1;
	while (H > 0){
		// dessa forma, pega bit a bit do expoente H
		if (H % 2 == 1)
			soma(&xt, &yt, xp, yp, n);
			// r = r*x % n;
		H >>= 1;
		dobro(&xt, &yt, x);
		//x = x*x % n;
	}
	return r;
}

void soma(int *xg, int *yg, int xq, int yq, int p)
{
	int lambda, xr, yr;
	int num, denom;

	num = (*yg - yq) % p;
	denom = eea(*xg - yg, p);

	lambda = (denom * num) % p;

	xr = (pow(lambda,2) - xg - xg) % p;
	yr = (lambda * (xg - xr) - yg) % p;
}

void dobro(int *xg, int *yg, int p)
{
	int lambda;
	int xr, yr;
	int denom, nu,;

	denom = (3 * pow(*xg,2) + a) % p;
	num = eea(2*(*yg), p);

	lambda = (denom * num) % p;

	xr = (pow(lambda,2) - xg - xg) % p;
	yr = (lambda * (xg - xr) - yg) % p;

	*xg = xr;
	*yg = yr;
}
