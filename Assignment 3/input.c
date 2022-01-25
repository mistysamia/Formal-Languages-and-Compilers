#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file, *file1;
char str[3000], save[3000], printoutput[3000], finalOutput[3000], c,
    saveoutput[3000], separateIdOutput[3000], operatorVariable[1000],
    symBolTable[3000];
int in = 0, singlecomment = 0, multicomment = 0, indx = 0, outputIndx = 0,
    saveOutputIndx = 0, separateIdIndx = 0;

int openCurly = 0, closeCurly = 0, serialNo = 1;

struct symbolTable {
  char no[100], name[100], id[100], data[100], scope[100], value[100],
      number[100];
};

struct symbolTable tempValue;
struct symbolTable tableStore[3000];

int updateVariable(char strInt[], char scopeName[], char updateVar[]) {

  for (int i = 0; i < serialNo; i++) {
    if (strcmp(tableStore[i].name, strInt) == 0 &&
        strcmp(tableStore[i].scope, scopeName) == 0) {
      strcpy(tableStore[i].value, updateVar);

      return 0;
    }
  }
  return -1;
}

int frontOperator(int i) {
  const char operators[40][10] = {
      "(type)", "sizeof", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||",
      "?:",     "+=",     "-=", "*=", "/=", "%=", "&=", "^=", "|=", "<<=",
      ">>=",    ".",      "->", "++", "--", "!",  "~",  "*",  "/",  "%",
      "+",      "-",      "=",  ">",  "<",  "*",  "&",  "^",  "|"};
  int equal = 0;
  for (int j = 0; j < 40; j++) {
    int length = strlen(operators[j]);

    if ((length - 1) + i < outputIndx) {
      equal = 0;
      for (int t = 0; t < length; t++) {
        if (operators[j][t] != finalOutput[i + t]) {
          equal = 1;
          break;
        }
      }
      if (!equal) {
        return -4;
      }
    }
  }
  return -5;
}

int frontSeparator(int i) {

  if (finalOutput[i] == ';' || finalOutput[i] == ',' || finalOutput[i] == ':' ||
      finalOutput[i] == '\'' || finalOutput[i] == '"') {
    return -4;
  }
  return -5;
}

int frontKeyword(int i) {
  const char keywords[12][20] = {"char",   "const",    "double", "else",
                                 "float",  "int",      "long",   "short",
                                 "signed", "unsigned", "void",   "FILE"};

  for (int j = 0; j < 12; j++) {
    int length = strlen(keywords[j]);
    if ((length - 1) + i < outputIndx) {
      int equal = 0;
      for (int t = 0; t < length; t++) {

        if (keywords[j][t] != finalOutput[i + t]) {
          equal = 1;
          break;
        }
      }
      if (!equal) {

        for (int k = 0; k < length; k++) {
          tempValue.data[k] = keywords[j][k];
        }

        return (length - 1) + i;
      }
    }
  }
  return -1;
}

int frontIdentifier(int i, char finalOutput[]) {

  char demo[1000];
  int demoIndx = i, demoIn = 0;
  memset(demo, 0, sizeof(demo));
  if ((finalOutput[i] >= 'a' && finalOutput[i] <= 'z') ||
      (finalOutput[i] >= 'A' && finalOutput[i] <= 'Z')) {

    int brac = 0;
    while (1) {
      if (((finalOutput[demoIndx] >= 'a' && finalOutput[demoIndx] <= 'z') ||
           (finalOutput[demoIndx] >= 'A' && finalOutput[demoIndx] <= 'Z') ||
           (finalOutput[demoIndx] >= '0' && finalOutput[demoIndx] <= '9') ||
           finalOutput[demoIndx] == '_' || finalOutput[demoIndx] == '[' ||
           finalOutput[demoIndx] == ']') &&
          !(brac == 0 && finalOutput[demoIndx] == ']')) {
        if (finalOutput[demoIndx] == '[') {
          brac++;
        } else if (finalOutput[demoIndx] == ']') {
          brac--;
        }
        demo[demoIn++] = finalOutput[demoIndx++];

      } else if (finalOutput[demoIndx] == '(' || finalOutput[demoIndx] == ' ' ||
                 finalOutput[demoIndx] == ')' || finalOutput[demoIndx] == ']' ||
                 frontSeparator(demoIndx) == -4 ||
                 frontOperator(demoIndx) == -4) {

        if (demo == "num" || demo == "sep" || demo == "op" || demo == "par" ||
            demo == "" || demo == "unwn") {
          return -1;
        }
        strcpy(tempValue.name, demo);

        return demoIndx - 1;
      } else {
        break;
      }
    }
  }

  return -1;
}
int frontNumber(int i) {

  int valueIndx = 0;
  char tempNum[1000];
  memset(tempNum, 0, sizeof(tempNum));
  tempValue.number[0] = '\0';

  while (1) {
    if ((finalOutput[i] >= '0' && finalOutput[i] <= '9') ||
        finalOutput[i] == '.') {

      tempNum[valueIndx++] = finalOutput[i++];

    } else {
      break;
    }
  }
  strcpy(tempValue.number, tempNum);

  return i - 1;
}

int getVariableValue(char strInt[], char scopeName[]) {

  for (int i = 0; i < serialNo; i++) {

    if (strcmp(tableStore[i].name, strInt) == 0 &&
        strcmp(tableStore[i].scope, scopeName) == 0) {
      char tempBack[100];
      memset(tempBack, 0, sizeof(tempBack));
      strcpy(tempBack, tableStore[i].value);

      return atoi(tempBack);
    }
  }
  return -10001;
}
/******************************************
*********** Keyword **********************
******************************************/

void preCheckKeyword() {
  separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'k';
  finalOutput[outputIndx++] = 'w';
  finalOutput[outputIndx++] = ' ';
}
int checkKeyword(int i) {

  const char keywords[34][20] = {
      "auto",     "break",  "case",    "continue", "char",     "const",
      "default",  "do",     "double",  "else",     "enum",     "extern",
      "float",    "for",    "goto",    "if",       "int",      "long",
      "register", "return", "short",   "signed",   "sizeof",   "static",
      "struct",   "switch", "typedef", "union",    "unsigned", "void",
      "volatile", "while",  "EOF",     "FILE"};

  for (int j = 0; j < 34; j++) {
    int length = strlen(keywords[j]);

    if ((length - 1) + i < indx) {
      int equal = 0;
      for (int t = 0; t < length; t++) {
        if (keywords[j][t] != printoutput[i + t]) {
          equal = 1;
          break;
        }
      }
      if (!equal) {
        preCheckKeyword();

        for (int k = 0; k < length; k++) {
          separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
              finalOutput[outputIndx++] = keywords[j][k];
        }
        separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
        saveoutput[saveOutputIndx++] = ' ';
        return (length - 1) + i;
      }
    }
  }
  return -1;
}

/******************************************
*********** Operator **********************
******************************************/

void preCheckOperator() {
  separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'o';
  finalOutput[outputIndx++] = 'p';
  finalOutput[outputIndx++] = ' ';
}
int checkOperator(int i, int isOperator) {

  const char operators[40][10] = {
      "(type)", "sizeof", "<<", ">>", "<=", ">=", "==", "!=", "&&", "||",
      "?:",     "+=",     "-=", "*=", "/=", "%=", "&=", "^=", "|=", "<<=",
      ">>=",    ".",      "->", "++", "--", "!",  "~",  "*",  "/",  "%",
      "+",      "-",      "=",  ">",  "<",  "*",  "&",  "^",  "|"};
  int equal = 0;
  for (int j = 0; j < 40; j++) {
    int length = strlen(operators[j]);

    if ((length - 1) + i < indx) {
      equal = 0;
      for (int t = 0; t < length; t++) {
        if (operators[j][t] != printoutput[i + t]) {
          equal = 1;
          break;
        }
      }

      if (!equal) {
        if (!isOperator) {
          preCheckOperator();
          for (int k = 0; k < length; k++) {
            separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
                finalOutput[outputIndx++] = operators[j][k];
          }
          separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
          saveoutput[saveOutputIndx++] = ' ';
          return (length - 1) + i;
        } else {
          return -4;
        }
      }
    }
  }
  if (equal) {
    return -5;
  }
  return -1;
}

/******************************************
*********** Parenthesis **********************
******************************************/

void preCheckParenthesis() {
  separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'p';
  finalOutput[outputIndx++] = 'a';
  finalOutput[outputIndx++] = 'r';
  finalOutput[outputIndx++] = ' ';
}

int checkParenthesis(int i) {

  if (printoutput[i] == '(' || printoutput[i] == ')' || printoutput[i] == '[' ||
      printoutput[i] == ']' || printoutput[i] == '{' || printoutput[i] == '}') {
    preCheckParenthesis();

    separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
        finalOutput[outputIndx++] = printoutput[i];
    separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
    saveoutput[saveOutputIndx++] = ' ';
    return i;
  }
}

/******************************************
*********** Number **********************
******************************************/
int checkNumber(int i) {
  separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'n';
  finalOutput[outputIndx++] = 'u';
  finalOutput[outputIndx++] = 'm';
  finalOutput[outputIndx++] = ' ';
  int valueIndx = 0;
  while (1) {
    if ((printoutput[i] >= '0' && printoutput[i] <= '9') ||
        printoutput[i] == '.') {
      separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
          tempValue.number[valueIndx++] = finalOutput[outputIndx++] =
              printoutput[i];
    } else {
      separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
      saveoutput[saveOutputIndx++] = ' ';
      break;
    }
    i++;
  }
  return i - 1;
}

/******************************************
*********** Separator **********************
******************************************/
int checkSeparator(int i, int isSeparator) {

  if (printoutput[i] == ';' || printoutput[i] == ',' || printoutput[i] == ':' ||
      printoutput[i] == '\'' || printoutput[i] == '"') {
    if (isSeparator) {
      return -4;
    } else {
      separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'p';
      finalOutput[outputIndx++] = ' ';
      separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
          finalOutput[outputIndx++] = printoutput[i];
      separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
      saveoutput[saveOutputIndx++] = ' ';
      return i;
    }
  }
  if (isSeparator)
    return -5;

  return -1;
}

/******************************************
*********** Identifier **********************
******************************************/

int checkIdentifier(int i) {

  char demo[1000];
  int demoIndx = i, demoIn = 0;
  demo[demoIn++] = '[';
  demo[demoIn++] = 'i';
  demo[demoIn++] = 'd';
  demo[demoIn++] = ' ';

  // id
  while (1) {

    if ((printoutput[demoIndx] >= 'a' && printoutput[demoIndx] <= 'z') ||
        (printoutput[demoIndx] >= 'A' && printoutput[demoIndx] <= 'Z') ||
        (printoutput[demoIndx] >= '0' && printoutput[demoIndx] <= '9') ||
        printoutput[demoIndx] == '_' || printoutput[demoIndx] == ']' ||
        printoutput[demoIndx] == '[') {
      demo[demoIn++] = printoutput[demoIndx++];
    } else if (printoutput[demoIndx] == '(' || printoutput[demoIndx] == ' ' ||
               printoutput[demoIndx] == ')' ||
               checkSeparator(demoIndx, 1) == -4 ||
               checkOperator(demoIndx, 1) == -4) {
      for (int j = 0; j < demoIn; j++) {
        separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] =
            demo[j];

        if (j > 3) {
          saveoutput[saveOutputIndx++] = demo[j];
        }
      }
      separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
      saveoutput[saveOutputIndx++] = ' ';
      return demoIndx - 1;
    } else {
      break;
    }
  }

  return -1;
}

/******************************************
*********** Unknown **********************
******************************************/
int checkUnknown(int i, int isPrint) {
  separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'u';
  finalOutput[outputIndx++] = 'n';
  finalOutput[outputIndx++] = 'w';
  finalOutput[outputIndx++] = 'n';
  finalOutput[outputIndx++] = ' ';

  while (1) {
    if (printoutput[i] == ' ' || printoutput[i] == '"' ||
        printoutput[i] == '\n' || printoutput[i] == '\'')
      break;
    else if ((printoutput[i] == '+' || printoutput[i] == '-' ||
              printoutput[i] == '=' || printoutput[i] == ')' ||
              printoutput[i] == '(' || printoutput[i] == '{' ||
              printoutput[i] == '}' || printoutput[i] == '[' ||
              printoutput[i] == ']') &&
             !isPrint)
      break;
    separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
        finalOutput[outputIndx++] = printoutput[i];
    i++;
  }
  separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
  saveoutput[saveOutputIndx++] = ' ';
  return i - 1;
}

void clr() {
  memset(tempValue.data, 0, strlen(tempValue.data));
  memset(tempValue.no, 0, strlen(tempValue.no));
  memset(tempValue.value, 0, strlen(tempValue.value));
  memset(tempValue.name, 0, strlen(tempValue.name));
  memset(tempValue.scope, 0, strlen(tempValue.scope));
  memset(tempValue.value, 0, strlen(tempValue.value));
}

int main() {

  printf("\n\nEnter your input Code :\n\n\n");
  // input portion
  file = fopen("inputfile.txt", "w");
  while (1) {
    gets(str);
    if (strcmp(str, "end") == 0)
      break;
    strcat(str, "\n");
    fputs(str, file);
  }
  fclose(file);

  // save to an array
  file = fopen("inputfile.txt", "r");
  while ((c = fgetc(file)) != EOF)
    save[in++] = c;

  save[in++] = '\0';
  fclose(file);

  // filtering  portion
  file = fopen("outputfile.txt", "w");
  printoutput[indx++] = save[0];
  for (int i = 1; i < in; i++) {
    if (save[i] == '/' && save[i + 1] == '/' && !multicomment && i < in - 1)
      singlecomment = 1;

    if (save[i] == '\n' && singlecomment) {
      singlecomment = 0;
      continue;
    }
    if (save[i + 1] == '*' && save[i] == '/' && i < in - 1 && !multicomment &&
        !singlecomment)
      multicomment = 1;

    if (multicomment == 2) {
      multicomment = 0;
      continue;
    }

    if (save[i + 1] == '/' && save[i] == '*' && i < in - 1 && multicomment) {
      multicomment = 2;
      continue;
    }

    if (!multicomment && !singlecomment && save[i] != '\n' && save[i] != '\0')
      printoutput[indx++] = save[i];
  }
  int flag1 = 0, flag2 = 0, temp = -1, gotInt = 0;

  for (int i = 0; i < indx; i++) {

    if (!gotInt) {
      if (printoutput[i] == '#') {
        separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
        finalOutput[outputIndx++] = 'h';
        finalOutput[outputIndx++] = 'd';
        finalOutput[outputIndx++] = ' ';
        while (printoutput[i] != '>') {
          if (printoutput[i] != ' ')
            separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
                finalOutput[outputIndx++] = printoutput[i++];
          else {
            finalOutput[outputIndx++] = printoutput[i++];
          }
        }

        separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
            finalOutput[outputIndx++] = '>';
        saveoutput[saveOutputIndx++] = ' ';
        separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = ']';
      }
      if (printoutput[i] == 'i')
        gotInt = 1;
    }
    if (gotInt) {

      if (printoutput[i] == ';' || printoutput[i] == ',' ||
          printoutput[i] == '\'' || printoutput[i] == '"') {
        if (printoutput[i] == '\'' && !flag1)
          flag1 = 1;
        else if (printoutput[i] == '\'' && flag1)
          flag1 = 0;

        if (printoutput[i] == '"' && !flag2)
          flag2 = 1;
        else if (printoutput[i] == '"' && flag2) {
          flag2 = 0;
          flag1 = 0;
        }

        temp = checkSeparator(i, 0);
      }

      if (!flag1 && !flag2) {

        if (printoutput[i] == 'c' || printoutput[i] == 'i' ||
            printoutput[i] == 'f' || printoutput[i] == 'b' ||
            printoutput[i] == 'd' || printoutput[i] == 'l' ||
            printoutput[i] == 'w' || printoutput[i] == 'e' ||
            printoutput[i] == 's' || printoutput[i] == 'v' ||
            printoutput[i] == 'r' || printoutput[i] == 'a' ||
            printoutput[i] == 'u' || printoutput[i] == 'g' ||
            printoutput[i] == 't' || printoutput[i] == 'E' ||
            printoutput[i] == 'F')
          temp = checkKeyword(i);

        if (printoutput[i] == '+' || printoutput[i] == '-' ||
            printoutput[i] == '*' || printoutput[i] == '/' ||
            printoutput[i] == '%' || printoutput[i] == '=' ||
            printoutput[i] == '!' || printoutput[i] == '>' ||
            printoutput[i] == '<' || printoutput[i] == '&' ||
            printoutput[i] == '|' || printoutput[i] == '~' ||
            printoutput[i] == '^' || printoutput[i] == '?')
          temp = checkOperator(i, 0);

        if (printoutput[i] == '(' || printoutput[i] == ')' ||
            printoutput[i] == '[' || printoutput[i] == ']' ||
            printoutput[i] == '{' || printoutput[i] == '}')
          temp = checkParenthesis(i);

        if (printoutput[i] >= '0' && printoutput[i] <= '9') {
          temp = checkNumber(i);
        }

        if ((temp == -1) && ((printoutput[i] >= 'a' && printoutput[i] <= 'z') ||
                             (printoutput[i] >= 'A' && printoutput[i] <= 'Z') ||
                             printoutput[i] == '_')) {

          temp = checkIdentifier(i);
        }

        if (temp == -1 && printoutput[i] != ' ' && printoutput[i] != '\n' &&
            printoutput[i] != '\0' && printoutput[i] != '"' &&
            printoutput[i] != '\'') {
          temp = (checkUnknown(i, 0));
        }
      } else if (printoutput[i] != ' ' && printoutput[i] != '\n' &&
                 printoutput[i] != '\0' && printoutput[i] != '"' &&
                 printoutput[i] != '\'') {
        temp = checkUnknown(i, 1);
      }

      if (temp != -1) {
        i = temp;
        temp = -1;
      }
    }
  }

  finalOutput[outputIndx++] = '\0';
  fputs(finalOutput, file);
  fclose(file);

  file1 = fopen("separateOutputfile.txt", "w");
  saveoutput[saveOutputIndx++] = '\0';
  fputs(saveoutput, file1);
  fclose(file1);

  file1 = fopen("separateIdOutputfile.txt", "w");
  separateIdOutput[separateIdIndx++] = '\0';
  fputs(separateIdOutput, file1);
  fclose(file1);

  // Printint Portion with keyword, id ,number, separator ,unknown,
  // paranthesis

  printf("\n\nPrinting the systax analysis with keyword, id ,number, separator "
         ",unknown, "
         "paranthesis:\n \n");
  file = fopen("outputfile.txt", "r");
  while ((c = fgetc(file)) != EOF) {
    printf("%c", c);
  }
  fclose(file);
  printf("\n\n");

  int symBolTableIndx = 0;
  // Printint Portion only with id

  printf("Printing the systax analysis only with id :\n \n");
  file = fopen("separateIdOutputfile.txt", "r");
  while ((c = fgetc(file)) != EOF) {
    printf("%c", c);
    symBolTable[symBolTableIndx++] = c;
  }
  symBolTable[symBolTableIndx] = '\0';
  fclose(file);
  printf("\n\n");

  char funcName[1000];
  for (int i = 0; i < outputIndx; i++) {
    int temp = -1, valueAssign = 0, ifId = 0;

    if (i + 4 < outputIndx && finalOutput[i] == '[' &&
        finalOutput[i + 1] == 'i' && finalOutput[i + 2] == 'd') {
      ifId = 1;
    }

    if ((i + 4 < outputIndx && finalOutput[i] == '[' &&
         finalOutput[i + 1] == 'k' && finalOutput[i + 2] == 'w') ||
        ifId || valueAssign) {

      if (!ifId)
        temp = frontKeyword(i + 4);

      if (temp != -1 || valueAssign || ifId) {

        if (temp != -1 && !ifId)
          i = temp + 2;
        temp = -1, ifId = 0;
        int loopBreak = 1, storeIndx = 0;
        char storeOperation[3000], storeName[3000];
        memset(storeOperation, 0, strlen(storeOperation));

        while ((loopBreak || valueAssign) && i < outputIndx) {
          int tempId = -1;

          if ((i + 4 < outputIndx && finalOutput[i] == '[' &&
               finalOutput[i + 1] == 'i' && finalOutput[i + 2] == 'd') ||
              valueAssign) {

            if (finalOutput[i + 1] == 'i' && finalOutput[i + 2] == 'd')
              tempId = frontIdentifier(i + 4, finalOutput);

            if (tempId != -1 || valueAssign) {

              if (tempId != -1)
                i = tempId + 2;

              if (i + 5 < outputIndx && finalOutput[i] == '[' &&
                  finalOutput[i + 1] == 's' && finalOutput[i + 2] == 'e' &&
                  finalOutput[i + 3] == 'p') {
                if (finalOutput[i + 5] == ';' || finalOutput[i + 5] == ',') {

                  int isUpdate = 0;

                  if (valueAssign) {

                    if (tempId != -1) {
                      for (int jk = 0; jk < strlen(tempValue.name); jk++) {
                        storeOperation[storeIndx++] = tempValue.name[jk];
                      }
                    }

                    char tempOpSave, strInt[1000];

                    int indxStr = 0, tempValuOp, result = 0;
                    for (int indxStrInt = 0;
                         indxStrInt < strlen(storeOperation); indxStrInt++) {

                      if (storeOperation[indxStrInt] == '+' ||
                          storeOperation[indxStrInt] == '-' ||
                          storeOperation[indxStrInt] == '/' ||
                          storeOperation[indxStrInt] == '*' ||
                          storeOperation[indxStrInt] == '%') {

                        int tempVariableValue = -10001;

                        if (funcName[0] == '\0') {
                          tempVariableValue =
                              getVariableValue(strInt, "global");
                        } else {
                          tempVariableValue =
                              getVariableValue(strInt, funcName);
                        }

                        if (tempVariableValue != -10001) {
                          memset(strInt, 0, sizeof(strInt));
                          sprintf(strInt, "%d", tempVariableValue);
                        }

                        if (tempOpSave == '\0') {
                          tempValuOp = atoi(strInt);
                        } else {
                          int nx = atoi(strInt);
                          if (tempOpSave == '+')
                            tempValuOp += nx;
                          else if (tempOpSave == '-')
                            tempValuOp -= nx;
                          else if (tempOpSave == '/')
                            tempValuOp /= nx;
                          else if (tempOpSave == '*')
                            tempValuOp *= nx;
                          else if (tempOpSave == '%')
                            tempValuOp %= nx;
                        }
                        tempOpSave = storeOperation[indxStrInt];

                        memset(strInt, 0, sizeof(strInt));

                        indxStr = 0;
                      } else {
                        strInt[indxStr++] = storeOperation[indxStrInt];
                      }
                    }

                    int lockValue = 0;
                    if (tempOpSave != '\0') {

                      int tempVariableValue = -10001;

                      if (funcName[0] == '\0') {
                        tempVariableValue = getVariableValue(strInt, "global");
                      } else {
                        tempVariableValue = getVariableValue(strInt, funcName);
                      }

                      if (tempVariableValue != -10001) {
                        memset(strInt, 0, sizeof(strInt));
                        sprintf(strInt, "%d", tempVariableValue);
                      }
                      int nx = atoi(strInt);
                      if (tempOpSave == '+')
                        tempValuOp += nx;
                      else if (tempOpSave == '-')
                        tempValuOp -= nx;
                      else if (tempOpSave == '/')
                        tempValuOp /= nx;
                      else if (tempOpSave == '*')
                        tempValuOp *= nx;
                      else if (tempOpSave == '%')
                        tempValuOp %= nx;
                      tempOpSave = '\0';
                      sprintf(storeOperation, "%d", tempValuOp);
                      memset(strInt, 0, sizeof(strInt));
                      strcpy(strInt, storeOperation);
                    }

                    if (funcName[0] == '\0') {
                      if (strInt[0] != '\0')
                        isUpdate =
                            updateVariable(operatorVariable, "global", strInt);
                      else
                        isUpdate =
                            updateVariable(operatorVariable, "global", "");
                    } else {

                      if (strInt[0] != '\0') {
                        isUpdate =
                            updateVariable(operatorVariable, funcName, strInt);

                      } else
                        isUpdate =
                            updateVariable(operatorVariable, funcName, "");
                    }
                    if (isUpdate == -1)
                      strcpy(tableStore[serialNo].value, storeOperation);

                  } else {

                    if (funcName[0] == '\0') {

                      if (operatorVariable[0] != '\0')
                        isUpdate = updateVariable(operatorVariable, "global",
                                                  storeOperation);
                      else {
                        isUpdate = updateVariable(tempValue.name, "global",
                                                  storeOperation);
                      }
                    } else {
                      if (operatorVariable[0] != '\0')
                        isUpdate = updateVariable(operatorVariable, funcName,
                                                  storeOperation);
                      else {
                        isUpdate = updateVariable(tempValue.name, funcName,
                                                  storeOperation);
                      }
                    }

                    if (isUpdate == -1)
                      strcpy(tableStore[serialNo].value, "");
                  }

                  if (isUpdate == -1) {
                    sprintf(tableStore[serialNo].no, "%d", serialNo);
                    if (operatorVariable[0] != '\0')
                      strcpy(tableStore[serialNo].name, operatorVariable);
                    else
                      strcpy(tableStore[serialNo].name, tempValue.name);
                    strcpy(tableStore[serialNo].id, "var");
                    strcpy(tableStore[serialNo].data, tempValue.data);
                    if (funcName[0] == '\0') {
                      strcpy(tableStore[serialNo].scope, "global");
                    } else {
                      strcpy(tableStore[serialNo].scope, funcName);
                    }
                  }

                  clr();
                  if (finalOutput[i + 5] == ',') {
                    strcpy(tempValue.data, tableStore[serialNo].data);
                    memset(storeOperation, 0, sizeof(storeOperation));
                  }
                  if (isUpdate == -1)
                    serialNo++;

                  valueAssign = 0;

                  if (finalOutput[i + 5] == ';') {
                    memset(operatorVariable, 0, sizeof(operatorVariable));
                    loopBreak = 0;
                    break;
                  }

                  i = i + 7;

                } else if (finalOutput[i + 5] == '\'') {
                  i = i + 7;
                } else {
                  valueAssign = 0;
                  loopBreak = 0;
                  break;
                }
                storeIndx = 0;
              } else if (i + 5 < outputIndx && finalOutput[i] == '[' &&
                         finalOutput[i + 1] == 'p' &&
                         finalOutput[i + 2] == 'a' &&
                         finalOutput[i + 3] == 'r') {

                if (finalOutput[i + 5] == '(' || finalOutput[i + 5] == ')') {
                  sprintf(tableStore[serialNo].no, "%d", serialNo);

                  strcpy(tableStore[serialNo].name, tempValue.name);
                  if (finalOutput[i + 5] == '(')
                    strcpy(tableStore[serialNo].id, "func");
                  else
                    strcpy(tableStore[serialNo].id, "var");
                  strcpy(tableStore[serialNo].data, tempValue.data);
                  if (finalOutput[i + 5] == ')')
                    strcpy(tableStore[serialNo].scope, funcName);
                  else
                    strcpy(tableStore[serialNo].scope, "global");

                  if (storeOperation[0] != '\0')
                    strcpy(tableStore[serialNo].value, storeOperation);
                  else {
                    strcpy(tableStore[serialNo].value, "");
                  }

                  if (finalOutput[i + 5] != ')')
                    strcpy(funcName, tableStore[serialNo].name);
                  serialNo++;
                  clr();
                  i = i + 6;
                  loopBreak = 0;
                  valueAssign = 0;
                  break;
                } else {
                  loopBreak = 0;
                  valueAssign = 0;
                  break;
                }
                storeIndx = 0;
                ifId = 0;
              } else if (i + 5 < outputIndx && finalOutput[i] == '[' &&
                         finalOutput[i + 1] == 'u' &&
                         finalOutput[i + 2] == 'n' &&
                         finalOutput[i + 3] == 'w' &&
                         finalOutput[i + 4] == 'n') {

                i = i + 6;

                while (i < outputIndx) {
                  if (finalOutput[i] == ']' && finalOutput[i + 1] == '[' &&
                      finalOutput[i + 2] == 'u' && finalOutput[i + 3] == 'n' &&
                      finalOutput[i + 4] == 'w' && finalOutput[i + 5] == 'n' &&
                      i + 6 < outputIndx) {
                    i += 6;
                  } else if (finalOutput[i] == ']' &&
                             finalOutput[i + 1] == '[' &&
                             finalOutput[i + 2] == 's' &&
                             finalOutput[i + 3] == 'e' &&
                             finalOutput[i + 4] == 'p' && i + 4 < outputIndx) {
                    i = i + 1;
                    break;
                  } else {
                    storeOperation[storeIndx++] = finalOutput[i++];
                  }
                }

              } else if (i + 5 < outputIndx && finalOutput[i] == '[' &&
                         finalOutput[i + 1] == 'o' &&
                         finalOutput[i + 2] == 'p') {
                if (finalOutput[i + 4] == '=') {

                  valueAssign = 1;

                  i = i + 6;
                  memset(operatorVariable, 0, sizeof(operatorVariable));
                  strcpy(operatorVariable, tempValue.name);
                  tempId = -1;

                } else if (finalOutput[i + 4] == '+' &&
                           finalOutput[i + 5] == '+') {
                  i = i + 13;
                  storeOperation[storeIndx++] = '+';
                  storeOperation[storeIndx++] = '+';

                  if (funcName[0] == '\0') {
                    for (int i = 0; i < serialNo; i++) {
                      if (strcmp(tableStore[i].name, tempValue.name) == 0 &&
                          strcmp(tableStore[i].scope, "global") == 0) {
                        char tempInc[1000];
                        strcpy(tempInc, tableStore[i].value);
                        int xValue = atoi(tempInc);
                        xValue++;
                        sprintf(tableStore[i].value, "%d", xValue);
                      }
                    }
                  } else {
                    for (int i = 0; i < serialNo; i++) {
                      if (strcmp(tableStore[i].name, tempValue.name) == 0 &&
                          strcmp(tableStore[i].scope, funcName) == 0) {
                        char tempInc[1000];
                        strcpy(tempInc, tableStore[i].value);
                        int xValue = atoi(tempInc);
                        xValue++;
                        sprintf(tableStore[i].value, "%d", xValue);
                      }
                    }
                  }

                  loopBreak = 0;
                  memset(storeOperation, 0, sizeof(storeOperation));

                  clr();
                } else if (finalOutput[i + 4] == '-' &&
                           finalOutput[i + 5] == '-') {
                  i = i + 7;
                  storeOperation[storeIndx++] = '-';
                  storeOperation[storeIndx++] = '-';
                } else if (finalOutput[i + 4] == '+') {
                  i = i + 6;
                  storeOperation[storeIndx++] = '+';

                } else if (finalOutput[i + 4] == '-') {
                  i = i + 6;
                  storeOperation[storeIndx++] = '-';
                } else if (finalOutput[i + 4] == '*') {
                  i = i + 6;
                  storeOperation[storeIndx++] = '*';
                } else if (finalOutput[i + 4] == '/') {
                  i = i + 6;
                  storeOperation[storeIndx++] = '/';
                } else if (finalOutput[i + 4] == '%') {
                  i = i + 6;
                  storeOperation[storeIndx++] = '%';
                }
              } else if ((i + 5 < outputIndx && finalOutput[i] == '[' &&
                          finalOutput[i + 1] == 'n' &&
                          finalOutput[i + 2] == 'u' &&
                          finalOutput[i + 3] == 'm') &&
                         valueAssign) {

                temp = frontNumber(i + 5);
                if (temp != -1) {

                  i = temp + 2;
                  temp = -1;
                  char tempNumSave[1000];
                  memset(tempNumSave, 0, sizeof(tempNumSave));
                  strcpy(tempNumSave, tempValue.number);
                  for (int jk = 0; jk < strlen(tempNumSave); jk++) {
                    storeOperation[storeIndx] = tempNumSave[jk];

                    storeIndx++;
                  }
                  storeOperation[storeIndx] = '\0';

                } else {
                  loopBreak = 0;
                  valueAssign = 0;
                  break;
                }
                tempId = -1;
              } else {
                loopBreak = 0;
                valueAssign = 0;
                break;
              }
            }
          }
        }
      } else if (i + 9 < outputIndx && finalOutput[i] == '[' &&
                 finalOutput[i + 1] == 'k' && finalOutput[i + 2] == 'w' &&
                 finalOutput[i + 4] == 'r' && finalOutput[i + 5] == 'e' &&
                 finalOutput[i + 6] == 't' && finalOutput[i + 7] == 'u' &&
                 finalOutput[i + 8] == 'r' && finalOutput[i + 9] == 'n') {

        memset(funcName, 0, strlen(funcName));
        i = i + 11;
      }
    }
  }
  for (int i = 0; i < serialNo; i++) {
    for (int j = i + 1; j < serialNo; j++) {
      if (strcmp(tableStore[i].name, tableStore[j].name) == 0 &&
          strcmp(tableStore[i].scope, tableStore[j].scope) == 0) {
        strcpy(tableStore[j].no, "");
        strcpy(tableStore[j].name, "");
        strcpy(tableStore[j].id, "");
        strcpy(tableStore[j].data, "");
        strcpy(tableStore[j].scope, "");
        strcpy(tableStore[j].value, "");
      }
    }
  }

  printf("\nSymbol Table :\n\n");
  printf("Sl.No.\t\tName\t\tID\t\tData\t\tScope\t\tValue \n");
  for (int i = 0; i < serialNo; i++) {
    printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s \n", tableStore[i].no,
           tableStore[i].name, tableStore[i].id, tableStore[i].data,
           tableStore[i].scope, tableStore[i].value);
  }
  printf("\n\n");

  char symbolTableStore[3000];
  int symbolTableStoreIndx = 0;
  memset(funcName, 0, sizeof(funcName));
  strcpy(funcName, "global");
  for (int i = 0; i < symBolTableIndx; i++) {
    symbolTableStore[symbolTableStoreIndx++] = symBolTable[i];

    if (symBolTable[i] == '[' && symBolTable[i + 1] == 'i' &&
        symBolTable[i + 2] == 'd' && i + 4 < symBolTableIndx) {
      symbolTableStore[symbolTableStoreIndx++] = 'i';
      symbolTableStore[symbolTableStoreIndx++] = 'd';
      symbolTableStore[symbolTableStoreIndx++] = ' ';

      memset(tempValue.name, 0, sizeof(tempValue.name));
      int temp = frontIdentifier(i + 4, symBolTable);
      i = temp;

      int funcFlag = 0;
      for (int k = 0; k < serialNo; k++) {
        if (strcmp(tableStore[k].id, "func") == 0 &&
            strcmp(tempValue.name, tableStore[k].name) == 0) {

          for (int j = 0; j < strlen(tableStore[k].no); j++) {
            symbolTableStore[symbolTableStoreIndx++] = tableStore[k].no[j];
          }
          symbolTableStore[symbolTableStoreIndx++] = ']';
          strcpy(funcName, tableStore[k].name);
          funcFlag = 1;
          break;
        }
      }
      if (!funcFlag) {
        for (int j = 0; j < serialNo; j++) {
          if (strcmp(tableStore[j].scope, funcName) == 0 &&
              strcmp(tempValue.name, tableStore[j].name) == 0) {

            for (int k = 0; k < strlen(tableStore[j].no); k++) {
              symbolTableStore[symbolTableStoreIndx++] = tableStore[j].no[k];
            }
            symbolTableStore[symbolTableStoreIndx++] = ']';
            break;
          }
        }
      }
    }
    if (i + 7 < outputIndx && symBolTable[i] == '[' &&
        symBolTable[i + 1] == 'r' && symBolTable[i + 2] == 'e' &&
        symBolTable[i + 3] == 't' && symBolTable[i + 4] == 'u' &&
        symBolTable[i + 5] == 'r' && symBolTable[i + 6] == 'n' &&
        symBolTable[i + 7] == ']') {
      strcpy(funcName, "global");
    }
  }
  symbolTableStore[symbolTableStoreIndx] = '\0';

  printf("Modified Syntax Analysis : \n\n%s\n\n", symbolTableStore);

  file = fopen("modifiedSystaxanalysisFile.txt", "w");
  fputs(symbolTableStore, file);
  fclose(file);


  return 0;
}

/*****

#include <stdio.h>
int Name(int para) {
  int x = 5, s = 1;
  x = 1 + s;
  return x;
}
int extra=3;
int main() {
  int sam = 10;
  sam++;
  int s;
  s = 3 + 1 - 2;
  char ch[100] = 'asd sdf sdf [] ';
  int value;
  value = Name(s);
  return 0;
}
end


*******/