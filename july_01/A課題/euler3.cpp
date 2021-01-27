#include <stdio.h>
#include <math.h>
#include <thread>

double I(double x, double y)
{
    return -y;
}

double Q(double x, double y)
{
    return (1 - y);
}


double euler(double x0, double y0, double xf, long n, double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    for(long i = 0; i<n; i++)
    {
        y = y + h * df(x, y);
        x = x + h;
    }
    return y;
}

double modeuler(double x0, double y0, double xf, long n, double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;

    for(long i = 0; i<n; i++)
    {
        y = y + h * df(x + 0.5*h, y + 0.5*h*df(x, y));
        x = x + h;
    }
    return y;
}


double RK(double x0, double y0, double xf, long n, double(*df)(double, double))
{
    double h = (xf - x0)/n;

    double x = x0;
    double y = y0;
    
    double k1, k2, k3, k4;

    for(long i = 0; i<n; i++)
    {
        k1 = df(x, y);
        k2 = df(x + 0.5*h, y + 0.5*h*k1);
        k3 = df(x + 0.5*h, y + 0.5*h*k2);
        k4 = df(x +     h, y +     h*k3);

        y = y + (h/6.0)*(k1 + 2*k2 + 2*k3 + k4);
        x = x + h;
    }
    return y;
}



#define power 35



void abc(double h[2][3][power], double y[2][3][power], double y0[2], double(*func[3])(double, double, double, long, double(*)(double, double)), double(*fI_Q[2])(double, double), double ms, long times, int threadnum, int threadsum)
{
    long n;

    for(long i = threadnum; i<power; i+=threadsum)
    {
        for(int j = 0; j<3; j++)//method
        {
            for(int k = 0; k<2; k++)// I or Q
            {
                n = 10*exp2(i);
                h[k][j][i] = ms/n;
                y[k][j][i] = func[j](0.0, y0[k], 1.0, n, fI_Q[k]);
            }
        }

    }
}


int main()
{
        double(*func[3])(double, double, double, long, double(*)(double, double)) = {euler, modeuler, RK};

        double(*fI_Q[2])(double, double) = {I, Q};


        char const * method[3] = {"euler", "modeuler", "RK"};
        char const *I_Q[2] = {"I", "Q"};
        char filename[100];



        double        y[2][3][power];// I or Q / method
        double        h[2][3][power];// I or Q / method

        double solution[2];   // I or Q

        double C = 1.0e-6;
        double R = 1.0e+3;
        double E = 1.0;
        double ms = 1.0;

        double y0[2] = {E/R*1.0e+3, 0.0};



        solution[0] = 1.0*exp(-ms);
        solution[1] = 1-exp(-ms);


  
        std::thread a(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  0, 8);});
        std::thread b(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  1, 8);});
        std::thread c(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  2, 8);});
        std::thread d(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  3, 8);});
        std::thread e(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  4, 8);});
        std::thread f(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  5, 8);});
        std::thread g(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  6, 8);});
        std::thread m(   [&h, &y, &y0, &func, &fI_Q, &ms](){abc(h, y, y0, func, fI_Q, ms, power,  7, 8);});


        a.join();
        b.join();
        c.join();
        d.join();
        e.join();
        f.join();
        g.join();
        m.join();


        for(int k = 0; k<2; k++)// I or Q
        {
            for(int j = 0; j<3; j++)//method
            {
                snprintf(filename, 100, "%s%s%s", "double_", method[j], I_Q[k]);
                FILE* fp = fopen(filename, "w");
                for(long i = 0; i<power; i++)
                {
                    fprintf(fp, "%.15e %.15e\n", h[k][j][i], fabs(y[k][j][i] - solution[k]));
                }
                fclose(fp);
            }
        }




}