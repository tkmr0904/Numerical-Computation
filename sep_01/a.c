#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Lを1回求めるときに何回移動するか*/
#define num_samples_dr 100

/*Lを何回求めるか*/ /*すなわちランダムウォークのシミュレーションを何回行うか*/
#define num_samples_L  100



int main()
{
    /***************Lの値に関する変数*****************/
    double L_sum; /*ここにサンプルを加えていく*/
    double L_first;   /*最初に求まるLの値*/
    double L_average; /*平均値を求めてここに格納する*/
    /*********************************************/

    /******************乱数の初期設定******************/
    int seed = 1219071; /*seedとして学籍番号*/
    srand48(seed);     /*初期化*/
    /************************************************/

    /*これからLの和を求めたいので、まずは0に初期化する*/
    L_sum = 0;

    /*一定回数だけLのサンプルを求め、それらの和をとる*/
    for(int j = 0; j<num_samples_L; j++)
    {
        /*サンプルを取る前に初期位置を原点とする*/
        double x = 0;
        double y = 0;

        /*一定回数だけランダムに移動する*/
        for(int i = 0; i<num_samples_dr; i++)  
        {
            /*0から1の乱数を求める*/
            double r = drand48();        

            /*0から2piまでの乱数を求める*/
            double theta = r * 2*M_PI;   

            /*ランダムな方向に距離1だけ移動する*/
            x += cos(theta);
            y += sin(theta);
        }

        /*Lの値*/
        double L = sqrt(x*x + y*y);

        /*移動距離をサンプル1個分として加算する*/
        L_sum += L;

        /*最初に求まるLの値を格納する*/ /*最初だけ実行する*/
        if(j == 0)
        {
            L_first = L;
        }
    }

    /*平均値を求めてここに格納する*/
    L_average = L_sum/num_samples_L;

    /*平均値などを表示する*/
    printf("最初の移動距離は%f\n", L_first);
    printf("移動距離の平均値は%f\n", L_average);
}