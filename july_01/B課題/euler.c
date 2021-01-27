#include <stdio.h>
#include <math.h>



double f(double x, double y)
{
    return x+y;
}

double g(double x, double y)
{
    return (1.0 - y);
}

double I(double x, double y)
{
    return -y;
}

double Q(double x, double y)
{
    return (1 - y);
}


#define number 100


double euler(double x0, double y0, double xf, int n, double arrayx[], double arrayy[], double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    arrayx[0] = x;
    arrayy[0] = y;

    for(int i = 0; i<n; i++)
    {
        y = y + h * df(x, y);
        x = x + h;

        arrayx[i+1] = x;
        arrayy[i+1] = y;
    }
    return y;
}

double modeuler(double x0, double y0, double xf, int n, double arrayx[], double arrayy[], double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    arrayx[0] = x;
    arrayy[0] = y;

    for(int i = 0; i<n; i++)
    {
        y = y + h * df(x + 0.5*h, y + 0.5*h*df(x, y));
        x = x + h;

        arrayx[i+1] = x;
        arrayy[i+1] = y;
    }
    return y;
}


double RK(double x0, double y0, double xf, int n, double arrayx[], double arrayy[], double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    arrayx[0] = x;
    arrayy[0] = y;
    
    double k1, k2, k3, k4;

    for(int i = 0; i<n; i++)
    {
        k1 = df(x, y);
        k2 = df(x + 0.5*h, y + 0.5*h*k1);
        k3 = df(x + 0.5*h, y + 0.5*h*k2);
        k4 = df(x +     h, y +     h*k3);

        y = y + (h/6)*(k1 + 2*k2 + 2*k3 + k4);
        x = x + h;

        arrayx[i+1] = x;
        arrayy[i+1] = y;

    }
    return y;
}




int main()
{

    /*
        double     euler_ =    euler(0.0, 0.0, 2.0,  40) - (1 - exp(-2.0));
        double  modeuler_ = modeuler(0.0, 0.0, 2.0,  40) - (1 - exp(-2.0));
        double        RK_ =       RK(0.0, 0.0, 2.0,  40) - (1 - exp(-2.0));

        double    euler__ =    euler(0.0, 0.0, 2.0, 200) - (1 - exp(-2.0));
        double modeuler__ = modeuler(0.0, 0.0, 2.0, 200) - (1 - exp(-2.0));
        double       RK__ =       RK(0.0, 0.0, 2.0, 200) - (1 - exp(-2.0));




        printf("h=0.05として、オイラー法、修正オイラー法、ルンゲクッタ法における解析解からの差は次のようになった。\n");
        printf("オイラー法:    %.15f\n",    euler_);
        printf("修正オイラー法: %.15f\n", modeuler_);
        printf("ルンゲクッタ法: %.15f\n",       RK_);
        printf("\n");


        printf("さらに、３つの解法において、h=0.01として同様の計算を行った場合、数値解と解析解の差は、h=0.05の場合と比べてそれぞれ次のような比率になった。\n");
        printf("オイラー法:    %.15f\n",    euler__/euler_);
        printf("修正オイラー法: %.15f\n", modeuler__/modeuler_);
        printf("ルンゲクッタ法: %.15f\n",       RK__/RK_);
    */
    
        double(*func[3])(double, double, double, int, double[], double[], double(*)(double, double)) = {euler, modeuler, RK};


        char *method[3] = {"euler", "modeuler", "RK"};
        char *I_Q[2] = {"I", "Q"};
        char filename[100];

        double        x[number + 1];
        double        y[2][3][number + 1];
        double solution[2][number + 1];

        double C = 1.0e-6;
        double R = 1.0e+3;
        double E = 1.0;
        double ms = 6.0;


        /*******************Iの場合**********************/
        for(int j = 0; j<3; j++)
        {
            func[j](0, E/R*1.0e+3, ms, number, x, y[0][j], I);
        }

        for(int i = 0; i<number; i++)
        {
            solution[0][i] = 1.0*exp(-x[i]);
        }
        /*************************************************/

    
        /*******************Qの場合***********************/
        for(int j = 0; j<3; j++)
        {
            func[j](0, 0, ms, number, x, y[1][j], Q);
        }

        for(int i = 0; i<number; i++)
        {
            solution[1][i] = 1 - exp(-x[i]);
        }
        /*************************************************/


        FILE* fp;


        for(int k = 0; k<2; k++)//I, Q
        {
            for(int j = 0; j<3; j++)//euler modeuler RK
            {
                snprintf(filename, 100, "%s%s", method[j], I_Q[k]);
                fp = fopen(filename, "w"); 
                for(int i = 0; i<number; i++)
                {
                    fprintf(fp, "%.15e %.15e\n", x[i], y[k][j][i]);
                }
                fclose(fp);

            
                snprintf(filename, 100, "%s%s%s", "difference_", method[j], I_Q[k]);
                fp = fopen(filename, "w");
                for(int i = 0; i<number; i++)
                {
                    fprintf(fp, "%.15e %.15e\n", x[i], fabs(y[k][j][i]-solution[k][i]));
                }
                fclose(fp);
            }

            snprintf(filename, 100, "%s%s", "solution", I_Q[k]);
            fp = fopen(filename, "w");
            for(int i = 0; i<number; i++)
            {
                fprintf(fp, "%.15e %.15e\n", x[i], solution[k][i]);
            }
            fclose(fp);
        }
    


    




}