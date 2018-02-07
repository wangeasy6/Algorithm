/*
Title:乘数密码
From：http://acm.nyist.edu.cn/JudgeOnline/problem.php?pid=769
描述：
      乘数密码也是一种替换密码，其加密变换是将明文字母串逐位乘以密钥k并进行模运算，数学表达式如下：

      E(m)=k*m mod q,   gcd(k,q)=1 (即k，q互素)。

      当k与q互素时，明文字母加密成密文字母的关系为一一映射。
      现有一经过乘法加密的密文，请破译出它的明文。

输入：
      输入包含多组数据,不超过1000组。第一行输入包含组数。
      之后每组包含一个字符串和一个正整数k，字符串全部由大写字母组成，长度不超过50，k是与q互素的数,q=26，k<26。
输出：
      每组输出数据单独占一行，输出对应的明文。

样例输入：
1
ILOVEYOU 3

样例输出：
UVWHKIWY
*/

#include <stdio.h>
#include <string.h>
#define STR_MAX_LEN 51
#define g_q 26

int main()
{
      int groups,k,len,i,n,tmp = 0;
      char str[STR_MAX_LEN] = {0};

      scanf("%d", &groups);
      while(groups--)
      {
            memset(str, 0, STR_MAX_LEN);
            scanf("%s", str);
            scanf("%d", &k);
            if(k<1 || k>25 || (k%2 == 0) || k==13)
                  break;

            len = strlen(str);
            for(i = 0; i < len; i++)
            {
                  for(n = 0; n < k; n++)
                  {
                        tmp = g_q*n+(str[i]-65);
                        if(tmp%k==0 && (tmp/k) < 26)
                        {
                              tmp /= k;
                              break;
                        }
                  }
                  printf("%c",tmp + 65);
            }
            putchar('\n');
      }

      return 0;
}