/*
* Title:�����������
* From:http://acm.nyist.net/JudgeOnline/problem.php?pid=2
* ����
*    ���ڣ���һ���������У����������������Ƿ���ԡ�
* ����
*     ��һ������һ����N��0<N<=100��,��ʾ��N��������ݡ������N����������������ݣ�ÿ���������ݶ���һ���ַ���S(S�ĳ���С��10000����S���ǿմ���������������������5�顣���ݱ�֤S��ֻ����"[","]","(",")"�����ַ�
* ���
*     ÿ���������ݵ����ռһ�У�������ַ�������������������Եģ������Yes,�������������No

* ��������
5
[(])
])
([[]()])
([([([([([([([([([([([([([((((([[[[[([([])])]]]]])))))])])])])])])])])])])])])])
([([([([([([([([([([([([([((((([[[[[([([])])]]]]])))))])])](])])])])])])])])])])

* �������

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
