#include <stdio.h>

int main(void)
{
    printf("これからa/bを求める\n");

    double a, b;

    printf("aを入力せよ\n");
    scanf("%lf", &a);

    printf("bを入力せよ\n");
    scanf("%lf", &b);

    if(b != 0)
    {
        printf("a/b = %12.3e\n", a/b);
    }
    else
    {
        printf("b = %fなのでa/bを計算できない\n", b);
    }
}
