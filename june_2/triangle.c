#include <stdio.h>
#include <math.h>

void output_triangle(int deg_)//度数(int)を渡せばsin, cos, tanが横に並べられて表示される
{
    /*度数とラジアンを格納*/
    int    deg = deg_;
    double rad = deg_ / 180.0 * M_PI;

    /*数式をここに記憶させる*/
    char sin_[20]; char cos_[20]; char tan_[20];

    /*数式を格納する*/
    snprintf(sin_, sizeof(sin_)/sizeof(char), "sin%2d° = %8f", deg, sin(rad));
    snprintf(cos_, sizeof(cos_)/sizeof(char), "cos%2d° = %8f", deg, cos(rad));
    snprintf(tan_, sizeof(tan_)/sizeof(char), "tan%2d° = %8f", deg, tan(rad));

    /*数式を横に並べる*/
    printf("%s  %s  %s\n", sin_, cos_, tan_);
}

int main(void)
{
    /*角度を格納*/
    int array_deg[9] = {0, 10, 20, 30, 40, 50, 60, 70, 80};

    /*繰り返し用の変数*/
    int i;

    for(i = 0; i < sizeof(array_deg)/sizeof(int); i++)
    {
        /*sin, cos, tanを横に並べて表示させる*/
        output_triangle(array_deg[i]);
    }
}