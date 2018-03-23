/*
Title：商队运输费
From：赛码（http://exercise.acmcoder.com/online/online_judge_ques?ques_id=3071&konwledgeId=139）
题目描述:
很久以前，某王国拥有 n 个大城市，为了方便交通，国王下令修建了大量的用于连接首都和其他各大城市高速路。
为节省经费，王国采用了一套优秀的修建方案，使得任何一个大城市都能从首都直接或者通过其他大城市间接到达。并且，如果不重复经过大城市，从首都到达每个大城市的方案都是唯一的。
G商队是王国重要的运输商队，他们奔波于各大城市之间，为王国的人们运输商品，实现长途贸易。所以，从一个城市马不停蹄地到另一个城市成了G商队最常做的事情。他们有一个钱袋，用于存放往来城市间的运输费。
在运输过程中G商队发现，如果不在某个城市停下来休整，在连续行进过程中，他们所花的运输费与他们已走过的距离有关，在走第x千米到第x+1千米这一千米中（x是整数），他们花费的运输费是x+10这么多。也就是说走1千米花费11，走2千米要花费23。
G商队想知道：他们从某一个城市出发，如果中间不休息，到达另一个城市，所有可能花费的运输费中最多是多少呢？

输入的第一行包含一个整数n，表示包括首都在内的王国的城市数
城市从1开始依次编号，1号城市为首都。
接下来n-1行，描述王国的高速路（王国的高速路一定是n-1条）
每行三个整数Pi, Qi, Di，表示城市Pi和城市Qi之间有一条高速路，长度为Di千米。输入城市数（〈10），长度（〈=100）

样例输入:

5
1 2 2
1 3 1
2 4 5
2 5 4

输出一个整数，表示G商队最多花费的运输费是多少。

样例输出:

135

解题思路：
首先建立一个城市树，标记叶子节点，然后从叶子节点依次从左向右深度搜索。
*/

#include <iostream>
#include <stdlib.h>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

#define MAX_NUMBER_OF_CITY 10
#define MAX_LINGTH_OF_PATH 100

typedef struct __NODE
{
	struct __NODE *next_node;
	struct
	{
		int city_number;
		int len;
	}city_info;
}NODE;

typedef struct __NODE_HEAD
{
	struct __NODE *next_node;
	int child_number;
}HEAD_NODE;

int max_len = 0;
HEAD_NODE city[MAX_NUMBER_OF_CITY];

int add_node(int city_1, int city_2, int len)
{
	NODE *child_node = NULL,*tmp_node = NULL;

	child_node = (NODE*)malloc(sizeof(NODE));
	if(child_node == NULL)
	{
		return 0;
	}

	child_node->city_info.city_number = city_2;
	child_node->city_info.len = len;

	if(city[city_1].next_node == NULL)
	{
		city[city_1].next_node = child_node;
	}
	else
	{
		tmp_node = city[city_1].next_node;
		while(tmp_node && tmp_node->next_node)
		{
			tmp_node = tmp_node->next_node;
		}
		tmp_node->next_node = child_node;
	}
	city[city_1].child_number ++;

	return 1;
}

int dfs(int last_node,int next_node)
{
	int tmp_len = 0, max_len = 0;
      NODE * tmp_node = NULL;
      //cout << "last_node = " << last_node << ", next_node = " << next_node << endl;

      for(tmp_node = city[next_node].next_node; tmp_node != NULL; tmp_node = tmp_node->next_node)     //遍历节点
      {
            if(tmp_node -> city_info.city_number == last_node)                                        //跳过来路的节点
            {
                  continue;
            }

            if(city[tmp_node -> city_info.city_number].child_number == 1)                             //到叶子节点则返回
            {
                  return tmp_node -> city_info.len;
            }
            else
            {
                  tmp_len = tmp_node -> city_info.len + dfs(next_node, tmp_node -> city_info.city_number);  //其他情况则继续向下
                  if(tmp_len > max_len)                                                                     //取最长子路径的值
                        max_len = tmp_len;
            }
      }

	return max_len;
}

int get_cost(int len)
{
      int tmp = 0;
      do
      {
            tmp += len+10;
      }
      while (--len);

      return tmp;
}

int main()
{
	int city_num,city_1,city_2,len,tmp_len;
	NODE *tmp_node = NULL;

	cin >> city_num;
	for(int i = 0; i < city_num-1; i++)
	{
		cin >> city_1 >> city_2 >> len;
		city_1--;city_2--;				//从0开始

		if(city_1 > MAX_NUMBER_OF_CITY || \
		   city_2 > MAX_NUMBER_OF_CITY || \
		   len > MAX_LINGTH_OF_PATH)
		{
			//cout << "Input Error:[" << i << ']' << city_1 << city_2 << len << endl;
			return -1;
		}

		if(!add_node(city_1,city_2,len))
		{
			//cout << "Add " << city_1 << '.' << city_2 << ' ' << "Error" << endl;
			return -1;
		}

		if(!add_node(city_2,city_1,len))
		{
			//cout << "Add " << city_2 << '.' << city_1 << ' ' << "Error" << endl;
			return -1;
		}

	}

#if 0                                     //打印数据储存结构
	for(int i = 0; i < city_num; i++)
	{
		cout << '[' << i << "]:";
		if(!city[i].next_node)
		{
			cout << endl;
			continue;
		}
		tmp_node = city[i].next_node;
		while(tmp_node)
		{
			cout << tmp_node->city_info.city_number << '.' << tmp_node->city_info.len << ',';
			tmp_node = tmp_node->next_node;
		}
		cout << endl;
	}
#endif

#if 1                                     //深度遍历求最长路径
	for(int i = 0; i < city_num; i++)
	{
		if(city[i].child_number == 1)
		{
			tmp_len = dfs(-1,i);
			//cout << '[' << i << "]:" << tmp_len << endl;
			if(tmp_len > max_len)
				max_len = tmp_len;
		}
	}
#endif

	//cout << "max_length: " << max_len << endl;
      cout << get_cost(max_len) << endl;

	return 0;
}

