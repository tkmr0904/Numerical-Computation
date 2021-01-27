#include <stdio.h>
#include <math.h>

#define ndatamax 100
#define nmax 100



int printmat(void* pmat, int n)
{
    double (*matrix)[n][n+1] = pmat;

    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n+1; j++)
        {
            printf("%f   ", (*matrix)[i][j]);
        }
        printf("\n");
    }
    return 1;
}
/*c:xのべき乗の係数   nd:データの個数   nc:係数の個数(次数+1)    xとcを用いて近似された関数値を求めyとの差の2乗和を求める*/
double sum_square(double x[], double y[], double c[], int nd, int nc)
{
    double sum = 0;

    for(int i = 0; i<nd; i++)
    {
        /*fxを計算*/
        double fx = 0;
        for(int j = 0; j<nc; j++)
        {
            fx += c[j] * pow(x[i], j);
        }

        /*fxが求まったらy[i]との差の2乗を加える*/
        sum += (y[i] - fx) * (y[i] - fx);
    }

    return sum;
}