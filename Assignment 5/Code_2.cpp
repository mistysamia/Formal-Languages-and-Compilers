#include <stdio.h>
#include <string.h>

char input[3000];
int index = 0;

int Factor();
int NumID();
int Term();
int Exp();

int NumID()
{
    if ((input[index] >= '0' && input[index] <= '9') && index < strlen(input))
    {
        index++;
        return 1;
    }

    if ((input[index] >= 'a' && input[index] <= 'e') && index < strlen(input))
    {
        index++;
        return 1;
    }

    return 0;
}

int Factor()
{
    if (NumID())
        return 1;
 
    if (input[index] == '(' && index < strlen(input))
    {
        index++;
        if (Exp())
        {
            if (input[index] == ')' && index < strlen(input))
            {
                index++;
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

int Term()
{
    if (Factor())
    {
        if ((input[index] == '*' || input[index] == '/') && index < strlen(input))
        {
            index++;
            if (Factor())
                return 1;

            return 0;
        }
        return 1;
    }
    return 0;
}

int Exp()
{
    if (Term())
    {
        if ((input[index] == '+' || input[index] == '-') && index < strlen(input))
        {
            index++;
            if (Term())
                return 1;

            return 0;
        }
        return 1;
    }
    return 0;
}

int main()
{
    printf("Enter the string : ");
    gets(input);

    if (Exp() && index==strlen(input))
    {
        printf("Yes\n", index, strlen(input));
    }
    else
    {
        printf("No\n");
    }
}
