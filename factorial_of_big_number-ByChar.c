/*
Title:大数阶乘
From： http://acm.nyist.edu.cn/JudgeOnline/problem.php?pid=28
描述
    我们都知道如何计算一个数的阶乘，可是，如果这个数很大呢，我们该如何去计算它并输出它？

输入
    输入一个整数m(0<m<=5000)
输出
    输出m的阶乘，并在输出结束之后输入一个换行符
	
样例输入
    50
样例输出
    30414093201713378043612608166064768844377641568960512000000000000
*/

#include <stdio.h>
#include <string.h>

#define MAX_NUMBER 5000
#define MAX_BIT (16*1024)

char *strrev(char *str, size_t len)
{

    char    *start = str;
    char    *end = str + len - 1;
    char    ch;

    if (str != NULL)
    {
        while (start < end)
        {
            ch = *start;
            *start++ = *end;
            *end-- = ch;
        }
    }
    return str;
}

int main()
{	int number,t,multiplier,index = 0,bit = 0,i,j,carry;
	char ret[MAX_BIT] = {0};
	char mult_tmp[4][MAX_BIT] = {0};
	
	scanf("%d", &number);
	if(number<1 || number>5000)
	{
		printf("Input number overflow\n");
		return -1;
	}
	
	if(number == 1 || number == 2)
	{
		printf("ret:%d\n",number);
		return 0;
	}
	
	if(number < 13)		// 12及以下可以直接计算
	{
		for(t = 1; number>1;number--)
		{
			t *= number;
		}
		printf("ret: %u\n", t);
		return 0;
	}
	
	memset(ret, -1, sizeof(char)*MAX_BIT);
	snprintf(ret, sizeof(ret), "%d", number*(number-1));
	strrev(ret, strlen(ret));
	for(i=0; ret[i] != -1;i++)
	{
		ret[i] -= 48;
	}
	ret[i-1] = -1;
	
	#if 1
	for(number -= 2; number > 1; number --)
	{
		memset(mult_tmp, -1, sizeof(char)*4*MAX_BIT);
		for(t = number,bit = 0, carry = 0; t != 0; t/=10,bit++)	//按 个十百千 的顺序乘
		{
			multiplier = t % 10;
			if(multiplier == 0)
				continue;
			
			memset(mult_tmp[bit], 0, sizeof(char)*bit);
			for(i = 0,carry = 0; ret[i] != -1; i++)
			{
				mult_tmp[bit][i + bit] = (multiplier * ret[i] + carry) % 10;
				if(multiplier * ret[i] + carry)
				{
					carry = (multiplier * ret[i] + carry) / 10;
				}
				else
				{
					carry = 0;
				}
			}
			mult_tmp[bit][i+bit] = carry?carry:-1;
		}
		
		for(i=0,carry = 0; mult_tmp[0][i] != -1 || mult_tmp[1][i] != -1 || \
						mult_tmp[2][i] != -1 || mult_tmp[3][i] != -1;i++)
		{
			for(j = 0,t = 0; j < 4; j++)
			{
				t += mult_tmp[j][i] == -1?0:mult_tmp[j][i];
			}
			t  += carry;
			ret[i] = t%10;
			if(t)
			{
				carry = t/10;
			}
			else
			{
				carry = 0;
			}
		}
		ret[i] = carry?carry:-1;
	}
	#endif

	for(i=0; ret[i] != -1;i++)
	{
		ret[i] += 48;
	}
	ret[i] = '\0';
	strrev(ret, strlen(ret));
	printf("ret: %s\n", ret);
	return 0;
}
/*
思路：
大数的阶乘，即使使用最大的 64位 Unsigned 数也存不下。
就得将结果用 char数组 存，并根据乘法运算规则分步计算和存储。
分步计算：
5000 以下，按位乘，保存进位，将结果分别保存在一个 Temp字符串 中，移位相应的位；
再将各个位乘的结果相加。

求阶乘的位数，可以用斯特林(Stirling)公式求解：
#include <math.h>
#define PI 3.141592654
#define E 2.71828182846
int Stirling(int n)
{
    int s=1;
    if(n>3)
        s=log10(2*PI*n)/2+n*log10(n/E)+1;
    return s;
}
*/
