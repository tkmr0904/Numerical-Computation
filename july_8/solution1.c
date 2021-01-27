#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxnum 60 /*最大分割回数*/

double f(double);
double df(double);
double g(double);
double dg(double);
double bisection(double, double, double, double(*)(double), int*, double[]);
double regula_falsi(double, double, double, double(*)(double), int*, double[]);
double newton(double, double, double(*)(double), double(*)(double), int*, double[]);
double secant(double, double, double, double(*)(double), int*, double[]);


int main()
{
    int i;
    FILE* fp;

    double solution[4][maxnum];
    double ex_solution = newton(0.0, 1.0e-8, f, df, &i, solution[2]);

    fp = fopen("bisection", "w");
    bisection(0.0, 1.0, 1.0e-8, f, &i, solution[0]);
    for(i = 0; i<maxnum; i++)
    {
        fprintf(fp, "%d, %.15e\n", i, fabs(solution[0][i] - ex_solution));
    }

    fclose(fp);

    fp = fopen("regula_falsi", "w");
    regula_falsi(0.0, 1.0, 1.0e-8, f, &i, solution[1]);
    for(i = 0; i<maxnum; i++)
    {
        fprintf(fp, "%d, %.15e\n", i, fabs(solution[1][i] - ex_solution));
    }

    fclose(fp);

    fp = fopen("newton", "w");
    newton(1.0, 1.0e-8, f, df, &i, solution[2]);
    for(i = 0; i<maxnum; i++)
    {
        fprintf(fp, "%d, %.15e\n", i, fabs(solution[2][i] - ex_solution));
    }
    
    fclose(fp);

    fp = fopen("secant", "w");
    secant(0.0, 1.0, 1.0e-8, f, &i, solution[3]);
    for(i = 0; i<maxnum; i++)
    {
        fprintf(fp, "%d, %.15e\n", i, fabs(solution[3][i] - ex_solution));
    }

    fclose(fp);

    
    
}


double f(double x)
{
    return x-cos(x);
}

double df(double x)
{
    return 1+sin(x);
}


double g(double x)
{
    return exp(x*x*x*x + x*x + x) - 2;
}

double dg(double x)
{
    return exp(x*x*x*x + x*x + x) * (4*x*x*x + 2*x + 1);
}

/*                a0とb0: 最初のaとb      func: 解を求めたい関数   ptr_i: 回数を書き込む場所    */
double bisection(double a0, double b0, double eps, double(*func)(double), int *ptr_i, double solution[])
{
    if(func(a0)*func(b0)>=0)
    {
        if(func(a0)*func(b0)>0)
        {
            printf("2分法で両端の初期値a, bでの関数値がどちらも同じ符号なのでこれは不適\n");
            exit(1);
        }
        else if(func(a0)==0)//少なくとも一方が解である場合
        {
            return a0;
        }
        else
        {

            return b0;
        }
    }

    //ここに達するのは両端の初期値での関数値が異符号の場合のみ

    /************/
    double a = a0;
    double b = b0;
    double c;
    /************/

    for(*ptr_i = 0; *ptr_i<maxnum; (*ptr_i)++)
    {
        /*この時点でa, bでの関数値が同符号であることはありえない*/
        /*aでの関数値が0であることもありえない*/

        c = (a+b)/2.0;
        solution[*ptr_i] = c;

        if(func(a)*func(c)<=0)//a, cでの関数値が異符号またはcでの関数値が0の場合は
        {
            b = c;
            continue;
        }
        else //a, cでの関数値が同符号でcでの関数値が0でなく、b, cでの関数値が異符号またはbでの関数値が0の場合は
        {
            a = c;
            continue;
        }
    }
    return c;
}

double regula_falsi(double a0, double b0, double eps, double(*func)(double), int *ptr_i, double solution[])
{
    if(func(a0)*func(b0)>=0)
    {
        if(func(a0)*func(b0)>0)
        {
            printf("2分法で両端の初期値a, bでの関数値がどちらも同じ符号なのでこれは不適\n");
            exit(1);
        }
        else if(func(a0)==0)//少なくとも一方が解である場合
        {
            return a0;
        }
        else
        {
            return b0;
        }
    }

    //ここに達するのは両端の初期値での関数値が異符号の場合のみ

    /************/
    double a = a0;
    double b = b0;
    double c;
    /************/

    for(*ptr_i = 0; *ptr_i<maxnum; (*ptr_i)++)
    {
        /*この時点でa, bでの関数値が同符号であることはありえない*/
        /*aでの関数値が0であることもありえない*/

        c = (a*func(b) - b*func(a))/(func(b) - func(a));
        solution[*ptr_i] = c;


        if(func(a)*func(c)<=0)//a, cでの関数値が異符号またはcでの関数値が0の場合は
        {
            b = c;
            continue;
        }
        else //a, cでの関数値が同符号でcでの関数値が0でなく、b, cでの関数値が異符号またはbでの関数値が0の場合は
        {
            a = c;
            continue;
        }
    }

    return c;
}

double newton(double x0, double eps, double(*func)(double), double(*dfunc)(double), int *ptr_i, double solution[])
{
    double x;
    double x_next = x0;
    for(*ptr_i = 0; *ptr_i<maxnum; (*ptr_i)++)
    {
        x = x_next;
        x_next = x - func(x)/dfunc(x);
        solution[*ptr_i] = x_next;


        continue;
    }
    return x_next;
}


/*                                             func: 解を求めたい関数,   ptr_i: 回数を書き込む場所   */
double secant(double x0, double x1, double eps, double(*func)(double), int *ptr_i, double solution[])
{
    double xi0;
    /*後でずらすためにわざとずらして代入*/
    double xi1 = x0;
    double x_next = x1;

    for(*ptr_i = 0; *ptr_i<maxnum; (*ptr_i)++)
    {
        /***ずらす***/
        xi0 = xi1;
        xi1 = x_next;
        /*********/

        x_next = xi1 - func(xi1) * (xi1 - xi0)/(func(xi1) - func(xi0));//解の推定値を求める
        solution[*ptr_i] = x_next;

        continue;
    }
    return x_next;
}