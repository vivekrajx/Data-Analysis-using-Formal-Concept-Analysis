#include<stdio.h>
#include<stdlib.h>

int main()
{

    int G=50;
    int M=39;

      FILE* fp;
      errno_t err;
      err = fopen_s(&fp, "C:\\Users\\Avik\\Desktop\\ScalingDatasetMod.txt", "r");
      char c;
      char attribute[40][30];
      int attribute_flag = 1, space_count = 0, attribute_number = 0, attribute_size = 0;
      int object_flag = 1,object[51][60],object_number=0,object_size=0;
      int row = 0, column = 0, Context[50][39];
      while ((c = fgetc(fp)) != EOF)
      {
          if (attribute_flag)
          {
              if (c == '\n')
              {
                  attribute_flag = 0;
                  continue;
              }
              if (c == ' ')
              {
              	if(attribute_size==0)
              	continue;
                  space_count++;
              }
               if (space_count >5 || attribute_size>28)
                {
                    attribute[attribute_number][attribute_size] = '\0';
                    space_count = 0;
                    attribute_number++;
                    attribute_size = 0;
                    continue;
                }
                attribute[attribute_number][attribute_size] = c;
                attribute_size++;
                
          }
          else
          {
              if (c == '\n')
              {
                  object_flag = 1;
                  continue;
              }
              if (object_flag && (c == '0' || c == '1'))
              {
                  object_flag = 0;
                  object[object_number][object_size] = '\0';
                  object_number++;
                  object_size = 0;
              }
              if (object_flag)
              {
                  object[object_number][object_size] = c;
                  object_size++;
              }
              else
              {
                  if (c == '1' || c == '0')
                  {
                      Context[row][column] = c - 48;
                      column++;
                      if (column == 39)
                      {
                          row++;
                          column = 0;
                      }
                  }
              }

          }

      }
}
