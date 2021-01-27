#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("これから2次方程式ax^2+bx+cの解を求める\n");

    double a, b, c;//係数
    double D;//判別式

    /*****2つの解の実数部, 虚数部*******Dが0ならx1だけ使われる*/
    double x1_real;
    double x2_real;
    double x1_imaginary;
    double x2_imaginary;
    /****************************************************/


    /******係数を入力*********/
    printf("aを入力せよ\n");
    scanf("%lf", &a);

    printf("bを入力せよ\n");
    scanf("%lf", &b);

    printf("cを入力せよ\n");
    scanf("%lf", &c);
    /**********************/

    D = b*b - 4.0*a*c; //判別式
    printf("\nD = %f\n\n", D);//D = ...


    if(D > 0)//実数解が2つ存在すれば
    {
        printf("実数解が2つ存在する\n\n");

        x1_real = (-b - sqrt(D))/(2.0*a);
        x2_real = (-b + sqrt(D))/(2.0*a);

        /****虚数部は0*******/
        x1_imaginary = 0;
        x2_imaginary = 0;
        /******************/
    }
    else if(D == 0)//実数解が1つのみ存在すれば
    {
        printf("実数解がただ1つ存在し, それ以外の解は存在しない\n\n");

        x1_real      = (-b)/(2.0*a);
        x1_imaginary = 0;
    }
    else//実数解が存在しなければ
    {
        printf("2つの虚数解をもつ\n\n");

        x1_real = (-b)/(2.0*a);
        x2_real = (-b)/(2.0*a);

        x1_imaginary = sqrt(fabs(D))/(2.0*a);
        x2_imaginary = -sqrt(fabs(D))/(2.0*a);
    }

    if(D == 0)//解が1つだけなら
    {
        /****1つだけ表示****/
        printf("実数部: %f, 虚数部: %f\n", x1_real, x1_imaginary);
    }
    else//解が2つ存在するなら
    {
        /*************2つの解を並べて表示*****************************/
        printf("1つ目の解\n");
        printf("実数部: %f, 虚数部: %f\n", x1_real, x1_imaginary);
        printf("2つ目の解\n");
        printf("実数部: %f, 虚数部: %f\n", x2_real, x2_imaginary);
        /*********************************************************/
    }
}