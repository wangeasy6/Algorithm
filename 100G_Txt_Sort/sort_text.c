/*
*  使用了 200M 的文件，内存限制在 4M， 模拟100G文件的排序
*  约在20s左右
*  Coder：yirong.wang
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME_LEN 256                       //文件名最大长度
#define CMD_MAX_LEN  256                        //System 命令最大长度
#define ORG_FILE_NAME "100G.txt"                //原文件名
#define OUT_FILE_NAME "100G_Sorted.txt"         //输出文件名
#define TMP_FILE_NAME_PRE "tmp_%d_%d.txt"       //临时文件名
#define MEM_SIZE (4 * 1024 * 1024)              //使用内存 4M
#define TXT_LINE_LEN 1024                       //每一行文本长度
#define MAX_LINE (MEM_SIZE/TXT_LINE_LEN)        //内存/文本长度 = 行数
#define MULT_MIX_N 6                            //多路合并数

int main(void)
{
      int i,j;
      FILE *fd_org = NULL;
      FILE *fd_i[MULT_MIX_N], *fd_o = NULL;
      char **tmp_buf = NULL;
      int file_sort_count = 0, min = -1;
      int read_len, count_tmp = 0, count_file = 0, count_file_end = 0, all_tmp_file = 0;
      int sub_sort[MAX_LINE] = {0},tmp_t = 0;
      char mv_cmd[CMD_MAX_LEN] = {0}, rm_cmd[CMD_MAX_LEN] = {0};
      char file_name_o[FILE_NAME_LEN] = {0},file_name_i[MULT_MIX_N][FILE_NAME_LEN] = {0};

      tmp_buf = (char**)malloc(sizeof(char*) * MAX_LINE);         //申请内存
      for(i = 0; i < MAX_LINE; i++)
      {
            tmp_buf[i] = (char*)malloc(sizeof(char) * TXT_LINE_LEN);
      }

      fd_org = fopen(ORG_FILE_NAME, "r");
      if(!fd_org)
      {
            printf("Open File Failed, %s\n", ORG_FILE_NAME);
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
            for(i = 0; i < (all_tmp_file-1); i+=MULT_MIX_N)
            {
                  count_file_end = (all_tmp_file - i)>MULT_MIX_N?MULT_MIX_N:(all_tmp_file - i);
                  //printf("[Easy-W] %d %d %d\n", all_tmp_file, i, count_file_end);
                  for(j = 0; j < count_file_end; j++)
                  {
                        snprintf(file_name_i[j], FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count-1, i+j);       //合并输入
                        fd_i[j] = fopen(file_name_i[j], "r");
                        if(!fd_i[j])
                        {
                              printf("Read File Failed, %s\n", file_name_i[j]);
                              return 0;
                        }
                        else
                        {
                              printf("Read File %s\n", file_name_i[j]);
                        }
                  }

                  if(all_tmp_file <= MULT_MIX_N)
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
                  else
                  {
                        printf("Create File %s\n",file_name_o);
                  }

                  do
                  {
                        for(j = 0; j < ((all_tmp_file - i)>MULT_MIX_N?MULT_MIX_N:(all_tmp_file - i)); j++)
                        {
                              if(min == -1 || min == j)
                              {
                                    if(!fgets(tmp_buf[j], TXT_LINE_LEN, fd_i[j]))
                                    {
                                          count_file_end--;
                                          strncpy(tmp_buf[j], "~", 2);
                                          printf("Read %s File End,Last:%d\n", file_name_i[j],count_file_end);
                                          continue;
                                    }
                              }
                        }
                        if (!count_file_end)
                              break;

                        for(min = 0,j = 1; j < ((all_tmp_file - i)>MULT_MIX_N?MULT_MIX_N:(all_tmp_file - i)); j++)
                        {
                              min = (strcmp(tmp_buf[min], tmp_buf[j])>0)?j:min;
                        }
                        fwrite(tmp_buf[min], 1, strlen(tmp_buf[min]), fd_o);
                  }while(1);

                  min = -1;
                  for(j = 0; j < MULT_MIX_N; j++)
                  {
                        if(fd_i[j])
                              fclose(fd_i[j]);
                  }
                  fclose(fd_o);
                  count_file++;
            }

            if(all_tmp_file > 1 && all_tmp_file%MULT_MIX_N == 1)
            {
                  snprintf(file_name_i[0], FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count-1, i);
                  snprintf(file_name_o, FILE_NAME_LEN, TMP_FILE_NAME_PRE, file_sort_count, count_file);
                  snprintf(mv_cmd, CMD_MAX_LEN, "rename %s %s", file_name_i[0], file_name_o);         //Winidows下的命令是 rename；Linux 下的命令是 mv
                  printf("CMD Run: %s\n", mv_cmd);
                  system(mv_cmd);
                  count_file++;
            }

            snprintf(rm_cmd, CMD_MAX_LEN, "rm tmp_%d_*", file_sort_count-1);
            printf("CMD Run: %s\n", rm_cmd);
            system(rm_cmd);
            all_tmp_file = count_file;
      }

      printf("File Sort All Done\n");
      return 0;
}
