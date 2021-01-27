#include <stdio.h>
#include <math.h>
#include <thread>

float I(float x, float y)
{
    return -y;
}

float Q(float x, float y)
{
    return (1 - y);
}


float euler(float x0, float y0, float xf, long n, float(*df)(float, float))
{
    float h = (xf - x0)/n;

    float x = x0;
    float y = y0;

    for(long i = 0; i<n; i++)
    {
        y = y + h * df(x, y);
        x = x + h;
    }
    return y;
}

float modeuler(float x0, float y0, float xf, long n, float(*df)(float, float))
{
    float h = (xf - x0)/n;

    float x = x0;
    float y = y0;

    for(long i = 0; i<n; i++)
    {
        y = y + h * df(x + 0.5f*h, y + 0.5f*h*df(x, y));
        x = x + h;
    }
    return y;
}


float RK(float x0, float y0, float xf, long n, float(*df)(float, float))
{
    float h = (xf - x0)/n;

    float x = x0;
    float y = y0;
    
    float k1, k2, k3, k4;

    for(long i = 0; i<n; i++)
    {
        k1 = df(x, y);
        k2 = df(x + 0.5f*h, y + 0.5f*h*k1);
        k3 = df(x + 0.5f*h, y + 0.5f*h*k2);
        k4 = df(x +     h, y +     h*k3);

        y = y + (h/6.0f)*(k1 + 2*k2 + 2*k3 + k4);
        x = x + h;
    }
    return y;
}



#define power 35



void abc(float h[2][3][power], float y[2][3][power], float y0[2], float(*func[3])(float, float, float, long, float(*)(float, float)), float(*fI_Q[2])(float, float), float ms, long times, int threadnum, int threadsum)
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
                y[k][j][i] = func[j](0.0f, y0[k], 1.0f, n, fI_Q[k]);
            }
        }

    }
}


int main()
{
        float(*func[3])(float, float, float, long, float(*)(float, float)) = {euler, modeuler, RK};

        float(*fI_Q[2])(float, float) = {I, Q};


        char const * method[3] = {"euler", "modeuler", "RK"};
        char const *I_Q[2] = {"I", "Q"};
        char filename[100];



        float        y[2][3][power];// I or Q / method
        float        h[2][3][power];// I or Q / method

        float solution[2];   // I or Q

        float C = 1.0e-6f;
        float R = 1.0e+3f;
        float E = 1.0f;
        float ms = 1.0f;

        float y0[2] = {E/R*1.0e+3f, 0.0f};



        solution[0] = 1.0f*exp(-ms);
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
                snprintf(filename, 100, "%s%s%s", "float_", method[j], I_Q[k]);
                FILE* fp = fopen(filename, "w");
                for(long i = 0; i<power; i++)
                {
                    fprintf(fp, "%.15e %.15e\n", h[k][j][i], fabs(y[k][j][i] - solution[k]));
                }
                fclose(fp);
            }
        }




}