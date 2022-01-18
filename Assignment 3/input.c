#include <math.h>
#include <stdio.h>
#include <string.h>

FILE *file, *file1;
char str[3000], save[3000], printoutput[3000], finalOutput[3000], c,
    saveoutput[3000], separateIdOutput[3000];
int in = 0, singlecomment = 0, multicomment = 0, indx = 0, outputIndx = 0,
    saveOutputIndx = 0, separateIdIndx = 0;

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
  while (1) {
    if ((printoutput[i] >= '0' && printoutput[i] <= '9') ||
        printoutput[i] == '.') {
      separateIdOutput[separateIdIndx++] = saveoutput[saveOutputIndx++] =
          finalOutput[outputIndx++] = printoutput[i];
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

  separateIdOutput[separateIdIndx++] = finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 's';
  finalOutput[outputIndx++] = 'e';
  finalOutput[outputIndx++] = 'p';
  finalOutput[outputIndx++] = ' ';
  if (printoutput[i] == ';' || printoutput[i] == ',' || printoutput[i] == ':' ||
      printoutput[i] == '\'' || printoutput[i] == '"') {
    if (isSeparator) {
      return -4;
    } else {
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
       separateIdOutput[separateIdIndx++]= finalOutput[outputIndx++] = demo[j];
        
        if (j > 3) {
          saveoutput[saveOutputIndx++] = demo[j];
        }
      }
      separateIdOutput[separateIdIndx++]=finalOutput[outputIndx++] = ']';
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

int main() {

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
        separateIdOutput[separateIdIndx++]=finalOutput[outputIndx++] = '[';
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

  // Printint Portion
  file = fopen("separateIdOutputfile.txt", "r");
  while ((c = fgetc(file)) != EOF)
    printf("%c", c);
  fclose(file);

  return 0;
}