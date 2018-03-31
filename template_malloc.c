/*
Title:
Frome:
Describe:
---------------------------------------
Input:

Output:

---------------------------------------
Thoughts:

Algorithm analysis:

*/

#include <stdio.h>
#include <stdlib.h>

#define ROW_MAX 960
#define ROW_MIN 3
#define COL_MAX 1440
#define COL_MIN 3

typedef int data_t;

int main()
{
      unsigned int n,Row,Col,i,j;
      data_t **a;  //用二级指针动态申请二维数组

      scanf("%d", &n);
      while(n--)
      {
            scanf("%d %d", &Col, &Row);
            if(Row > ROW_MAX || Row < ROW_MIN || \
               Col > COL_MAX || Col < COL_MIN)
            {
                  printf("Input Overflow\n");
                  break;
            }

            a = (data_t**)malloc(sizeof(data_t*)*Row);
            for(i=0;i<Row;i++)
                  a[i]=(data_t*)malloc(sizeof(data_t)*Col);

            for(i=0;i<Row;i++)
            {
                  for(j=0;j<Col;j++)
                  {
                        scanf("%d", &a[i][j]);
                        printf("%d ", a[i][j]);
                  }
                  printf("\n");
            }

            for(i=0;i<Row;i++)
                  free(a[i]);
            free(a);
      }
      return 0;
}