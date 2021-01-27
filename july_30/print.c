#include <stdio.h>

double f(double x)
{
    return 1 - 2*x + 3*x*x - 4*x*x*x + 5*x*x*x*x;
}

int main()
{
    FILE* fp;
    fp = fopen("data1.1_5", "w");
    for(double i = 0; i<=2; i+=0.2)
    {
        fprintf(fp, "%f %f\n", i, f(i));
    }
    fclose(fp);
}