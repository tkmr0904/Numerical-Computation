#include <stdio.h>
#include <math.h>


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
        if(i==0)
        {
            printf("%.15f\n", h * df(x, y));
        }

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




int main()
{
    printf("%.15e %.15e\n", euler(0.0f, 1.0f, 1.0f, (10*exp2(21)), I) - (float)exp(-1.0f), 1.0f/(float)(10*exp2(24)));
    printf("%.15e %.15e\n", euler(0.0f, 1.0f, 1.0f, (10*exp2(22)), I) - (float)exp(-1.0f), 1.0f/(float)(10*exp2(24)));
}
//5.960464566356904e-09