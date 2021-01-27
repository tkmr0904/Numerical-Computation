#include <stdio.h>
#include <math.h>

double omega = 2;

double I(double x, double y)
{
    return 1.0*omega*cos(omega*x)-y;
}

double Q(double x, double y)
{
    return 1.0*sin(omega*x) - y;
}


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

#define number 1000

int main()
{

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
            func[j](0, 0, ms, number, x, y[0][j], I);
        }

        for(int i = 0; i<number; i++)
        {
            solution[0][i] = omega/(1+omega*omega)*cos(omega*x[i]) + omega*omega/(1+omega*omega)*sin(omega*x[i]) - omega/(1+omega*omega)*exp(-x[i]);
        }
        /*************************************************/

    
        /*******************Qの場合***********************/
        for(int j = 0; j<3; j++)
        {
            func[j](0, 0, ms, number, x, y[1][j], Q);
        }

        for(int i = 0; i<number; i++)
        {
            solution[1][i] = 1/(1+omega*omega)*sin(omega*x[i]) - omega/(1+omega*omega)*cos(omega*x[i]) + omega/(1+omega*omega)*exp(-x[i]);
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

            
                snprintf(filename, 100, "%s%s%s", "error_", method[j], I_Q[k]);
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