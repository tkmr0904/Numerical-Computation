#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define maxnum 100000000 /*最大分割回数*/

double f(double);
double df(double);
double g(double);
double dg(double);
double bisection(double, double, double, double(*)(double), int*);
double regula_falsi(double, double, double, double(*)(double), int*);
double newton(double, double, double(*)(double), double(*)(double), int*);
double secant(double, double, double, double(*)(double), int*);


int main()
{
    int i;
    
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
double bisection(double a0, double b0, double eps, double(*func)(double), int *ptr_i)
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

    for(*ptr_i = 0; *ptr_i<=maxnum; (*ptr_i)++)
    {
        /*この時点でa, bでの関数値が同符号であることはありえない*/
        /*aでの関数値が0であることもありえない*/

        c = (a+b)/2.0;

        if(func(a)*func(c)<=0)//a, cでの関数値が異符号またはcでの関数値が0の場合は
        {
            if(b-a>eps)
            {
                b = c;
                continue;
            }
            else
            {
                return c;
            }
        }
        else //a, cでの関数値が同符号でcでの関数値が0でなく、b, cでの関数値が異符号またはbでの関数値が0の場合は
        {
            if(b-a>eps)
            {
                a = c;
                continue;
            }
            else
            {
                return c;
            }
        }
    }
    //ここに達した場合は解が求まらなかった
    printf("解が求まらなかった\n");
    exit(1);
}

double regula_falsi(double a0, double b0, double eps, double(*func)(double), int *ptr_i)
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

    for(*ptr_i = 0; *ptr_i<=maxnum; (*ptr_i)++)
    {
        /*この時点でa, bでの関数値が同符号であることはありえない*/
        /*aでの関数値が0であることもありえない*/

        c = (a*func(b) - b*func(a))/(func(b) - func(a));

        if(func(a)*func(c)<=0)//a, cでの関数値が異符号またはcでの関数値が0の場合は
        {
            if((c-a)*(b-c)>eps)
            {
                b = c;
                continue;
            }
            else
            {
                return c;
            }
        }
        else //a, cでの関数値が同符号でcでの関数値が0でなく、b, cでの関数値が異符号またはbでの関数値が0の場合は
        {
            if((c-a)*(b-c)>eps)
            {
                a = c;
                continue;
            }
            else
            {
                return c;
            }
        }
    }
    //ここに達した場合は解が求まらなかった
    printf("解が求まらなかった\n");
    exit(1);
}

double newton(double x0, double eps, double(*func)(double), double(*dfunc)(double), int *ptr_i)
{
    double x;
    double x_next = x0;
    for(*ptr_i = 0; *ptr_i<=maxnum; (*ptr_i)++)
    {
        x = x_next;
        x_next = x - func(x)/dfunc(x);
        if(fabs(x_next - x) > eps)
        {
            continue;
        }
        else
        {
            return x_next;
        }
    }
    printf("解が求まらなかった\n");
    exit(1);
}
/*                                             func: 解を求めたい関数,   ptr_i: 回数を書き込む場所   */
double secant(double x0, double x1, double eps, double(*func)(double), int *ptr_i)
{
    double xi0;
    /*後でずらすためにわざとずらして代入*/
    double xi1 = x0;
    double x_next = x1;

    for(*ptr_i = 1; *ptr_i<=maxnum; (*ptr_i)++)
    {
        /***ずらす***/
        xi0 = xi1;
        xi1 = x_next;
        /*********/

        x_next = xi1 - func(xi1) * (xi1 - xi0)/(func(xi1) - func(xi0));//解の推定値を求める

        if(fabs(x_next - xi1) > eps)
        {
            continue;
        }
        else
        {
            return x_next;
        }
    }

    /*一定回数接線を引いても解が収束しなかった場合*/
    printf("解が求まらなかった\n");
    exit(1);
}