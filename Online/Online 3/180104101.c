#include <math.h>
#include <stdio.h>
#include <string.h>

struct symbolTable {
  char no[1000], var[1000], type[1000];
};

struct symbolTable tableStore[3000];
int main() {

  FILE *p1, *p2;
  char c;
  char str[1000], str1[1000], str0[1000];
  int flag = 0, hash = 0, st;
 
  printf("Insert Data : ");
  gets(str);
  gets(str0);
  printf("Insert At : ");
  gets(str1);
  puts(str1);

  p1 = fopen("inputfile.txt", "r");
  int i = 1;
  int serialNo = 1;
  flag = 0;
  char tempSave[1000];
  int tempSaveNo = 0;
  char tempValue[1000];
  char strSave[1000];
  int strSaveNo = 0;
  while ((c = fgetc(p1)) != EOF) {
    strSave[strSaveNo++] = c;
  }
  strSave[strSaveNo] = '\0';
  fclose(p1);
   memset(tempValue, 0, sizeof(tempValue));
  i=0;
  while (i < strSaveNo) {

  

    if (flag == 0) {
      while (strSave[i] != ' ') {
        tempValue[tempSaveNo++] = strSave[i++];
      }
      tempValue[tempSaveNo] = '\0';
      if (strcmp(str1, tempValue) == 0) {
        strcpy(tableStore[serialNo].no, str1);
        strcpy(tableStore[serialNo].var, str);
        strcpy(tableStore[serialNo].type, str0);
        serialNo++;
      }
      
      sprintf(tempValue, "%d", serialNo);
      strcpy(tableStore[serialNo].no, tempValue);
      flag++;
      tempSaveNo = 0;
      memset(tempValue, 0, sizeof(tempValue));
      while (strSave[i] == ' ')
        i++;
    }

  

    if (flag == 1) {
      while (strSave[i] != ' ') {
        tempValue[tempSaveNo++] = strSave[i++];
      }
      tempValue[tempSaveNo] = '\0';
      strcpy(tableStore[serialNo].var, tempValue);
      flag++;
      tempSaveNo = 0;
      memset(tempValue, 0, sizeof(tempValue));
      while (strSave[i] == ' ')
        i++;
    }

    if (flag == 2) {
      while (strSave[i] != ' ' && strSave[i] != '\n') {
        tempValue[tempSaveNo++] = strSave[i++];
      }
      tempValue[tempSaveNo] = '\0';
      strcpy(tableStore[serialNo].type, tempValue);
      flag = 0;
      tempSaveNo = 0;
      serialNo++;
      memset(tempValue, 0, sizeof(tempValue));
      while (strSave[i] == ' ' || strSave[i] == '\n')
        i++;
    }
  }
  printf("\n\n");

  for (int i = 0; i < serialNo; i++) {
    printf("%s %s %s\n", tableStore[i].no, tableStore[i].var,
           tableStore[i].type);
  }

  return 0;
}