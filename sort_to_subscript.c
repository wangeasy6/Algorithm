/*
*   FUNC: 内容不变，将排序后的下标保存到一个数组中。
*/
#include <stdio.h>
#define MAX_NUM 12

int main()
{
    int Count = 0;
    int i,n,t;
    int Content_order[MAX_NUM];
    int Content[MAX_NUM] = {1,2,5,4,3,6,9,8};

    Count = 8;
    if (Count > 1)
    {
        Content_order[0] = 0;
        for (i=1; i<Count; i++)
        {
            Content_order[i] = i;
            for (n=i;n>=1;n--)
            {
                if (Content[Content_order[n]] < Content[Content_order[n-1]])  //后面如果更小，交换
                {
                    t = Content_order[n-1];
                    Content_order[n-1] = Content_order[n];
                    Content_order[n] = t;
                }
                else
                {
                    break;
                }
            }
        }
      }

    printf("order: ");
    for (i=0;i<Count; i++)
    {
      printf("%d,",Content_order[i]);
    }
    printf("\n");

    printf("Content: ");
    for (i=0;i<Count; i++)
    {
      printf("%d,",Content[Content_order[i]]);
    }
    printf("\n");
}
