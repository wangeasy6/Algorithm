/*
 *  生成 100G 文本，用于测试
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_NAME "100G.txt"
#define FILE_SIZE (200*1024*1024)
#define TXT_LINE_LEN 1024

int main()
{
      FILE *fd = NULL;
      char str[TXT_LINE_LEN] = {0};
      int file_size = 0, line = 0;
      int i = 0, str_len = 0,t = 0;

      fd = fopen(FILE_NAME, "w");
      if(!fd)
      {
            printf("Create File Failed\n");
            return 0;
      }

      srand(time(0));
      do
      {
            str_len = rand()%(TXT_LINE_LEN-1);
            if(!str_len)
                  continue;
            for (i=0;i < str_len; i++)
            {
                  t = rand()%62;
                  if(t < 10)
                  {
                        str[i] = t + 48;
                  }
                  else if (t < 36)
                  {
                        str[i] = t + (65-10);
                  }
                  else
                  {
                        str[i] = t + (97 - 36);
                  }
            }
            str[i] = '\n';

            fwrite(str, 1, str_len+1, fd);
            file_size += (str_len+2);                 //Windows 下面 \n 自动占两个字符
            line ++;
      }
      while( file_size < FILE_SIZE);

      printf("Creat Done: File_Name:%s, File_Size:%d, Line:%d\n", FILE_NAME, file_size, line);
      fclose(fd);
      return 0;
}
