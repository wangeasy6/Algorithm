/*
*  对于1G 的文件，这里的内存应该限制在 20M 以下
*/
#include <stdio.h>
#include <string.h>

#define ORG_FILE_NAME "1G.txt"
#define TMP_FILE_NAME_PRE "tmp_%d.txt"
#define FILE_NAME_LEN 128
#define MEM_SIZE (4 * 1024 * 1024)
#define TXT_LINE_LEN 1024
#define MAX_LINE (MEM_SIZE/TXT_LINE_LEN)

int main(void)
{
      int i,j;
      int read_len, count_tmp = 0, count_file = 0;
      FILE *fd_org = NULL,*fd_output = NULL;
      char tmp_buf[MAX_LINE][TXT_LINE_LEN] = {0};
      char name_t[FILE_NAME_LEN] = {0};
      int sub_sort[MAX_LINE] = {0},tmp_t = 0;

      fd_org = fopen(ORG_FILE_NAME, "r");
      if(!fd_org)
      {
            printf("Create File Failed, %s\n", ORG_FILE_NAME);
            return 0;
      }
      printf("file_org Open Success\n");

      do
      {
            if(!fgets(tmp_buf[count_tmp], TXT_LINE_LEN, fd_org))     //结束不整除处理
            {
                  printf("Read Org File Out\n");
                  break;
            }

            count_tmp ++;
            if(count_tmp == MAX_LINE)                 //可用内存达到上限，内部排序
            {
                  #if 1
                  for(i = 0; i < MAX_LINE; i++)       //插入排序，排下标
                  {
                        sub_sort[i] = i;
                  }
                  for(i = 1; i < MAX_LINE; i++)
                  {
                        if(strlen(tmp_buf[i]) == 0)
                              continue;
                        tmp_t = sub_sort[i];
                        for(j = i-1; j >= 0; j--)
                        {
                              if (strcmp(tmp_buf[sub_sort[j]], tmp_buf[tmp_t]) > 0)  //后面如果更小，交换
                              {
                                  sub_sort[j+1] = sub_sort[j];
                              }
                              else
                                  break;
                        }
                        sub_sort[j+1] = i;
                  }
                  #endif

                  snprintf(name_t, FILE_NAME_LEN, TMP_FILE_NAME_PRE, count_file);   //创建文件名，open
                  printf("File Write > %s\n", name_t);
                  fd_output = fopen(name_t, "w");
                  if(!fd_output)
                  {
                        printf("Create File Failed, %s\n", name_t);
                        return 0;
                  }

                  for(i = 0; i < MAX_LINE; i++)       //写文件
                  {
                        if(strlen(tmp_buf[sub_sort[i]]) == 1 && tmp_buf[sub_sort[i]][0] == '\n')
                              continue;
                        fwrite(tmp_buf[sub_sort[i]], 1, strlen(tmp_buf[sub_sort[i]]), fd_output);
                        //fwrite(tmp_buf[i], 1, strlen(tmp_buf[i]), fd_output);
                  }

                  count_file ++;
                  fclose(fd_output);
                  memset(tmp_buf, 0, MEM_SIZE);
                  count_tmp = 0;
                  break;
            }
      }while(!feof(fd_org));

      fclose(fd_org);
      return 0;
}
