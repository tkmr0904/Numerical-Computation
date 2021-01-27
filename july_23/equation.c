#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n (3)

int sweeping_out(double matrix[n][n+1])
{
    for(int col = 0; col<n; col++) //列ごとに対角成分以外0にする　これを1~n列に渡って行う
    {
        /*対角成分が0ならエラー*/
        if(matrix[col][col] == 0)
        {
            return 1;
        }

        /*対角成分が0でなければ、col列の対角成分が1になるようにcol行を定数倍する*/
        for(int j = col+1; j<n+1; j++)
        {
            matrix[col][j] /= matrix[col][col];
        }
        matrix[col][col] = 1; // /= matrix[col][col]  値が失われるのでforの後で計算する

        /*col行の定数倍を他の行に加えてcol列の対角成分以外0にする*/
        for(int i = 0; i<n; i++)//
        {
            if(i != col) //col行以外なら計算する
            {
                /*i行にcol行の定数倍を加える col列の成分が0になるように*/
                for(int j = col+1; j<n+1; j++)
                {
                    matrix[i][j] -= matrix[col][j] * matrix[i][col];
                }
                matrix[i][col] = 0; // -= matrix[col][col] * matrix[i][col]  値が失われるのでforの後で計算する
            }
            else
            {
                /*col行の場合計算しない*/
            }
            
        }
    }

    return 0;
}

int printmat(double matrix[n][n+1])
{
    for(int i = 0; i<n; i++)
    {
        for(int j = 0; j<n+1; j++)
        {
            printf("%f   ", matrix[i][j]);
        }
        printf("\n");
    }
    return 1;
}

int sweeping_out_inverse(double matrix[n][n*2])
{
    for(int col = 0; col<n; col++) //列ごとに対角成分以外0にする　これを1~n列に渡って行う
    {
        /*対角成分が0ならエラー*/
        if(matrix[col][col] == 0)
        {
            return 1;
        }

        /*対角成分が0でなければ、col列の対角成分が1になるようにcol行を定数倍する*/
        for(int j = col+1; j<n*2; j++)
        {
            matrix[col][j] /= matrix[col][col];
        }
        matrix[col][col] = 1; // /= matrix[col][col]  値が失われるのでforの後で計算する

        /*col行の定数倍を他の行に加えてcol列の対角成分以外0にする*/
        for(int i = 0; i<n; i++)//
        {
            if(i != col) //col行以外なら計算する
            {
                /*i行にcol行の定数倍を加える col列の成分が0になるように*/
                for(int j = col+1; j<n*2; j++)
                {
                    matrix[i][j] -= matrix[col][j] * matrix[i][col];
                }
                matrix[i][col] = 0; // -= matrix[col][col] * matrix[i][col]  値が失われるのでforの後で計算する
            }
            else
            {
                /*col行の場合計算しない*/
            }
        }
    }

    return 0;
}

int gauss(double matrix[n][n+1], double solution[n])
{
    for(int col = 0; col<n-1; col++) //列ごとに対角成分より下を0にする　これを1~n列に渡って行う
    {
        /*対角成分が0ならエラー*/
        if(matrix[col][col] == 0)
        {
            return 1;
        }

        /*対角成分が0でなければ*/
        /*col行の定数倍を他の行に加えてcol列の対角成分より下を0にする*/
        for(int i = col+1; i<n; i++)//
        {
            double alpha = matrix[i][col] / matrix[col][col];
            
            /*i行にcol行の定数倍を加える col列の成分が0になるように*/
            matrix[i][col] = 0; // -= matrix[col][col] * alpha
            for(int j = col+1; j<n+1; j++)
            {
                matrix[i][j] -= matrix[col][j] * alpha;
            }
        }
    }

    /*解を求める*/
    for(int i = n-1; i>=0; i--)
    {
        solution[i] = matrix[i][n];  //まずn+1列目の値を代入
        for(int j = n-1; j>i; j--)   //引き算する
        {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i]; //係数で割る
    }


    return 0;
}

int printsolution(double solution[n])
{
    printf("解はここから\n");
    for(int j = 0; j<n; j++)
    {
        printf("%f\n", solution[j]);
    }
    printf("解はここまで\n");

    return 0;
}

int gauss_seidel(double matrix[n][n+1], double solution[n], double *e, int *k, double epsilon) //収束すれば1、収束しなければ0を返す
{
    double solutionlast[n];

    for(*k = 1; (*k)<50; (*k)++) //k=1から回数を数える ある回数までに収束すれば終了
    {
        for(int i = 0; i<n; i++)
        {
            /*i番目の解の近似値を求める*/
            solutionlast[i] = solution[i];//前の値を記憶
            solution[i] = matrix[i][n];  //まずはn+1列目の値を代入
            for(int j = 0; j<n; j++)     //iとjが異なれば引き算する
            {
                if(i != j)
                {
                    solution[i] -= matrix[i][j] * solution[j];
                }
                else
                {
                    /*何もしない*/
                }
            }
            solution[i] /= matrix[i][i];  //係数で割って近似値を決定する
        }

        /*前回の近似値との差の絶対値の和を求める*/
        *e = 0;
        for(int i = 0; i<n; i++)
        {
            *e += fabs(solution[i] - solutionlast[i]);
        }

        /*収束すれば終了し, 0を返す*/
        if(*e < epsilon)
        {
            return 0;
        }
    }

    /*ある回数まで収束しなければ1を返す*/
    return 1;
}



int main()
{

    double matrix[n][n+1]
    =
/*
    {
        {4, 3, 2, 11},
        {1,-1, 1,-3 },
        {2, 3,-1, 12}
    };
*/

/*
    {
        {3, 1, 1, 10},
        {1, 5, 2, 21},
        {1, 2, 5, 30}
    };
*/

    {
        {10,   1,  2, 23},
        {-2,   5,  2, 23},
        { 5, -10, 20, 75}
    };

    double solution[n] = {0, 0, 0};
    double e;
    int k;

    printf("%d\n", gauss_seidel(matrix, solution, &e, &k, 1e-7));

    //printmat(matrix);
    printf("回数%d\n", k);
    printf("eの値%.15e\n", e);

    printsolution(solution);
}