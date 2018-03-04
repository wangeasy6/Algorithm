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

#define MAX_NUMBER 5000 //可输入最大值
#define MAX_BIT (10240) //数组位数
#define DIVISOR (10000) //除数
#define DIVISOR_P "%.5d" //输入占位符

int main()
{	int number,i,carry,multiplier,bit = 0;
	int ret[MAX_BIT] = {0};
	
	scanf("%d", &number);
	if(number<1 || number>5000)
	{
		printf("Input number overflow\n");
		return -1;
	}
	
	ret[0] = 1;
	for(multiplier = 2; multiplier <= number; multiplier++)
	{
		carry = 0;
		for(i = 0; i <= bit; i++)
		{
			ret[i] = ret[i]*multiplier + carry;
			carry = ret[i]/DIVISOR;
			ret[i] = ret[i]%DIVISOR;
		}
		if(carry>0) {bit++;ret[bit] = carry;}
	}
	
	printf("%d",ret[bit]); 
	for(i=bit-1;i>=0;i--) printf(DIVISOR_P,ret[i]);
	return 0;
}
/*
思路：
大数的阶乘，即使使用最大的 64位 Unsigned 数也存不下。
就得将结果用 int数组 存，并根据乘法运算规则分步计算和存储。
分步计算：
1、首先初始化数组为1
2、在将每个小于输入的数和已有结果相乘
3、bit 代表已有的数组中的位数，它随进位（carry）而加一
4、最高位在最后，所以最后倒序输出
备注：
对于除数的选择，可以是10000/100000，要保证 DIVISOR*MAX_NUMBER < INT_MAX，且 DIVISOR > MAX_NUMBER （DIVISOR 属于 10^n)

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
