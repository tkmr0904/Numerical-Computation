#include <stdio.h>
#include <math.h>

double area_circle(double r)
{
    return M_PI*r*r;
}

int main()
{
    double r;
    scanf("%lf", &r);
    printf("%f\n", area_circle(r));
}