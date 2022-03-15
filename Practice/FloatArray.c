#include <stdio.h>
#include <string.h>

char str[1000], input[1000];

int main() {

  FILE *p1, *p2;
  char c;

  int flag = 0, sum = 0, line = 1, i = 0, indx = 0;

  // File Reading Start
  p1 = fopen("inputFile.c", "r");
  while ((c = fgetc(p1)) != EOF) {
    str[indx++] = c;
  }
  str[indx++] = '\0';
  fclose(p1);
  // File Reading End

  int n = strlen(str);

  while (i < n) {

    if (str[i] == 'f' && str[i + 1] == 'l' && str[i + 2] == 'o' &&
        str[i + 3] == 'a' && str[i + 4] == 't' && i + 4 < n) {

      while (str[i] != ';') {
        if (str[i] == '[')
          sum++;

        i++;
      }
    }
    i++;
  }

  printf("No. of Float arrays declared : %d\n", sum);
}