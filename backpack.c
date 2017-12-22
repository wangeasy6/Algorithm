/*
Title: 背包问题
From: http://acm.nyist.net/JudgeOnline/problem.php?pid=106
描述
    现在有很多物品（它们是可以分割的），我们知道它们每个物品的单位重量的价值v和重量w（1<=v,w<=10）；如果给你一个背包它能容纳的重量为m（10<=m<=20）,你所要做的就是把物品装到背包里，使背包里的物品的价值总和最大。

输入
    第一行输入一个正整数n（1<=n<=5）,表示有n组测试数据；
    随后有n测试数据，每组测试数据的第一行有两个正整数s，m（1<=s<=10）;s表示有s个物品。接下来的s行每行有两个正整数v，w。
输出
    输出每组测试数据中背包内的物品的价值和，每次输出占一行。
样例输入

2
3 15
5 10
2 8
3 9

10 20
5 3
6 7
7 5
5 8
4 4
8 7
9 9
12 10
2 3
2 2

样例输出

65
57

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CASE 5
#define MAX_GOODS 10
#define PACKAGE_MIN_W 10
#define PACKAGE_MAX_W 20
#define GOODS_MAX_W 10
#define VAL 0
#define WGT 1

int groups = 0, goods_num = 0, pack_w = 0, goods[MAX_GOODS][2] = {0};

int get_max_value(void)
{
    int max_value = 0;
    int i,j,tmp_v,tmp_w;

    for(i=1; i<goods_num; i++)
    {
        if(goods[i-1][VAL] < goods[i][VAL])
        {
            tmp_v = goods[i][VAL];
            tmp_w = goods[i][WGT];
            for(j = i; j>0; j--)
            {
                if(goods[j-1][VAL] < tmp_v)
                {
                    goods[j][VAL] = goods[j-1][VAL];
                    goods[j][WGT] = goods[j-1][WGT];
                }
                else
                {
                    break;
                }
            }
            goods[j][VAL] = tmp_v;
            goods[j][WGT] = tmp_w;
        }
    }
/*
    for(i=0; i<goods_num; i++)
    {
        printf("%d ", goods[i][VAL]);
    }
    putchar('\n');
    for(i=0; i<goods_num; i++)
    {
        printf("%d ", goods[i][WGT]);
    }
    putchar('\n');
*/
    for(i=0; i<goods_num; i++)
    {
        if((pack_w-goods[i][WGT]) > 0)
        {
            max_value += (goods[i][VAL] * goods[i][WGT]);
            pack_w -= goods[i][WGT];
        }
        else
        {
            max_value += goods[i][VAL] * pack_w;
            break;
        }
    }
    return max_value;
}

int main()
{
    int i;

    scanf("%d", &groups);
    if(groups<1 || groups>MAX_CASE)
    {
        printf("Input n error\n");
        return 0;
    }

    while(groups--)
    {
        scanf("%d %d", &goods_num, &pack_w);
        if(goods_num<1 || goods_num>MAX_GOODS || pack_w < PACKAGE_MIN_W || pack_w > PACKAGE_MAX_W)
        {
            printf("Input s or m error\n");
            return 0;
        }
        //printf("s=%d, m=%d\n", goods_num, pack_w);

        for(i=0; i<goods_num; i++)
        {
            scanf("%d %d", &goods[i][VAL], &goods[i][WGT]);
            if(goods[i][WGT]<1 || goods[i][WGT]>GOODS_MAX_W)
            {
                printf("Input goods w error\n");
                return 0;
            }
            //printf("v=%d, w=%d\n", goods[i][VAL], goods[i][WGT]);
        }

        //printf("Max_Value:%d\n",get_max_value());
        printf("%d\n",get_max_value());
    }
}

/*
* 所用方法：
*   本来应该是背包问题，但是这道题更像是一道排序题。
*   重要的是这里的物体是可以分割的，使得只需要按价值排序，然后依次装到背包就行了
*
* 复杂度：
*   时间复杂度，此处是由排序算法所决定的，这里使用的是插入排序，复杂度为 O(n^2)
*   空间复杂度，此处为 O(1)
*/
