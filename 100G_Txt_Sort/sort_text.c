/*
*  使用了 200M 的文件，内存限制在 4M， 模拟100G文件的排序
*  约在50s左右
*  Coder：yirong.wang
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORG_FILE_NAME "100G.txt"
#define OUT_FILE_NAME "100G_Sorted.txt"
#define TMP_FILE_NAME_PRE "tmp_%c_%d.txt"
#define FILE_NAME_LEN 128
#define MEM_SIZE (4 * 1024 * 1024)
#define TXT_LINE_LEN 1024
#define MAX_LINE (MEM_SIZE/TXT_LINE_LEN)
#define CMD_MAX_LEN 256

int main(void)
{
      int i,j;
      FILE *fd_org = NULL;
      FILE *fd_a = NULL, *fd_b = NULL, *fd_o = NULL;
      char **tmp_buf = NULL;
      char file_sort_count = 'a', upper = 'o';
      int read_len, count_tmp = 0, count_file = 0, all_tmp_file = 0;
      int sub_sort[MAX_LINE] = {0},tmp_t = 0;
      char mv_cmd[CMD_MAX_LEN] = {0}, rm_cmd[CMD_MAX_LEN] = {0};
      char tmp_buf_a[TXT_LINE_LEN] = {0}, tmp_buf_b[TXT_LINE_LEN] = {0};
      char file_name_o[FILE_NAME_LEN] = {0},file_name_a[FILE_NAME_LEN] = {0},file_name_b[FILE_NAME_LEN] = {0};

      tmp_buf = (char**)malloc(sizeof(char*) * MAX_LINE);         //申请内存
      for(i = 0; i < MAX_LINE; i++)
      {
            tmp_buf[i] = (char*)malloc(sizeof(char) * TXT_LINE_LEN);
      }

      fd_org = fopen(ORG_FILE_NAME, "r");
      if(!fd_org)
      {
            printf("Create File Failed, %s\n", ORG_FILE_NAME);
            return 0;
      }
      printf("file_org Open Success\n");

      do
      {
            if(!fgets(tmp_buf[count_tmp], TXT_LINE_LEN, fd_org))
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
                  snprintf(file_name_o, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count, count_file);   //创建文件名，open
                  printf("File Write > %s\n", file_name_o);
                  fd_o = fopen(file_name_o, "w");
                  if(!fd_o)
                  {
                        printf("Create File Failed, %s\n", file_name_o);
                        return 0;
                  }
                  for(i = 0; i < MAX_LINE; i++)       //写文件
                  {
                        if(strlen(tmp_buf[sub_sort[i]]) == 1 && tmp_buf[sub_sort[i]][0] == '\n')
                              continue;
                        fwrite(tmp_buf[sub_sort[i]], 1, strlen(tmp_buf[sub_sort[i]]), fd_o);
                        //fwrite(tmp_buf[i], 1, strlen(tmp_buf[i]), fd_o);
                  }
                  count_file ++;
                  fclose(fd_o);
                  count_tmp = 0;
            }
      }while(!feof(fd_org));
      if(count_tmp != 0)
      {
                  #if 1
                  for(i = 0; i < count_tmp; i++)       //插入排序，排下标
                  {
                        sub_sort[i] = i;
                  }
                  for(i = 1; i < count_tmp; i++)
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

                  snprintf(file_name_o, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count, count_file);   //创建文件名，open
                  printf("File Write > %s\n", file_name_o);
                  fd_o = fopen(file_name_o, "w");
                  if(!fd_o)
                  {
                        printf("Create File Failed, %s\n", file_name_o);
                        return 0;
                  }

                  for(i = 0; i < count_tmp; i++)       //写文件
                  {
                        if(strlen(tmp_buf[sub_sort[i]]) == 1 && tmp_buf[sub_sort[i]][0] == '\n')
                              continue;
                        fwrite(tmp_buf[sub_sort[i]], 1, strlen(tmp_buf[sub_sort[i]]), fd_o);
                        //fwrite(tmp_buf[i], 1, strlen(tmp_buf[i]), fd_o);
                  }

                  count_file ++;
                  fclose(fd_o);
                  count_tmp = 0;
      }
      fclose(fd_org);               //关闭源文件

      all_tmp_file = count_file;    //文件合并
      while(all_tmp_file > 1)
      {
            count_file = 0;
            file_sort_count++;
            for(i = 0; i < all_tmp_file-1; i+=2)
            {
                  snprintf(file_name_a, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count-1, i);       //合并输入
                  fd_a = fopen(file_name_a, "r");
                  if(!fd_a)
                  {
                        printf("Read File Failed, %s\n", file_name_a);
                        return 0;
                  }
                  snprintf(file_name_b, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count-1, i+1);     //合并输入
                  fd_b = fopen(file_name_b, "r");
                  if(!fd_b)
                  {
                        printf("Read File Failed, %s\n", file_name_b);
                        return 0;
                  }

                  if(all_tmp_file == 2)
                  {
                        strncpy(file_name_o, OUT_FILE_NAME, FILE_NAME_LEN);                      //最终输出
                  }
                  else
                  {
                        snprintf(file_name_o, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count, count_file); //合并输出
                  }
                  fd_o = fopen(file_name_o, "w");
                  if(!fd_o)
                  {
                        printf("Create File Failed, %s\n", file_name_o);
                        return 0;
                  }

                  do
                  {
                        if(upper != 'a')
                        {
                              if(!feof(fd_a))
                              {
                                    if(!fgets(tmp_buf_a, TXT_LINE_LEN, fd_a))
                                    {
                                          printf("Read %s File End\n", file_name_a);
                                          continue;
                                    }
                              }
                              else
                              {
                                    strncpy(tmp_buf_a, "~", 2);
                              }
                        }

                        if(upper != 'b')
                        {
                              if(!feof(fd_b))
                              {
                                    if(!fgets(tmp_buf_b, TXT_LINE_LEN, fd_b))
                                    {
                                          printf("Read %s File End\n", file_name_b);
                                          continue;
                                    }
                              }
                              else
                              {
                                    strncpy(tmp_buf_b, "~", 2);
                              }
                        }

                        if (strcmp(tmp_buf_a, tmp_buf_b) > 0)
                        {
                              upper = 'a';
                              fwrite(tmp_buf_b, 1, strlen(tmp_buf_b), fd_o);
                        }
                        else
                        {
                              upper = 'b';
                              fwrite(tmp_buf_a, 1, strlen(tmp_buf_a), fd_o);
                        }
                  }while(!feof(fd_a) || !feof(fd_b));

                  upper = 'o';
                  fclose(fd_a);
                  fclose(fd_b);
                  fclose(fd_o);
                  //delete a,b
                  count_file++;
            }
            if(all_tmp_file > 1 && all_tmp_file%2 == 1)
            {
                  snprintf(file_name_b, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count-1, i);
                  snprintf(file_name_o, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count, count_file);
                  snprintf(mv_cmd, CMD_MAX_LEN, "mv %s %s", file_name_b, file_name_o);
                  printf("CMD Run: %s\n", mv_cmd);
                  system(mv_cmd);
                  count_file++;
            }

            snprintf(rm_cmd, CMD_MAX_LEN, "rm tmp_%c_*", file_sort_count-1);
            system(rm_cmd);
            all_tmp_file = count_file;
      }

      printf("File Sort All Done\n");
      return 0;
}
