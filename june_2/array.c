#include <stdio.h>

int main(void)
{
    int number[4] = {0, 2, 4, 6};

    int sum = 0;

    for(int i = 0; i < sizeof(number)/sizeof(int); i++)//配列の終わりまで繰り返す
    {
        sum += number[i];
    }

    printf("%d\n", sum);
}