#include <stdio.h>
#include <string.h>

char input[3000];
int index = 0;

int Factor();
int NumID();
int Term();
int Exp();
int stat();
int expn();
int relop();
int extn();
int extn1();
int asgn_stat();
int dscn_stat();
int loop_stat();

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

int expn()
{
    if (Exp())
    {
        if (extn())
            return 1;

        return 0;
    }
    return 0;
}

int relop()
{
    if (((input[index] == '=' && input[index + 1] == '=') ||
         (input[index] == '!' && input[index + 1] == '=') ||
         (input[index] == '<' && input[index + 1] == '=') ||
         (input[index] == '>' && input[index + 1] == '=')) &&
        index + 1 < strlen(input))
    {
        index += 2;
        return 1;
    }

    if ((input[index] == '>' || input[index] == '<') && index < strlen(input))
    {
        index++;
        return 1;
    }

    return 0;
}

int extn()
{
    int tempIndex = index;
    if (relop())
    {
        if (Exp())
            return 1;

        return 0;
    }

    index = tempIndex;
    return 1;
}

int extn1()
{
    int tempIndex = index;

    if ((input[index] == 'e' && input[index + 1] == 'l' && input[index + 2] == 's' && input[index + 3] == 'e') && index + 3 < strlen(input))
    {
        index += 4;
        if (stat())
            return 1;

        return 0;
    }

    index = tempIndex;
    return 1;
}

int asgn_stat()
{
    if (NumID())
    {
        if ( input[index] == '=' && index< strlen(input))
        {
            index ++;
            if (expn())
                return 1;

            return 0;
        }
        return 0;
    }
    return 0;
}
int dscn_stat()
{
    if ((input[index] == 'i' && input[index + 1] == 'f' && input[index + 2] == '(') && index + 2 < strlen(input))
    {
        index += 3;
        if (expn())
        {
            if (input[index] == ')' && index < strlen(input))
            {
                index++;
                if (stat())
                {
                    if (extn1())
                        return 1;

                    return 0;
                }
                return 0;
            }
            return 0;
        }

        return 0;
    }
    return 0;
}

int loop_stat()
{
    int tempIndex = index;
    if ((input[index] == 'w' && input[index + 1] == 'h' && input[index + 2] == 'i' && input[index + 3] == 'l' && input[index + 4] == 'e' && input[index + 5] == '(') && index + 5 < strlen(input))
    {
        index += 6;
        if (expn())
        {
            if (input[index] == ')' && index < strlen(input))
            {
                index++;
                if (stat())
                    return 1;

                return 0;
            }
            return 0;
        }
        return 0;
    }

    index = tempIndex;
    if ((input[index] == 'f' && input[index + 1] == 'o' && input[index + 2] == 'r' && input[index + 3] == '(') && index + 3 < strlen(input))
    {
        index += 4;
        if (asgn_stat())
        {
            if (input[index] == ';' && index < strlen(input))
            {
                index++;
                if (expn())
                {
                    if (input[index] == ';' && index < strlen(input))
                    {
                        index++;
                        if (asgn_stat())
                        {
                            if (input[index] == ')' && index < strlen(input))
                            {
                                index++;
                                if (stat())
                                    return 1;

                                return 0;
                            }
                            return 0;
                        }
                        return 0;
                    }
                    return 0;
                }
                return 0;
            }
            return 0;
        }
        return 0;
    }

    return 0;
}

int stat()
{
    int tempIndex = index;

    if (asgn_stat())
        return 1;

    index = tempIndex;
 
    if (dscn_stat())
        return 1;
    index = tempIndex;
    if (loop_stat())
        return 1;

    return 0;
}

int main()
{
    while (1)
    {
        index = 0;
        printf("Enter the string : ");
        gets(input);

        if (stat() && index == strlen(input))
            printf("String Accepted\n");
        else
            printf("String Rejected\n");
    }
}