/*
Title:数独
From：http://acm.nyist.net/JudgeOnline/problem.php?pid=722&rec=sim
描述
    数独是一种运用纸、笔进行演算的逻辑游戏。玩家需要根据9×9盘面上的已知数字，推理出所有剩余空格的数字，并满足每一行、每一列、每一个3*3宫内的数字均含1-9，不重复。 每一道合格的数独谜题都有且仅有唯一答案，推理方法也以此为基础，任何无解或多解的题目都是不合格的。

输入
    第一行有一个数n（0< n <100），表示有n组测试数据，每组测试数据是由一个9*9的九宫格构成，0表示对应的格子为空
输出
    输出一个9*9的九宫格，为这个数独的答案

样例输入

2
0 0 5 3 0 0 0 0 0
8 0 0 0 0 0 0 2 0
0 7 0 0 1 0 5 0 0
4 0 0 0 0 5 3 0 0
0 1 0 0 7 0 0 0 6
0 0 3 2 0 0 0 8 0
0 6 0 5 0 0 0 0 9
0 0 4 0 0 0 0 3 0
0 0 0 0 0 9 7 0 0

0 0 0 5 0 0 0 0 9
4 5 8 0 6 0 0 0 3
0 7 0 8 0 0 0 0 6
0 0 0 3 0 4 0 1 5
0 0 4 6 0 0 2 0 0
0 0 5 0 2 0 7 0 4
3 0 7 0 0 8 4 0 1
0 9 2 4 0 1 3 0 0
0 0 1 7 3 6 0 0 0


样例输出

1 4 5 3 2 7 6 9 8
8 3 9 6 5 4 1 2 7
6 7 2 9 1 8 5 4 3
4 9 6 1 8 5 3 7 2
2 1 8 4 7 3 9 5 6
7 5 3 2 9 6 4 8 1
3 6 7 5 4 2 8 1 9
9 8 4 7 6 1 2 3 5
5 2 1 8 3 9 7 6 4

2 1 6 5 4 3 8 7 9
4 5 8 9 6 7 1 2 3
9 7 3 8 1 2 5 4 6
7 2 9 3 8 4 6 1 5
1 3 4 6 7 5 2 9 8
6 8 5 1 2 9 7 3 4
3 6 7 2 9 8 4 5 1
8 9 2 4 5 1 3 6 7
5 4 1 7 3 6 9 8 2
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

#define MAX_CASE 100

static int nine_grid[9][9] = {0};
static int trace_i=0;

int is_determine(int value)
{
    int ret;
    switch (value) {
        case 2:
            ret =  1;
            break;
        case 4:
            ret = 2;
            break;
        case 8:
            ret = 3;
            break;
        case 16:
            ret = 4;
            break;
        case 32:
            ret = 5;
            break;
        case 64:
            ret = 6;
            break;
        case 128:
            ret = 7;
            break;
        case 256:
            ret = 8;
            break;
        case 512:
            ret = 9;
            break;
        default:
            return 0;
    }
    return ret;
}

int is_conflict(unsigned char col, unsigned char row)
{
    int i,j;
    int grid_row, grid_col;

    for(i = 0; i < 9; i++)
    {
        if(i != row && nine_grid[col][i] == nine_grid[col][row])
        {
            printf("Get conflict:%d [%d][%d] ==  [%d][%d]\n", nine_grid[col][row], col, i, col, row);
            return 1;
        }
    }
    for(i = 0; i < 9; i++)
    {
        if( i != col && nine_grid[i][row] == nine_grid[col][row])
        {
            printf("Get conflict:%d [%d][%d] ==  [%d][%d]\n", nine_grid[col][row], i, row, col, row);
            return 1;
        }
    }

    grid_row = (row/3)*3 + 3;
    grid_col = (col/3)*3 + 3;
    for(i=grid_row-3; i<grid_row; i++)
    {
        for(j=grid_col-3; j<grid_col; j++)
        {
            if ( i == row && j == col)
            {
                continue;
            }
            if(nine_grid[j][i] == nine_grid[col][row])
            {
                printf("Get conflict:%d [%d][%d] ==  [%d][%d]\n", nine_grid[col][row], j, i, col, row);
                return 1;
            }
        }
    }

    return 0;
}

int i_2pow(unsigned char ii)
{
    int ret;
    switch (ii)
    {
        case 0:
            ret = 1;
            break;
        case 1:
            ret = 2;
            break;
        case 2:
            ret = 4;
            break;
        case 3:
            ret = 8;
            break;
        case 4:
            ret = 16;
            break;
        case 5:
            ret = 32;
            break;
        case 6:
            ret = 64;
            break;
        case 7:
            ret = 128;
            break;
        case 8:
            ret = 256;
            break;
        case 9:
            ret = 512;
            break;
        default:
            ret = 0;
            break;
    }
    return ret;
}

int get_Optional(int row, int col)
{
    int i,j,grid_row,grid_col;
    int optional = 1022;

    for(i=0;i<9;i++)
    {
        if(nine_grid[i][col] != 0)
        {
            optional &= ~i_2pow(nine_grid[i][col]); //(int)pow(2,nine_grid[i][col])
        }
    }

    for(j=0;j<9;j++)
    {
        if(nine_grid[row][j] != 0)
        {
            optional &= ~i_2pow(nine_grid[row][j]);
        }
    }

    grid_row = (row/3)*3 + 3;
    grid_col = (col/3)*3 + 3;
    for(i=grid_row-3; i<grid_row; i++)
    {
        for(j=grid_col-3; j<grid_col; j++)
        {
            if(nine_grid[i][j] != 0)
            {
                optional &= ~i_2pow(nine_grid[i][j]);
            }
        }
    }

    return optional;
}

int Brute_force(int trace_i)
{
    int optional,i,back = trace_i?(trace_i - 1):trace_i;

    do {
        if(nine_grid[trace_i/9][trace_i%9] == 0)
        {
            break;
        }
        if(trace_i == 80)
        {
            break;
        }
    } while(trace_i++);

    optional = get_Optional(trace_i/9, trace_i%9);
    if(trace_i == 80 && is_determine(optional) != 0)
    {
        nine_grid[trace_i/9][trace_i%9] = is_determine(optional);
        return 1;
    }
    for(i=1; i<10; i++)
    {
        if(optional & (1<<i))
        {
            nine_grid[trace_i/9][trace_i%9] = i;
            if (Brute_force(trace_i+1))
            {
                return 1;
            }
        }
    }

    nine_grid[trace_i/9][trace_i%9] = 0;
    trace_i = back;
    return 0;
}

int main()
{
    int groups,i,j,conflict = 0;
    int determined_num,tmp_num, tmp_val;
    char line[18] = {0};

    scanf("%d", &groups);
    if(groups<1 || groups>=MAX_CASE)
    {
        printf("groups num wrong\n");
        return 0;
    }

    while(groups--)
    {
        for(i=0; i<9; i++)
        {
            for(j=0; j<9; j++)
            {
                scanf("%d", &nine_grid[i][j]);
                if(nine_grid[i][j] < 0 || nine_grid[i][j] > 9)
                {
                    break;
                }
            }
        }
        if(i != 9 && j != 9)
        {
            printf("Get number error:[%d][%d] =  %d\n", i, j, nine_grid[i][j]);
            break;
        }

        determined_num=0;
        for(i=0; i<9; i++)
        {
            for(j=0; j<9; j++)
            {
                if(nine_grid[i][j] != 0)
                {
                    determined_num++;
                    if( is_conflict(i,j))
                    {
                        conflict = 1;
                        break;
                    }
                }
            }
            if (conflict)
                break;
        }
        if(conflict)
        {
            conflict = 0;
            determined_num = 0;
            break;
        }

        while(determined_num!=81)
        {
            tmp_num = determined_num;
            for(i=0; i<9; i++)
            {
                for(j=0; j<9; j++)
                {
                    if(nine_grid[i][j] == 0)
                    {
                        if(tmp_val = is_determine(get_Optional(i,j)))
                        {
                            nine_grid[i][j] = tmp_val;
                            determined_num++;
                        }
                    }
                }
            }

            if(determined_num == tmp_num)
            {
                if(Brute_force(0))
                {
                    determined_num = 81;
                }
                else
                {
                    printf("brute forec failed\n");
                    break;
                }
            }
        }

        if(determined_num != 81)
        {
            break;
        }

        for(i=0; i<9; i++)
        {
            for(j=0; j<9; j++)
            {
                printf("%d ", nine_grid[i][j]);
                if(j == 8)
                {
                    putchar('\n');
                }
            }
        }
        putchar('\n');
    }

    return 1;
}

/*
* 解题思路：
*   1、首先获取输入
*   2、获取已确定的个数，判断是否冲突
*   3、遍历判断是否可以直接根据九宫格定义确定
*   4、使用回溯法，遍历所有的可能，当最后一个格子填满，则返回1
*   5、输出九宫格
* 复杂度：
*   空间复杂度：
*   时间复杂度：
*/