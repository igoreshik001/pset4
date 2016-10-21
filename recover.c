#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr," Usage: ./recover image\n");
        return 1;
    }
    char* infile = argv[1];

    // open input file 
    //OPEN FILE
    FILE* file = fopen(infile, "r");
    if(file == NULL) //Перевіряємо чи відкрито файл
    {
      printf("cat: datd.txt: No such file or directory\n");
      return 1; //Якщо файл не відкрито, отже він не існує - помилка
    }
    //NAME NEW FILE
    char n[8]="000.jpg";
    int num='0';// 0 in char

    //OPEN NEW FILE
    FILE* outptr = fopen(n, "w");
    if (outptr == NULL)
    {
        printf("Could not create \n");
        return 2;
    }
    //Цикл, у якому зчитуємо символи з файлу

    int x[sizeof(char)*512]; //varieble bite

    int mark=0; //marker
    int c; //
    for (int i=0; i>=0; i++)
    {
        c=fgetc(file);
        fseek (file,-1,SEEK_CUR);
        
        if ( c==EOF )
        {
            break;
        }
        fread(x, sizeof(char)*512, 1, file);

        if (x[0]==0xe0ffd8ff || x[0]==0xe1ffd8ff)
        {
            mark++;
        }

        if ( mark != 0 )
        {
            if ( mark==1 )
            {
                fwrite(x, sizeof(char)*512, 1, outptr);
            }
            else if ( mark>1 )
            {
                fclose(outptr);
                num++;
                if ( num>'9' )
                {
                    num='0';
                    n[1]=num+1;
                    n[2]=num;
                }
                else
                {
                    n[2]=num;
                }
                outptr = fopen(n, "w");
                if (outptr == NULL)
                {
                    printf("Could not create \n");
                    return 2;
                }
                fwrite(x, sizeof(char)*512, 1, outptr);
                mark=1;
            }
        }
    }
    fclose(outptr);

    fclose(file);

  return 0;
}
