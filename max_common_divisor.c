/*
Title: 欧几里德算法求最大公约数(辗转相除法)
Frome: http://acm.nyist.net/JudgeOnline/problem.php?pid=556
描述
    编写程序，输入两个正整数x和y，求它们的最大公约数。

输入
    有多组测试数据，以EOF结束。
    每组测试数据有2个整数x、y。
输出
    每组数据输出一行。
样例输入

8,6
EOF

样例输出

2
*/

#include <stdio.h>
#include <string.h>

int main()
{
    char tmp;
    int x,y,r;
    do{
        scanf("%d%c%d", &x, &tmp, &y);
        if(x <= 0 || y <= 0)
            break;
        //printf("%d %c %d\n", x, tmp, y);

        if(x < y)
        {
            r = x;
            x = y;
            y = r;
        }
        do{
                r = x%y;
                y = x;
                x = r;
        }while(r);

        printf("%d\n", y);
    }while(1);

    return 1;
}

/*
欧几里得辗转相除法证明:
基本概念：
两个数的最大公约数是指能同时整除它们的最大正整数；
互质是公约数只有1的两个整数，叫做互质整数；
GCD 是Greatest common divisor的缩写即最大公约数；
将 a%n=0 写作 n|a；

证： GCD(a,b) == GCD(b,a%b) (a>=b,b>0)
1. 令 c = GCD(a,b)，设 a=mc,b=nc
2. 设 r = a%b,设 k = a/b
3. 则 r = a - kb = mc -knc = (m-kn)c
4. 由3可得，c|r
5. m-kn 与 n 互质(用反证法进行证明：设存在m-kn=xd,n=yd(d>1)，则m=kn+xd = kyd+xd = (ky+x)d，则 a = mc = (ky+x)cd，b = nc = ycd，则a与b的一个公约数 cd > c，故c非ab的最大公约数，与条件矛盾，因此c也是b与r的最大公约数)
6. 所以 GCD(a,b) == GCD(b,a%b)
*/
