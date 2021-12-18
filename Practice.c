#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{
    FILE *p1, *p2;
    char c;

    int flag = 0, hash = 0;
    p1 = fopen("Practice.c", "r");

    char arr[100];
    if (!p1)
        printf("Can't Open");
    else
    {
        int i = 0;
        while ((c = fgetc(p1)) != EOF)
        {
            arr[i++] = c;
        }

        for (int j = 0; j < i; j++)
        {
            if (arr[j] == '#')
            {
                hash = 1;
            }
            if (hash)
            {
                if (arr[j] == '<')
                {
                    flag = 1;
                    continue;
                }
                else if (arr[j] == '>')
                {
                    flag = 0;
                    hash = 0;
                    printf("\n");
                }
                if (flag)
                    printf("%c", arr[j]);
            }
        }
    }

    fclose(p1);

    return 0;
}