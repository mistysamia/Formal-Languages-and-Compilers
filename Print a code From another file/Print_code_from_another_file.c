#include <stdio.h>
#include <math.h>
#include <string.h>

int main()
{

    FILE *p1, *p2;
    char c;

    int flag = 0, hash = 0;
    p1 = fopen("file.c", "r");
    p2 = fopen("header.txt", "w");

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
    printf("%d: ", i);
    while ((c = fgetc(p2)) != EOF)
    {
        printf("%c", c);
        if (c == '\n')
        {
             printf("%d: ", i++);
        }
    }

    fclose(p2);

    return 0;
}