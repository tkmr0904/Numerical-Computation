#include <stdio.h>
#include <math.h>

int main()
{
    double a = 1;
    double b = 0.01;

    double x1 = (-a+sqrt(a*a-4*b))/2;
    double x2 = (-a-sqrt(a*a-4*b))/2;

    printf("x1 = %.20f\n", x1);
    printf("x2 = %.20f\n", x2);
    printf("x1x2-b = %.20f\n", x1*x2-b);

    printf("\n");

    x1 = b/x2;

    printf("x1 = %.20f\n", x1);
    printf("x2 = %.20f\n", x2);
    printf("x1x2-b = %.20f\n", x1*x2-b);




}