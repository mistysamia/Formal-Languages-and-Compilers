#include <stdio.h>
#include <string.h>

char input[3000];
int index = 0;

int X()
{
    if (input[index] == 'b' && index < strlen(input))
    {
        index++;
        if ((input[index] == 'b' || input[index] == 'c') && index < strlen(input))
        {
            index++;
            if (X())
                return 1;

            return 0;
        }
        return 0;
    }
    return 1;
}
int A()
{
    if (input[index] == 'a' && index < strlen(input))
    {
        index++;
        if (X())
        {
            if (input[index] == 'd')
                return 1;
        }
        return 0;
    }
    return 0;
}

int main()
{
    printf("Enter the string : ");
    gets(input);

    if (A() && index + 1 == strlen(input))
        printf("String Accepted\n");
    else
        printf("String Rejected\n");
}
