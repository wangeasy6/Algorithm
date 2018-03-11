/*
Title：24点问题
给出 4 张牌，计算是否可以通过 普通四则运算和括号 得到 24.可行输出 1，否则输出 0.

解题思路：
暴力破解，得出所有运算可能。
4张牌最多有3个基本的运算，两组括号。
复杂度是常量的：总的可能性为
4张牌有 4！ = 12 种的排列；
只考虑基础运算的情况是 4^3 = 64 种情况；
括号的可能性为以下6种：{(12),(23),(34),(123),(234),1(2(34)),1((23)4)}；
但是其中可以去除加法、和乘除对于括号没有区别的情况； 
所以总的情况为： 12*64*6 - n == 4608-n
*/
#include <stdio.h>
#include <math.h>

#define MAX_CARD 4
#define MAX_METHOD 4
#define TARGET_RESULT 24
#define IS_TARGET(x) if(x==TARGET_RESULT){putchar('1');putchar('\n');goto GET_CARD;}
typedef int (* operation)(int i,int j);      //通过typedef定义回调函数

int card[MAX_CARD] = {0};
int card_t[MAX_CARD] = {0};
operation opt[MAX_METHOD];
char optc[MAX_METHOD] = {'+','-','*','/'};

int plus(int i,int j){
	return i + j;
}
int minus(int i,int j){
	
	return i>j?i-j:j-i;
}
int mult(int i,int j)
{
	return i*j;
}
int division(int i,int j)
{
	if(i < j || j == 0) return 0;
	return (int)floor(i/j);
}

int run(int i,int j,int k,int *ret);

int main()
{
	int c1,c2,c3,c4;
	int i,j,k,ret,n = 0;
	opt[0] = plus;opt[1] = minus;opt[2] = mult;opt[3] = division;
	
	do{
GET_CARD:
		for(i = 0; i < MAX_CARD; i++)
		{
			scanf("%d", &card_t[i]);
			if(card_t[i] < 1 || card_t[i] > 10)
			{
				break;
			}
		}
		if(i != MAX_CARD)
			break;
		for(i = 0;i<MAX_CARD;i++)printf("%d ", card_t[i]);printf("| ");

		for(c1 = 0; c1 < MAX_CARD; c1++){
		for(c2 = 0; c2 < MAX_CARD; c2++){
			if(c2 == c1) continue;
		for(c3 = 0; c3 < MAX_CARD; c3++){
			if(c3 == c1 || c3 == c2) continue;
		for(c4 = 0; c4 < MAX_CARD; c4++)
		{
			if(c4 == c1 || c4 == c2 || c4 == c3) continue;
			card[0] = card_t[c1];card[1] = card_t[c2];card[2] = card_t[c3];card[3] = card_t[c4];
			for(i = 0; i<MAX_METHOD; i++)
			{
				for(j = 0; j<MAX_METHOD; j++)
				{
					for(k = 0,ret = 0; k<MAX_METHOD; k++)
					{
						run(i,j,k, &ret);
						IS_TARGET(ret);
						//printf("%d, %d %d %d\n", ret,i,j,k);
					}
				}
			}
		}
		}
		}
		}
		
		printf("0\n");
	}while(1);
	
	return 1;
}

int run(int i,int j,int k,int *ret)
{
	int tmp;
	
	//1234
	*ret = opt[i](card[0],card[1]);
	*ret = opt[j](*ret,card[2]);
	*ret = opt[k](*ret,card[3]);
	if(*ret == TARGET_RESULT){ printf("%d %c %d %c %d %c %d,1234 | ",\
	card[0],optc[i],card[1],optc[j],card[2],optc[k],card[3]); return 0;}
	
	//(23)
	tmp = opt[j](card[1],card[2]);
	*ret = opt[i](card[0],tmp);
	*ret = opt[k](*ret,card[3]);
	if(*ret == TARGET_RESULT){ printf("%d %c %d %c %d %c %d,23 | ",\
	card[0],optc[i],card[1],optc[j],card[2],optc[k],card[3]); return 0;}
	
	//(34)
	tmp = opt[k](card[2],card[3]);
	*ret = opt[i](card[0],card[1]);
	*ret = opt[j](*ret,tmp);
	if(*ret == TARGET_RESULT){ printf("%d %c %d %c %d %c %d,34 | ",\
	card[0],optc[i],card[1],optc[j],card[2],optc[k],card[3]); return 0;}
	
	//(234)
	tmp = opt[j](card[1],card[2]);
	tmp = opt[k](tmp, card[3]);
	*ret = opt[i](card[0],tmp);
	if(*ret == TARGET_RESULT){ printf("%d %c %d %c %d %c %d,234 | ",\
	card[0],optc[i],card[1],optc[j],card[2],optc[k],card[3]); return 0;}
	
	//1(2(34))
	tmp = opt[k](card[2],card[3]);
	tmp = opt[j](card[1],tmp);
	*ret = opt[i](card[0],tmp);
	if(*ret == TARGET_RESULT){ printf("%d %c %d %c %d %c %d,(2(34)) | ",\
	card[0],optc[i],card[1],optc[j],card[2],optc[k],card[3]); return 0;}
	
	//1((23)4)
	tmp = opt[k](card[1],card[2]);
	tmp = opt[j](tmp,card[3]);
	*ret = opt[i](card[0],tmp);
	if(*ret == TARGET_RESULT){ printf("%d %c %d %c %d %c %d,((23)4) | ",\
	card[0],optc[i],card[1],optc[j],card[2],optc[k],card[3]); return 0;}
}
