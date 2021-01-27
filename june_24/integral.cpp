#include <stdio.h>
#include <math.h>
#include <thread>


typedef struct x_y
{
    long int x;
    double y;
}x_y;

double f(double x)
{
    return x*x*x + x*x;
}

double trapezoidal(double a, double b, int n)
{
    /* 2辺の和*高さ/2 を複数の隣接する台形で和を取る */
    double sum;
    double h = (b-a)/(double)n;

    /************辺の総和を求める**********************/
    sum = 0;                     //リセット
    sum += f(a)+f(b);            //端は1回しか足されない

    for(int i=1; i<=n-1; i++)    //内側は2回足される
    {
        sum += 2.0 * f(a + h*i);
    }
    /***********************************************/

    sum *= h/2.0;  // *高さ/2する

    return sum;
}

double sympson3(double a, double b, int n)
{
    /*   (f(a+0h) + 4f(a+1h) + f(a+2h)) + (f(a+2h) + 4f(a+3h) + f(a+4h)) + (f(a+4h) + 4f(a+5h) + f(a+6h)) + ...   */
    double sum;
    double h = (b-a)/(2.0 * (double)n); //区間をn等分して更に2等分する

    sum = 0; //リセット

    /*和を取ってからh/3倍する*/

    for(int i=0; i<=2*n; i++)
    {
        if(i == 0)         //端は1回しか足されない
        {
            sum += f(a);
        }
        else if(i == 2*n)  //端は1回しか足されない
        {
            sum += f(b);
        }
        else if(i%2 == 0)
        {
            sum += 2.0 * f(a + h*i);  //x+偶数*hの部分は2回足される
        }
        else
        {
            sum += 4.0 * f(a + h*i);  //x+奇数*hの部分は1回ずつ足されるが、各々の係数が4だから4をかける
        }
    }

    sum *= h/3.0;

    return sum;
}

double sympson8(double a, double b, int n)
{
    /*( f(a+0h) + 3f(a+1h) + 3f(a+2h) + f(a+3h) ) + ( f(a+3h) + 3f(a+4h) + 3f(a+5h) + f(a+6h) ) + ( f(a+6h) + 3f(a+7h) + 3f(a+8h) + f(a+9h) ) + ...*/
    double sum;
    double h = (b-a)/(3.0 * (double)n); //区間をn等分して更に3等分する

    sum = 0; //リセット

    /*和を取ってから3h/8倍する*/
    for(int i=0; i<=3*n; i++)
    {
        if(i == 0)         //端は1回しか足されない
        {
            sum += f(a);
        }
        else if(i == 3*n)  //端は1回しか足されない
        {
            sum += f(b);
        }
        else if((i%3 == 1) || (i%3 == 2)) //iが3k+1 もしくは 3k+2の場合
        {
            sum += 3*f(a + h*i);    //係数が3の項が1回ずつ足されるので3倍
        }
        else                //iが3の倍数の場合
        {
            sum += 2*f(a + h*i);    //係数が1の項が2回ずつ足されるので2倍
        }

    }

    sum *= 3.0*h/8.0;

    return sum;
}








double ftrapezoidal(double a, double b, int n, double(*func)(double))
{
    /* 2辺の和*高さ/2 を複数の隣接する台形で和を取る */
    double sum;
    double h = (b-a)/(double)n;

    /************辺の総和を求める**********************/
    sum = 0;                     //リセット
    sum += func(a)+func(b);      //端は1回しか足されない

    for(int i=1; i<=n-1; i++)    //内側は2回足される
    {
        sum += 2.0 * func(a + h*i);
    }
    /***********************************************/

    sum *= h/2.0;  // *高さ/2する

    return sum;
}

double fsympson3(double a, double b, long int n, double(*func)(double))
{
    /*   (f(a+0h) + 4f(a+1h) + f(a+2h)) + (f(a+2h) + 4f(a+3h) + f(a+4h)) + (f(a+4h) + 4f(a+5h) + f(a+6h)) + ...   */
    double sum;
    double h = (b-a)/(2.0 * (double)n);

    //sum += f(a)+f(b);          //端は1回しか足されない

    sum = 0;

    for(long int i=0; i<=2*n; i++)
    {
        if(i == 0)         //端は1回しか足されない
        {
            sum += func(a);
        }
        else if(i == 2*n)  //端は1回しか足されない
        {
            sum += func(b);
        }
        else if(i%2 == 0)
        {
            sum += 2.0 * func(a + h*i);  //x+偶数*hの部分は2回足される
        }
        else
        {
            sum += 4.0 * func(a + h*i);  //x+奇数*hの部分は1回ずつ足されるが、各々の係数が4だから4をかける
        }
    }

    sum *= h/3.0;

    return sum;
}

double fsympson8(double a, double b, long int n, double(*func)(double))
{
    /*( f(a+0h) + 3f(a+1h) + 3f(a+2h) + f(a+3h) ) + ( f(a+3h) + 3f(a+4h) + 3f(a+5h) + f(a+6h) ) + ( f(a+6h) + 3f(a+7h) + 3f(a+8h) + f(a+9h) ) + ...*/
    double sum;
    double h = (b-a)/(3.0 * (double)n); //区間をn等分して更に3等分する

    sum = 0; //リセット

    /*和を取ってから3h/8倍する*/
    for(long int i=0; i<=3*n; i++)
    {
        if(i == 0)         //端は1回しか足されない
        {
            sum += func(a);
        }
        else if(i == 3*n)  //端は1回しか足されない
        {
            sum += func(b);
        }
        else if((i%3 == 1) || (i%3 == 2)) //iが3k+1 もしくは 3k+2の場合
        {
            sum += 3*func(a + h*i);    //係数が3の項が1回ずつ足されるので3倍
        }
        else                //iが3の倍数の場合
        {
            sum += 2*func(a + h*i);    //係数が1の項が2回ずつ足されるので2倍
        }


    }

    sum *= 3.0*h/8.0;

    return sum;
}

float ftrapezoidalf(float a, float b, int n, float(*func)(float))
{
    /* 2辺の和*高さ/2 を複数の隣接する台形で和を取る */
    float sum;
    float h = (b-a)/(float)n;

    /************辺の総和を求める**********************/
    sum = 0;                     //リセット
    sum += func(a)+func(b);      //端は1回しか足されない

    for(int i=1; i<=n-1; i++)    //内側は2回足される
    {
        sum += 2.0f * func(a + h*i);
    }
    /***********************************************/

    sum *= h/2.0f;  // *高さ/2する

    return sum;
}


float fsympson3f(float a, float b, long int n, float(*func)(float))
{
    /*   (f(a+0h) + 4f(a+1h) + f(a+2h)) + (f(a+2h) + 4f(a+3h) + f(a+4h)) + (f(a+4h) + 4f(a+5h) + f(a+6h)) + ...   */
    float sum;
    float h = (b-a)/(2.0f * (float)n);

    //sum += f(a)+f(b);          //端は1回しか足されない

    sum = 0;

    for(long int i=0; i<=2*n; i++)
    {
        if(i == 0)         //端は1回しか足されない
        {
            sum += func(a);
        }
        else if(i == 2*n)  //端は1回しか足されない
        {
            sum += func(b);
        }
        else if(i%2 == 0)
        {
            sum += 2.0f * func(a + h*i);  //x+偶数*hの部分は2回足される
        }
        else
        {
            sum += 4.0f * func(a + h*i);  //x+奇数*hの部分は1回ずつ足されるが、各々の係数が4だから4をかける
        }
    }

    sum *= h/3.0f;

    return sum;
}

float fsympson8f(float a, float b, long int n, float(*func)(float))
{
    /*( f(a+0h) + 3f(a+1h) + 3f(a+2h) + f(a+3h) ) + ( f(a+3h) + 3f(a+4h) + 3f(a+5h) + f(a+6h) ) + ( f(a+6h) + 3f(a+7h) + 3f(a+8h) + f(a+9h) ) + ...*/
    float sum;
    float h = (b-a)/(3.0f * (float)n); //区間をn等分して更に3等分する

    sum = 0; //リセット

    /*和を取ってから3h/8倍する*/
    for(long int i=0; i<=3*n; i++)
    {
        if(i == 0)         //端は1回しか足されない
        {
            sum += func(a);
        }
        else if(i == 3*n)  //端は1回しか足されない
        {
            sum += func(b);
        }
        else if((i%3 == 1) || (i%3 == 2)) //iが3k+1 もしくは 3k+2の場合
        {
            sum += 3*func(a + h*i);    //係数が3の項が1回ずつ足されるので3倍
        }
        else                //iが3の倍数の場合
        {
            sum += 2*func(a + h*i);    //係数が1の項が2回ずつ足されるので2倍
        }


    }

    sum *= 3.0f*h/8.0f;

    return sum;
}


double f2(double x)
{
    return 2/(x*x);
}

double f3(double x)
{
    return 4.0/(1 + x*x);
}

double f4(double x)
{
    return 1/(x*x);
}

float f4f(float x)
{
    return 1.0f/(x*x);
}



#define size 36

void cal(x_y s3[], x_y s8[], x_y s3f[], x_y s8f[], x_y t[], x_y tf[], int threadnum, int threadsum)
{
    for(int i=threadnum; i<size; i+=threadsum)
    {
        /*
            s3[i].y = fsympson3(1, 2, s3[i].x, f4) - 0.5;
            s8[i].y = fsympson8(1, 2, s8[i].x, f4) - 0.5;

            s3f[i].y = fsympson3f(1, 2, s3f[i].x, f4f) - 0.5f;
            s8f[i].y = fsympson8f(1, 2, s8f[i].x, f4f) - 0.5f;
        */

       t[i].y = ftrapezoidal(1, 2, t[i].x, f4) - 0.5;
       tf[i].y = ftrapezoidalf(1, 2, tf[i].x, f4f) - 0.5f;



        if(threadnum == 7)
        {
            printf("%d%%\n", i*100/size);
        }
    }
}


int main()
{
    x_y t[size];
    x_y tf[size];
    x_y s3[size];
    x_y s8[size];
    x_y s3f[size];
    x_y s8f[size];


    tf[0].x =t[0].x = s8f[0].x = s3f[0].x = s8[0].x = s3[0].x = 2;
    for(int i=1; i<size; i++)
    {
        tf[i].x =t[i].x = s8f[i].x = s3f[i].x = s8[i].x = s3[i].x = 2*s3[i-1].x;
    }


    std::thread a([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 0, 8);});
    std::thread b([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 1, 8);});
    std::thread c([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 2, 8);});
    std::thread d([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 3, 8);});
    std::thread e([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 4, 8);});
    std::thread f([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 5, 8);});
    std::thread g([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 6, 8);});
    std::thread h([&s3, &s8, &s3f, &s8f, &t, &tf](){cal(s3, s8, s3f, s8f, t, tf, 7, 8);});

    a.join();
    b.join();
    c.join();
    d.join();
    e.join();
    f.join();
    g.join();
    h.join();



    FILE* fp;

/*
    fp = fopen("s3.dat", "w");
    for(int i=0; i<size; i++)
    {
        fprintf(fp, "%ld %.20e\n", s3[i].x, fabs(s3[i].y));
    }
    fclose(fp);


    fp = fopen("s8.dat", "w");
    for(int i=0; i<size; i++)
    {
        fprintf(fp, "%ld %.20e\n", s8[i].x, fabs(s8[i].y));
    }
    fclose(fp);

    fp = fopen("s3f.dat", "w");
    for(int i=0; i<size; i++)
    {
        fprintf(fp, "%ld %.20e\n", s3f[i].x, fabs(s3f[i].y));
    }
    fclose(fp);

    fp = fopen("s8f.dat", "w");
    for(int i=0; i<size; i++)
    {
        fprintf(fp, "%ld %.20e\n", s8f[i].x, fabs(s8f[i].y));
    }
    fclose(fp);
*/

    fp = fopen("trapezoidal_double", "w");
    for(int i=0; i<size; i++)
    {
        fprintf(fp, "%ld %.20e\n", t[i].x, fabs(t[i].y));
    }
    fclose(fp);

    fp = fopen("trapezoidal_float", "w");
    for(int i=0; i<size; i++)
    {
        fprintf(fp, "%ld %.20e\n", tf[i].x, fabs(tf[i].y));
    }
    fclose(fp);



}