#include <stdio.h>

int main(void)
{
    printf("これからx(整数)が偶数であるか奇数であるか判定する\n");
    int x;
    printf("xを入力せよ\n");
    scanf("%d", &x);

    if(x%2 == 0)
    {
        printf("xは偶数\n");
    }
    else
    {
        printf("xは奇数\n");
    }
}