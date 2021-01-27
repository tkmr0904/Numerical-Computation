#include <stdio.h>
#include <math.h>

typedef struct x_y
{
    double x;
    double y;
}x_y;

double interpolation_2(double a, double b, double fa, double fb, double x)//2個の点で1次補間する
{
    return fa*(x-b)/(a-b) + fb*(x-a)/(b-a);
}

double interpolation_3(double x0, double x1, double x2, double y0, double y1, double y2, double x)//3個の点で補間する
{
    return y0*(x-x1)*(x-x2)/(x0-x1)/(x0-x2) + y1*(x-x2)*(x-x0)/(x1-x2)/(x1-x0) + y2*(x-x0)*(x-x1)/(x2-x0)/(x2-x1);
}

double interpolation_n(double x_value[], double y_value[], int n, double x)//n個の点で補間する
{
    double sum = 0;

    for(int i = 0; i<n; i++)//Liの総和を求めてsumに代入
    {
        double Li = y_value[i];//Li = y_value[i]*...
        for(int j = 0; j<n; j++)//Liを求める
        {
            if(i != j)
            {
                Li *= (x-x_value[j])/(x_value[i]-x_value[j]);
            }
            else
            {
                /*何もしない*/
            }
        }
        sum += Li;//jに関するfor文で求めたLiを加算
    }
    return sum;
}


double f(double x)
{
    return sin(x)+x;
}


int main()
{


    //double x_value[] = {0.00, 0.20, 0.40, 0.60, 0.80, 1.0, 1.20, 1.40, 1.60, 1.80, 2.00};
    //double y_value[] = {-1.59, -1.03, -0.63, -0.35, -0.16, 0.00, 0.16, 0.35, 0.63, 1.03, 1.59};


    double x_value[80];
    double y_value[80];

    for(int i = 0; i<sizeof(x_value)/sizeof(double); i++)
    {
        x_value[i] = 2+i*0.1;
        y_value[i] = 1/x_value[i];
    }


    FILE* fp;
    fp = fopen("plot.dat", "w");

    for(double x = 3; x<=8; x+=0.01)
    {
        fprintf(fp, "%.6f %.6f\n", x, interpolation_n(x_value, y_value, sizeof(x_value)/sizeof(double), x));
    }

    fclose(fp);

/*
    fp = fopen("plot1.dat", "w");

    for(int i = 0; i<sizeof(x_value)/sizeof(double); i++)
    {
        fprintf(fp, "%.6f %.6f\n", x_value[i], y_value[i]);
    }

    fclose(fp);
*/

}