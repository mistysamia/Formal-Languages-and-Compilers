#include <math.h>
#include <stdio.h>
#include <string.h>


int main()
{
    char ch[1000];

    gets(ch);
    int flag1 =0,flag2=0,flag3=0,flag4=0;
    int i=0;
    if(ch[0]>='a' && 'z'>=ch[0])
    {
        i++;
    }
    else
    {
        printf("String rejected\n");
        return 0;
    }
    if(ch[i]=='_')
    {
        i++;
        int one=0;
        for(; i<strlen(ch); i++)
        {
            if(ch[i]>='0' && ch[i]<='9')
            {
                one++;
            }
            else
            {
                printf("String rejected\n");
                return 0;
            }
        }
        if(one==0)
        {
            printf("String rejected\n");
            return 0;
        }
        else
        {
            printf("String Accepted\n");
            return 0;
        }
    }
    else if(ch[i]>='0' && ch[i]<='9')
    {
        int under=0;
        while(1)
        {
            if(ch[i]>='0' && ch[i]<='9')
            {
                i++;
            }
            else if(ch[i]=='_')
            {
                i++;
                under=1;
                break;
            }
            else
            {
                printf("String rejected\n");
                return 0;
            }
        }
        if(under)
        {
            int one=0;
            for(; i<strlen(ch); i++)
            {
                if(ch[i]>='0' && ch[i]<='9')
                {
                    one++;
                }
                else
                {
                    printf("String rejected\n");
                    return 0;
                }
            }
            if(one==0)
            {
                printf("String rejected\n");
                return 0;
            }
            else
            {
                printf("String Accepted\n");
                return 0;
            }
        }
        else
        {
            printf("String rejected\n");
            return 0;
        }

    }
    else
    {
        printf("String rejected\n");
        return 0;
    }

}


