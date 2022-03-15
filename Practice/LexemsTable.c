#include <stdio.h>
#include <string.h>

char str[1000], input[1000];
int inputIndx = 0;

struct symbolTable {
  char no[1000], var[1000], type[1000];
};

struct symbolTable tableStore[3000];
int tableStoreIndx = 0;

void lexems(char temp[]) {
  for (int i = 0; i < tableStoreIndx; i++) {
    if (strcmp(temp, tableStore[i].var) == 0) {
      for (int j = 0; j < strlen(tableStore[i].no); j++) {
        input[inputIndx++] = tableStore[i].no[j];
      }
      input[inputIndx++] = ']';
      return;
    }
  }
}

int main() {

  FILE *p1, *p2;
  char c;

  int flag = 0, sum = 0, line = 1, i = 0, indx = 0;

  // File Reading Start
  p1 = fopen("Symbol.txt", "r");
  while ((c = fgetc(p1)) != EOF) {
    str[indx++] = c;
  }
  str[indx++] = '\0';
  fclose(p1);
  // File Reading End
  int n = strlen(str);



  // Table Data Save
  indx = 0;
  while (i < n) {
    char temp[1000];
    int tempIn = 0;
    while (str[i] != ' ') {
      temp[tempIn++] = str[i++];
    }
    temp[tempIn++] = '\0';
    strcpy(tableStore[indx].no, temp);
    memset(temp, 0, strlen(temp));

    while (str[i] == ' ')
      i++;

    tempIn = 0;
    while (str[i] != ' ') {
      temp[tempIn++] = str[i++];
    }
    temp[tempIn++] = '\0';
    strcpy(tableStore[indx].var, temp);
    memset(temp, 0, strlen(temp));

    while (str[i] == ' ')
      i++;

    tempIn = 0;
    while (str[i] != '\n' && str[i] != '\0') {
      temp[tempIn++] = str[i++];
    }
    temp[tempIn++] = '\0';
    strcpy(tableStore[indx++].type, temp);
    memset(temp, 0, strlen(temp));
    tableStoreIndx++;
    while (str[i] == ' ' || str[i] == '\n')
      i++;
  }
  fclose(p1);


  memset(str, 0, strlen(str));
  p1 = fopen("tokens.txt", "r");
  indx = 0;
  while ((c = fgetc(p1)) != EOF) {
    str[indx++] = c;
  }
  str[indx++] = '\0';
  fclose(p1);
  // printf("In %s\n", str);
  n = strlen(str);



  for (int j = 0; j < n; j++) {
    if (str[j] == '[' && str[j + 1] == 'i' && str[j + 2] == 'd' && j + 2 < n) {
      input[inputIndx++] = '[';
      input[inputIndx++] = 'i';
      input[inputIndx++] = 'd';
      input[inputIndx++] = ' ';

      char temp[1000];
      int tempIn = 0;
      j += 4;

      while (str[j] != ']') {
        temp[tempIn++] = str[j++];
      }
      temp[tempIn++] = '\0';
      lexems(temp);

    } else {
      input[inputIndx++] = str[j];
    }
  }

  input[inputIndx++] = '\0';

  // File Writing Start
  p2 = fopen("output.txt", "w");
  fputs(input, p2);
  fclose(p2);
  // File Writing End
}