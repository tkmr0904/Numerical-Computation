#include <stdio.h>
#include <math.h>



struct format
{
    char   str[100];
    double k;
};


void printstr(struct format const array[], int);


int main(void)
{


    double a=1.0/0.0;
    double b=1.0/a;


    double f = 1.0;
    double g = f;

    while((1.0+g)>1.0)
    {
        f = g;
        g *= 0.5;
    }

    a=1.0;
    b=0.01;

    double x1 = (-a+sqrt(a*a-4*b))/2;
    double x2 = (-a-sqrt(a*a-4*b))/2;





    struct format const array[] = 
    {
        {"%f"       , 0.0/0.0           }, 
        {"%f"       , 1.0/0.0           }, 
        {"%.20f"    , b                 }, 
        {"%f"       , 1.0/1.0e-313      }, 
        {"%f"       , sqrt(-1)          }, 
        {"%f"       , 1.0+sqrt(-1)      }, 
        {"%.20f"    , pow(sqrt(2.0), 2) },
        {"%.20f"    , 0.5+0.1           }, 
        {"%.20f"    , 0.5+0.25+0.125    },
        {"%.20e"    , f                 },
        {"%.20f"    , f*0.5+1.0         },
        {"%.20e"    ,x1*x2-b            }
    };

    printstr(array, sizeof(array)/sizeof(struct format));
}


void printstr(struct format const array[], int len)
{
    char str[len][100];

    int  i = 0;
    while(i<len)
    {
        snprintf(str[i], 100, array[i].str, array[i].k);
        i++;
    }
    
    for(int i = 0; i<len; i++)
    {
        printf("(%d): %s\n", i+1, str[i]);
    }


}