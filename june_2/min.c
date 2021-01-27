#include <stdio.h>

int min_int(int const x, int const y)//2つの整数を受け取り, 小さい方を返す
{
    if(x>y)
    {
        return y;
    }
    else
    {
        return x;
    }
}

int main(void)
{
    printf("これから2つの整数x, yを比較して小さい値を求める\n");

    int x, y;

    printf("まずは、xを入力せよ\n");
    printf("x = ");
    scanf("%d", &x);

    printf("次に、yを入力せよ\n");
    printf("y = ");
    scanf("%d", &y);

    printf("小さい方の値は%d\n", min_int(x, y));
}