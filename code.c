//Course Name : CSE 4130
//Group : C1
//ID : 180104101
//Online : 1
#include <math.h>
#include <stdio.h>
#include <string.h>


int main()
{
    FILE *file;
    char str[100], save[100], printoutput[100], c;
    int in = 0, singlecomment = 0, multicomment = 0, indx = 0;
    int sum=0;
    // save to an array
    file = fopen("input.txt", "r");
    while ((c = fgetc(file)) != EOF)
        save[in++] = c;

    save[in++] = '\0';
    fclose(file);


    for(int i=1; i<in; i++)
    {

        if (save[i] == '/' && save[i + 1] == '/' && !multicomment && i < in - 1)
            singlecomment = 1;

        if (save[i] == '\n' && singlecomment)
        {
            singlecomment = 0;
            continue;
        }
        if (save[i + 1] == '*' && save[i] == '/' && i < in - 1 && !multicomment &&
                !singlecomment)
            multicomment = 1;

        if (multicomment == 2)
        {
            multicomment = 0;
            continue;
        }

        if (save[i + 1] == '/' && save[i] == '*' && i < in - 1 && multicomment)
        {
            multicomment = 2;
            continue;
        }

        if (!multicomment && !singlecomment && save[i] != '\n')
        {

            if(save[i]=='d' && save[i-1]=='%')
            {
                sum++;
            }

        }

    }

    printf("No. of Integer : %d",sum);

    return 0;
}
