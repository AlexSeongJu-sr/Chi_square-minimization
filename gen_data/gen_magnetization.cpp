#include <iostream>
#include <math.h>
#include "ran0.h"

#define J (1e-3*1.60219e-19)
#define mu (9.2741e-24)
#define kB (1.3806e-23)

#define NN 10
#define nmax 1000
#define hrng 250
#define hstp 0.1


using namespace std;

void iteration(double hh, double T, int s[NN][NN][NN])
{
	int i, j, k;
	int ii, jj, kk, nn, pp;
	double dE, r;
	static long idum = 0;

	for (pp = 0; pp <= 1; pp++)
	{
		for (i = 0; i < NN; i++)
			for (j = 0; j < NN; j++)
				for (k = 0; k < NN; k++)
				{
					if ((i + j + k) % 2 == pp) {
						nn = 0;
						for (ii = -1; ii <= 1; ii++)
							for (jj = -1; jj <= 1; jj++)
								for (kk = -1; kk <= 1; kk++)
								{
									if (ii * ii + jj * jj + kk * kk == 1)
										nn += s[(i + ii + NN) % NN][(j + jj + NN) % NN][(k + kk + NN) % NN];
								}
						dE = (J * nn + mu * hh) * (2 * s[i][j][k]);
						r = exp(-dE / kB / T);
						if (ran0(&idum) < r)
						{
							s[i][j][k] = -s[i][j][k];
						}
					}
				}
	}
	return;
}



int main() {

	int i, j, k, h, n;
	int ss;
	double T;
	float hh=0;
	int s[NN][NN][NN];

	for (T = 51; T < 52.5; T=T+0.1) {
		//cout << "T" << " " << T << endl;
		cout << T << " ";
		for (int x = 0; x < 50; x++)
		{
			for (i = 0; i < NN; i++)
				for (j = 0; j < NN; j++)
					for (k = 0; k < NN; k++)
						s[i][j][k] = -1;

			for (n = 0; n < nmax; n++)
				iteration(hh, T, s);

			ss = 0;

			for (i = 0; i < NN; i++)
				for (j = 0; j < NN; j++)
					for (k = 0; k < NN; k++)
						ss += s[i][j][k];

			printf("%f ", (double)ss / (NN * NN * NN));
		}
		cout << endl;
	}

}