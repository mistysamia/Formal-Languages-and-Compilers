#include <stdio.h>
#include <string.h>

char str[1000], input[1000];
struct symbolTable {
  char no[1000], var[1000], type[1000];
};

struct paranthesis {
  int no, open, close;
};
struct paranthesis ifElse[3000];

int main() {

  FILE *p1, *p2;
  char c;

  int flag = 0, sum = 0, line = 1, i = 0, indx = 0, lineStart = 1, ifCount = 0;

  // File Reading Start
  p1 = fopen("elseInput.c", "r");
  while ((c = fgetc(p1)) != EOF) {
    str[indx++] = c;
  }
  str[indx++] = '\0';
  fclose(p1);
  // File Reading End
  int n = strlen(str);

  while (i < n) {

    // return
    if (str[i] == 'r' && str[i + 1] == 'e' && str[i + 2] == 't' &&
        str[i + 3] == 'u' && str[i + 4] == 'r' && str[i + 5] == 'n' &&
        i + 5 < n) {
      if (flag) {
        flag = 0;
        while (str[i] != '\n' && i < n) {
          i++;
        }
      }
    }

    // header file
    if (str[i] == '#' && str[i + 1] == 'i' && str[i + 2] == 'n' &&
        str[i + 3] == 'c' && str[i + 4] == 'l' && str[i + 5] == 'u' &&
        str[i + 6] == 'd' && str[i + 7] == 'e' && i + 7 < n) {
      while (str[i] != '\n')
        i++;
    }

    // printf
    if (str[i] == 'p' && str[i + 1] == 'r' && str[i + 2] == 'i' &&
        str[i + 3] == 'n' && str[i + 4] == 't' && str[i + 5] == 'f' &&
        i + 5 < n) {
      while (str[i] != ';' && str[i] != ')' && i < n)
        i++;
    }

    // scanf
    if (str[i] == 's' && str[i + 1] == 'c' && str[i + 2] == 'a' &&
        str[i + 3] == 'n' && str[i + 4] == 'f' && i + 4 < n) {
      while (str[i] != ';' && str[i] != ')' && i < n)
        i++;
    }

    // Starting a function
    if (((str[i] == 'd' && str[i + 1] == 'o' && str[i + 2] == 'u' &&
          str[i + 3] == 'b' && str[i + 4] == 'l' && str[i + 5] == 'e' &&
          i + 5 < n) ||
         (str[i] == 'i' && str[i + 1] == 'n' && str[i + 2] == 't' &&
          i + 2 < n) ||
         (str[i] == 'v' && str[i + 1] == 'o' && str[i + 2] == 'i' &&
          str[i + 3] == 'd' && i + 3 < n)) &&
        !flag) {
      ifCount = 0;
      while (1) {
        if (str[i] == ')') {
          flag = 1;
          break;
        }
        i++;
        if (i >= n)
          break;
      }
    }

    if (str[i] == 'i' && str[i + 1] == 'f' && i + 1 < n) {
      ifCount = 1;
      i++;
    }

    if (str[i] == 'e' && str[i + 1] == 'l' && str[i + 2] == 's' &&
        str[i + 3] == 'e' && str[i + 4] == ' ' && str[i + 5] == 'i' &&
        str[i + 6] == 'f' && i + 6 < n) {
      if (!ifCount)
        ifElse[line].open++;
      i += 6;
    }

    if (str[i] == 'e' && str[i + 1] == 'l' && str[i + 2] == 's' &&
        str[i + 3] == 'e' && i + 3 < n) {
      if (!ifCount)
        ifElse[line].close++;
      ifCount = 0;
      i += 3;
    }

    if (str[i] == '/' && str[i + 1] == '/' && i + 1 < n) {
      while (str[i] != '\n' && i < n) {
        i++;
      }
    }

    if (str[i] == '/' && str[i + 1] == '*' && i + 1 < n) {
      while (i < n) {
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

    if (str[i] == '\n') {
      line++;
    }
    i++;
  }

  for (int i = 1; i <= line; i++) {
    // printf("%d %d %d\n", i, ifElse[i].open, ifElse[i].close);
    if (ifElse[i].close)
      printf("Unmatched else at Line No : %d \n", i);
  }
}