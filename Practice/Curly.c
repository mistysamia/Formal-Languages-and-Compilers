#include <stdio.h>
#include <string.h>

char str[1000], input[1000];
struct symbolTable {
  char no[1000], var[1000], type[1000];
};

struct paranthesis {
  int no, open, close;
};
struct paranthesis CurlyStore[3000], parStore[3000], thirdBrac[3000],
    ifElse[3000];

void curlyCheck(int last, int lineStart, int x) {
  int n = last, i = lineStart;
  while (i <= n) {
    if (CurlyStore[i].open > 0 && CurlyStore[n].close > 0) {
      CurlyStore[i].open--;
      CurlyStore[n].close--;
    }
    if (CurlyStore[i].open <= 0)
      i++;
    if (CurlyStore[n].close <= 0)
      n--;
  }
}

void parCheck(int last, int lineStart, int x) {
  int n = last, i = lineStart;
  while (i <= n) {
    if (parStore[i].open > 0 && parStore[i].close > 0) {
      parStore[i].open--;
      parStore[i].close--;
    }
    if (parStore[i].open <= 0)
      i++;
    if (parStore[i].close <= 0)
      i++;
  }
}

int main() {

  FILE *p1, *p2;
  char c;

  int flag = 0, sum = 0, line = 1, i = 0, indx = 0, lineStart = 1, ifCount = 0;

  // File Reading Start
  p1 = fopen("curlyInput.c", "r");
  while ((c = fgetc(p1)) != EOF) {
    str[indx++] = c;
  }
  str[indx++] = '\0';
  fclose(p1);
  // File Reading End
  int n = strlen(str);
  CurlyStore[line].open = 0, CurlyStore[line].open = 0;
  while (i < n) {

    if (str[i] == 'r' && str[i + 1] == 'e' && str[i + 2] == 't' &&
        str[i + 3] == 'u' && str[i + 4] == 'r' && str[i + 5] == 'n' &&
        i + 5 < n) {

      if (flag) {

        flag = 0;
        while (str[i] != '\n' && i < n) {
          if (str[i] == '{') {
            CurlyStore[line].open++;
          }
          if (str[i] == '}') {
            CurlyStore[line].close++;
          }

          if (str[i] == '(') {
            parStore[line].open++;
          }
          if (str[i] == ')') {
            parStore[line].close++;
          }

          i++;
        }
        curlyCheck(line, lineStart, 1);
        parCheck(line, lineStart, 1);
        lineStart = line + 1;
      }
    }

    if (((str[i] == 'd' && str[i + 1] == 'o' && str[i + 2] == 'u' &&
          str[i + 3] == 'b' && str[i + 4] == 'l' && str[i + 5] == 'e' &&
          i + 5 < n) ||
         (str[i] == 'i' && str[i + 1] == 'n' && str[i + 2] == 't' &&
          i + 2 < n)) &&
        !flag) {
      if (line > 1)
        curlyCheck(line - 1, lineStart, 2);
      else {
        curlyCheck(line, lineStart, 2);
      }
      ifCount = 0;
      if (line > 1)
        parCheck(line - 1, lineStart, 2);
      else {
        parCheck(line, lineStart, 2);
      }

      while (1) {
        if (str[i] == '(')
          parStore[line].open++;
        if (str[i] == ')') {
          flag = 1;
          break;
        }
        i++;
        if (i >= n)
          break;
      }
      lineStart = line;
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

    if (str[i] == '{') {
      CurlyStore[line].open++;
    }
    if (str[i] == '}') {
      CurlyStore[line].close++;
    }

    if (str[i] == '(') {
      parStore[line].open++;
    }
    if (str[i] == ')') {
      parStore[line].close++;
    }
    if (str[i] == '/' && str[i + 1] == '/' && i + 1 < n) {
      while (str[i] != '\n') {
        i++;
      }
    }

    if (str[i] == '/' && str[i + 1] == '*' && i + 1 < n) {
      while (1) {
        if (str[i] == '\n') {
          line++;
          CurlyStore[line].open = 0, CurlyStore[line].close = 0;
          parStore[line].open = 0, parStore[line].close = 0;
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
      CurlyStore[line].open = 0, CurlyStore[line].close = 0;
      parStore[line].open = 0, parStore[line].close = 0;
    }
    i++;
  }

  for (int i = 1; i <= line; i++) {
    /* if (CurlyStore[i].open || CurlyStore[i].close)
       printf("Mismatched Curly Braces at Line : %d\n", i);

     if (parStore[i].open || parStore[i].close)
       printf("Mismatched Parenthesis Braces at Line : %d\n", i);*/

    printf("%d %d %d\n", i, ifElse[i].open, ifElse[i].close);
  }
}