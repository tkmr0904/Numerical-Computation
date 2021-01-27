#include <stdio.h>

int fact(int n)//n!を求める
{
    if((n==0)||(n==1))//1!と0!は1
    {
        return 1;
    }
    else//1より大きければ
    {
        return n * fact(n-1);//n! = n(n-1)!
    }
}

int main(void)
{
    printf("これからn!(階乗)を求める\n");

    int n;

    int iscorrect = 0;//nに適切な値が入力されたかどうか
    
    while(iscorrect == 0)//nに0以上の値が入力されるまで繰り返す
    {
        printf("n(0以上の整数)を入力せよ\n");
        scanf("%d", &n);
        printf("n = %dが入力された\n", n);

        if(n >= 0)
        {
            printf("n! = %d\n", fact(n));//階乗を表示
            iscorrect = 1;//ループを抜ける
        }
        else
        {
            printf("これは適切な値ではないのでやり直し\n");
            iscorrect = 0;//やり直し
        }
    }
}