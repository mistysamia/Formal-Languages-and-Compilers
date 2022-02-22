#include <stdio.h>
#include <math.h>
#include <string.h>

struct symbolTable
{
    char no[1000], var[1000], type[1000];
};

struct symbolTable tableStore[3000];
int main()
{

    FILE *p1, *p2;
    char c;
    char str[1000],str1[1000],str0[1000];
    int flag = 0, hash = 0,st;
    p1 = fopen("inputfile.txt", "r");
    p2 = fopen("header.txt", "w");

    printf("Insert Data : ");
    gets(str);
    gets(str0);
    printf("Insert At : ");
    gets(str1);
    puts(str1);


    if (!p1)
    {
        printf("Not run");
    }
    else
    {
        while ((c = fgetc(p1)) != EOF)
        {
            fputc(c, p2);
        }
    }
    fclose(p1);
    fclose(p2);

    p2 = fopen("header.txt", "r");

    int i = 1;




    int serialNo=1;
    flag=0;
    char tempSave[1000];
    int tempSaveNo=0;
    char tempValue[1000];
    char strSave[1000];
    int strSaveNo=0;
    while ((c = fgetc(p2)) != EOF)
    {
        strSave[strSaveNo++]=c;
    }
    fclose(p2);

    for(int i=0; i<strSaveNo; i++)
    {
        //printf("%s\n",tempValue);
        if(strSave[i]==' ' && flag==0)
        {
            tempValue[tempSaveNo]='\0';
            if( strcmp(str1,tempValue)==0)
            {

                strcpy(tableStore[serialNo].no,str);
                strcpy(tableStore[serialNo].var,str0);
                strcpy(tableStore[serialNo].type,str1);
                serialNo++;
            }

            strcpy(tableStore[serialNo].no,tempValue);
            flag++;
            tempSaveNo=0;
            memset(tempValue,0,sizeof(tempValue));
        }
        //printf("%c", c);
        if(flag==0)
        {
            tempValue[tempSaveNo]=strSave[i];
         //   printf("Innnnnnnnnnn %c\n",tempValue[tempSaveNo]);
            tempSaveNo++;


        }
        //printf("%s %d\n",tempValue,flag);
//printf("%s\n",tempValue);
        if(c==' ' && flag==1)
        {
            tempValue[tempSaveNo]='\0';
            //  printf("xxx\n");
            strcpy(tableStore[serialNo].var,tempValue);
            flag++;

            tempSaveNo=0;
            memset(tempValue,0,sizeof(tempValue));
        }
        if(flag==1)
        {

            tempValue[tempSaveNo++]=strSave[i];
            //printf("sss %c %s\n",strSave[i],tempValue);

        }
        // printf("Flag  %d\n",flag);

        if((strSave[i]==' '|| strSave[i]=='\n') && flag==2)
        {
            tempValue[tempSaveNo]='\0';
            //   printf("Flag1  %d\n",flag);
            //   printf("xxx\n");
            strcpy(tableStore[serialNo].type,tempValue);
//printf("sss %s %s\n",tableStore[serialNo].type,tempValue);
            flag=0;
            tempSaveNo=0;
            serialNo++;
            memset(tempValue,0, sizeof(tempValue));

        }

        if(flag==2)
        {
            //printf("Flag2  %d\n",flag);
            tempValue[tempSaveNo++]=strSave[i];

        }


    }
    printf("\n\n");

    for(int i=0; i<serialNo; i++)
    {
        printf("%s %s %s",tableStore[serialNo].no,tableStore[serialNo].var,tableStore[serialNo].type);
    }

    return 0;
}
