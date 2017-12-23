/*
*   Title: 排列索引
*   From: 工程需求
*   正题: 内容不变，将排序后的下标保存到一个数组中，之后按排序下标索引达到排序的目的
*/
#include <stdio.h>
#define MAX_NUM 12

int main()
{
    int i,n;
    int Content_order[MAX_NUM];
    int Content[MAX_NUM] = {5,1,2,4,3,6,9,8,4,65,7,3},*tmp;

    Content_order[0] = 0;
    for (i=1; i<MAX_NUM; i++)
    {
        tmp = &Content[i];
        for (n=i-1; n>=0; n--)
        {
            if (Content[Content_order[n]] > *tmp)  //后面如果更小，交换
            {
                Content_order[n+1] = Content_order[n];
            }
            else
            {
                break;
            }
        }
        Content_order[n+1] = i;
    }

    printf("order: ");
    for (i=0; i<MAX_NUM; i++)
    {
        printf("%d,",Content_order[i]);
    }
    printf("\n");

    printf("Content: ");
    for (i=0; i<MAX_NUM; i++)
    {
        printf("%d,",Content[Content_order[i]]);
    }
    printf("\n");
}
