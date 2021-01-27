#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("半径(実数)を入力せよ\n");
    double r;
    scanf("%lf", &r);
    printf("円の面積は%f\n", M_PI*r*r);
}