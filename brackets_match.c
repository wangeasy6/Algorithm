/*
* Title:括号配对问题
* From:http://acm.nyist.net/JudgeOnline/problem.php?pid=2
* 描述
*    现在，有一行括号序列，请你检查这行括号是否配对。
* 输入
*     第一行输入一个数N（0<N<=100）,表示有N组测试数据。后面的N行输入多组输入数据，每组输入数据都是一个字符串S(S的长度小于10000，且S不是空串），测试数据组数少于5组。数据保证S中只含有"[","]","(",")"四种字符
* 输出
*     每组输入数据的输出占一行，如果该字符串中所含的括号是配对的，则输出Yes,如果不配对则输出No

* 样例输入
5
[(])
])
([[]()])
([([([([([([([([([([([([([((((([[[[[([([])])]]]]])))))])])])])])])])])])])])])])
([([([([([([([([([([([([([((((([[[[[([([])])]]]]])))))])])](])])])])])])])])])])

* 样例输出

No
No
Yes
Yes
No
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100
#define MAX_LEN  10000
#define STACK_MAX_LEN  (MAX_LEN/2 + 1)

int parse_str(char *str, int len)
{
    int i = 0,stack_i = 0;
    char stack[STACK_MAX_LEN] = {0},tmp;

    if(str == NULL || len <= 0)
    {
        return 0;
    }

    for(i = 0;i < len;i++)
    {
        tmp = str[i];
        if(tmp == '[' || tmp == '(')
        {
            stack[stack_i] = tmp;
            stack_i++;

            if(stack_i > STACK_MAX_LEN)
            {
                return 0;
            }
        }
        else if(tmp == ']' || tmp == ')')
        {
            if(stack_i == 0)
            {
                return 0;
            }

            if(tmp == ']' && stack[stack_i-1] == '[')
            {
                stack_i--;
            }
            else if(tmp == ')' && stack[stack_i-1] == '(')
            {
                stack_i--;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }

    if(stack_i == 0)
    {
        return 1;
    }

    return 0;
}

int main()
{
    unsigned int line,i;
    char *Line_Str;

    Line_Str = (char *)malloc(MAX_LEN);
    if(Line_Str == NULL)
    {
        printf("malloc failed\n");
        return 0;
    }

    scanf("%d", &line);
    if(line < 1 || line > MAX_LINE)
    {
        printf("Input line error:%d\n", line);
        return 0;
    }

    for(i = 0;i < line; i++)
    {
        memset(Line_Str, 0, MAX_LEN);
        scanf("%s", Line_Str);
        if(parse_str(Line_Str, strlen(Line_Str)) == 1)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    free(Line_Str);
    return 1;
}
