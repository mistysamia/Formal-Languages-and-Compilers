#include <stdio.h>
#include <string.h>

char str[1000], input[1000];
struct symbolTable {
  char no[1000], var[1000], type[1000];
};

int relational(int i, int n) {

  if ((str[i] == '!' && str[i + 1] == '=' && i + 1 < n) ||
      (str[i] == '>' && str[i + 1] == '=' && i + 1 < n) ||
      (str[i] == '<' && str[i + 1] == '=' && i + 1 < n) ||
      (str[i] == '=' && str[i + 1] == '=' && i + 1 < n)) {
    // printf("In %c%c\n", str[i], str[i + 1]);
    return 2;
  }

  if ((str[i] == '<') || (str[i] == '>')) {
    // printf("Isn %c%c\n", str[i], str[i + 1]);
    return 1;
  }

  return 0;
}
int main() {

  printf("Enter your code and write end to terminate : \n");

  while (1) {

    gets(input);
    if (strcmp(input, "end") == 0)
      break;
    strcat(str, input);
    strcat(str, "\n");
  }
  strcat(str, "\0");

  int n = strlen(str);
  int flag = 0, sum = 0, line = 1, i = 0;

  while (i < n) {
    flag = 0;

    if (str[i] == '#' && str[i + 1] == 'i' && str[i + 2] == 'n' &&
        str[i + 3] == 'c' && str[i + 4] == 'l' && str[i + 5] == 'u' &&
        str[i + 6] == 'd' && str[i + 7] == 'e' && i + 7 < n) {
      while (str[i] != '\n')
        i++;
    }

    if (str[i] == 'p' && str[i + 1] == 'r' && str[i + 2] == 'i' &&
        str[i + 3] == 'n' && str[i + 4] == 't' && str[i + 5] == 'f' &&
        i + 5 < n) {
      while (str[i] != ';' && str[i] != ')')
        i++;
    }

    if (str[i] == 's' && str[i + 1] == 'c' && str[i + 2] == 'a' &&
        str[i + 3] == 'n' && str[i + 4] == 'f' && i + 4 < n) {
      while (str[i] != ';' && str[i] != ')')
        i++;
    }

    if (str[i] == '/' && str[i + 1] == '/' && i + 1 < n) {
      while (1) {
        if (str[i] == '\n') {
          break;
        }
        i++;
      }
    }

    if (str[i] == '/' && str[i + 1] == '*' && i + 1 < n) {
      while (1) {
        if (str[i] == '\n') {
          line++;
        }
        if (str[i] == '*' && str[i + 1] == '/' && i + 1 < n) {
          i += 2;
          break;
        }
        i++;
      }
    }

    flag = relational(i, n);
    if (flag == 2) {
      flag = 1;
      i++;
    }

    if (flag)
      sum++;
    if (str[i] == '\n') {
      if (sum != 0)
        printf("Line No. %d : %d\n", line, sum);
      line++;
      sum = 0;
    }
    i++;
  }
}