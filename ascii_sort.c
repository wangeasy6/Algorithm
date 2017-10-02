/*
描述
    输入三个字符（可以重复）后，按各字符的ASCII码从小到大的顺序输出这三个字符。
来源：
    http://acm.nyist.net/JudgeOnline/problem.php?pid=4

输入
    第一行输入一个数N,表示有N组测试数据。后面的N行输入多组数据，每组输入数据都是占一行，有三个字符组成，之间无空格。
输出
    对于每组输入数据，输出一行，字符中间用一个空格分开。
样例输入

2
qwe
asd

样例输出

e q w
a d s
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sort_str(char *str, int len)
{
    int i;
    char tmp;

    if(str == NULL || len != 3)
    {
        return 0;
    }

    if(str[1] < str[0])
    {
        tmp = str[1];
        str[1] = str[0];
        str[0] = tmp;
    }

    for(i=2;i>0;i--)
    {
        if(str[i] < str[i-1])
        {
            tmp = str[i];
            str[i] = str[i-1];
            str[i-1] = tmp;
        }
    }

    return 1;
}

int main()
{
    int line,i;
    char str[4] = {0};
    scanf("%d", &line);

    for(i=0;i<line;i++)
    {
        memset(str, 0, 4);
        scanf("%s", str);
        sort_str(str, strlen(str));
        printf("%c %c %c\n", str[0], str[1], str[2]);
    }

    return 1;
}
