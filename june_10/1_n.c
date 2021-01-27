#include <stdio.h>

int main(void)
{
    int n = 1000000;
    printf("n=%d\n", n);

    {
        double sum_1_n = 0.0;//1からnまでの和
        double sum_n_1 = 0.0;//nから1までの和

        for(int i = 1; i <= n; i++)//1からnまで
        {
            sum_1_n += 1.0/((double)i*(double)(i+1));
        }

        for(int i = n; 1 <= i; i--)//nから1まで
        {
            sum_n_1 += 1.0/((double)i*(double)(i+1));
        }

        printf("double\n");
        printf("i=1から順番に足し算 :%.20f\n", sum_1_n);
        printf("i=nから順番に足し算 :%.20f\n", sum_n_1);
    }

    printf("\n");

    {
        float sum_1_n = 0.0f;//1からnまでの和
        float sum_n_1 = 0.0f;//nから1までの和

        for(int i = 1; i <= n; i++)//1からnまで
        {
            sum_1_n += 1.0f/((float)i*(float)(i+1));
        }

        for(int i = n; 1 <= i; i--)//nから1まで
        {
            sum_n_1 += 1.0f/((float)i*(float)(i+1));
        }

        printf("float\n");
        printf("i=1から順番に足し算 :%.20f\n", sum_1_n);
        printf("i=nから順番に足し算 :%.20f\n", sum_n_1);
    }
}

