#include <math.h>
#include <stdio.h>
#include <string.h>

FILE *file;
char str[1000], save[1000], printoutput[1000], finalOutput[1000], c;
int in = 0, singlecomment = 0, multicomment = 0, indx = 0, outputIndx = 0;

/******************************************
*********** Keyword **********************
******************************************/

void preCheckKeyword() {
  finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'k';
  finalOutput[outputIndx++] = 'w';
  finalOutput[outputIndx++] = ' ';
}
int checkKeyword(int i) {

  // int
  if (printoutput[i] == 'i' && i + 2 < indx) {
    if (printoutput[i + 1] == 'n' && printoutput[i + 2] == 't') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = ']';

      return i + 2;
    }
  }

  // float
  if (printoutput[i] == 'f' && i + 4 < indx) {
    if (printoutput[i + 1] == 'l' && printoutput[i + 2] == 'o' &&
        printoutput[i + 3] == 'a' && printoutput[i + 4] == 't') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'f';
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = ']';

      return i + 4;
    }
  }

  // double
  if (printoutput[i] == 'd' && i + 5 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 'u' &&
        printoutput[i + 3] == 'b' && printoutput[i + 4] == 'l' &&
        printoutput[i + 5] == 'e') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'd';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'b';
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // long
  if (printoutput[i] == 'l' && i + 3 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 'n' &&
        printoutput[i + 3] == 'g') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 'g';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // char
  if (printoutput[i] == 'c' && i + 3 < indx) {
    if (printoutput[i + 1] == 'h' && printoutput[i + 2] == 'a' &&
        printoutput[i + 3] == 'r') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'c';
      finalOutput[outputIndx++] = 'h';
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // break
  if (printoutput[i] == 'b' && i + 4 < indx) {
    if (printoutput[i + 1] == 'r' && printoutput[i + 2] == 'e' &&
        printoutput[i + 3] == 'a' && printoutput[i + 4] == 'k') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'b';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 'k';
      finalOutput[outputIndx++] = ']';

      return i + 4;
    }
  }

  // continue
  if (printoutput[i] == 'c' && i + 7 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 'n' &&
        printoutput[i + 3] == 't' && printoutput[i + 4] == 'i' &&
        printoutput[i + 5] == 'n' && printoutput[i + 6] == 'u' &&
        printoutput[i + 7] == 'e') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'c';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = ']';

      return i + 7;
    }
  }

  // while
  if (printoutput[i] == 'w' && i + 4 < indx) {
    if (printoutput[i + 1] == 'h' && printoutput[i + 2] == 'i' &&
        printoutput[i + 3] == 'l' && printoutput[i + 4] == 'e') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'w';
      finalOutput[outputIndx++] = 'h';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = ']';

      return i + 4;
    }
  }

  // do
  if (printoutput[i] == 'd' && i + 1 < indx) {
    if (printoutput[i + 1] == 'o') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'd';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  // for
  if (printoutput[i] == 'f' && i + 2 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 'r') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'f';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = ']';

      return i + 2;
    }
  }

  // if
  if (printoutput[i] == 'i' && i + 1 < indx) {
    if (printoutput[i + 1] == 'f') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'f';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  // else
  if (printoutput[i] == 'e' && i + 3 < indx) {
    if (printoutput[i + 1] == 'l' && printoutput[i + 2] == 's' &&
        printoutput[i + 3] == 'e') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // switch
  if (printoutput[i] == 's' && i + 5 < indx) {
    if (printoutput[i + 1] == 'w' && printoutput[i + 2] == 'i' &&
        printoutput[i + 3] == 't' && printoutput[i + 4] == 'c' &&
        printoutput[i + 5] == 'h') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'w';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'c';
      finalOutput[outputIndx++] = 'h';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // case
  if (printoutput[i] == 'c' && i + 3 < indx) {
    if (printoutput[i + 1] == 'a' && printoutput[i + 2] == 's' &&
        printoutput[i + 3] == 'e') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'c';
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // default
  if (printoutput[i] == 'd' && i + 6 < indx) {
    if (printoutput[i + 1] == 'e' && printoutput[i + 2] == 'f' &&
        printoutput[i + 3] == 'a' && printoutput[i + 4] == 'u' &&
        printoutput[i + 5] == 'l' && printoutput[i + 6] == 't') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'd';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'f';
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = ']';

      return i + 6;
    }
  }

  // void
  if (printoutput[i] == 'v' && i + 3 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 'i' &&
        printoutput[i + 3] == 'd') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'v';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'd';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // return
  if (printoutput[i] == 'r' && i + 5 < indx) {
    if (printoutput[i + 1] == 'e' && printoutput[i + 2] == 't' &&
        printoutput[i + 3] == 'u' && printoutput[i + 4] == 'r' &&
        printoutput[i + 5] == 'n') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // auto
  if (printoutput[i] == 'a' && i + 3 < indx) {
    if (printoutput[i + 1] == 'u' && printoutput[i + 2] == 't' &&
        printoutput[i + 3] == 'o') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // const
  if (printoutput[i] == 'c' && i + 4 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 'n' &&
        printoutput[i + 3] == 's' && printoutput[i + 4] == 't') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'c';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = ']';

      return i + 4;
    }
  }

  // short
  if (printoutput[i] == 's' && i + 4 < indx) {
    if (printoutput[i + 1] == 'h' && printoutput[i + 2] == 'o' &&
        printoutput[i + 3] == 'r' && printoutput[i + 4] == 't') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'h';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = ']';

      return i + 4;
    }
  }

  // struct
  if (printoutput[i] == 's' && i + 5 < indx) {
    if (printoutput[i + 1] == 't' && printoutput[i + 2] == 'r' &&
        printoutput[i + 3] == 'u' && printoutput[i + 4] == 'c' &&
        printoutput[i + 5] == 't') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'c';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // unsigned
  if (printoutput[i] == 'u' && i + 7 < indx) {
    if (printoutput[i + 1] == 'n' && printoutput[i + 2] == 's' &&
        printoutput[i + 3] == 'i' && printoutput[i + 4] == 'g' &&
        printoutput[i + 5] == 'n' && printoutput[i + 6] == 'e' &&
        printoutput[i + 7] == 'd') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'g';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'd';
      finalOutput[outputIndx++] = ']';

      return i + 7;
    }
  }

  // signed
  if (printoutput[i] == 's' && i + 5 < indx) {
    if (printoutput[i + 1] == 'i' && printoutput[i + 2] == 'g' &&
        printoutput[i + 3] == 'n' && printoutput[i + 4] == 'e' &&
        printoutput[i + 5] == 'd') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'g';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'd';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // enum
  if (printoutput[i] == 'e' && i + 3 < indx) {
    if (printoutput[i + 1] == 'n' && printoutput[i + 2] == 'u' &&
        printoutput[i + 3] == 'm') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'm';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // goto
  if (printoutput[i] == 'g' && i + 3 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 't' &&
        printoutput[i + 3] == 'o') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'g';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = '0';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }

  // register
  if (printoutput[i] == 'r' && i + 7 < indx) {
    if (printoutput[i + 1] == 'e' && printoutput[i + 2] == 'g' &&
        printoutput[i + 3] == 'i' && printoutput[i + 4] == 's' &&
        printoutput[i + 5] == 't' && printoutput[i + 6] == 'e' &&
        printoutput[i + 7] == 'r') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'g';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = ']';

      return i + 7;
    }
  }

  // sizeof
  if (printoutput[i] == 's' && i + 5 < indx) {
    if (printoutput[i + 1] == 'i' && printoutput[i + 2] == 'z' &&
        printoutput[i + 3] == 'e' && printoutput[i + 4] == 'o' &&
        printoutput[i + 5] == 'f') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'z';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'f';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // typedef
  if (printoutput[i] == 't' && i + 6 < indx) {
    if (printoutput[i + 1] == 'y' && printoutput[i + 2] == 'p' &&
        printoutput[i + 3] == 'e' && printoutput[i + 4] == 'd' &&
        printoutput[i + 5] == 'e' && printoutput[i + 6] == 'f') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'y';
      finalOutput[outputIndx++] = 'p';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'd';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'f';
      finalOutput[outputIndx++] = ']';

      return i + 6;
    }
  }

  // volatile
  if (printoutput[i] == 'v' && i + 7 < indx) {
    if (printoutput[i + 1] == 'o' && printoutput[i + 2] == 'l' &&
        printoutput[i + 3] == 'a' && printoutput[i + 4] == 't' &&
        printoutput[i + 5] == 'i' && printoutput[i + 6] == 'l' &&
        printoutput[i + 7] == 'e') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'v';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'l';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = ']';

      return i + 7;
    }
  }
  // extern
  if (printoutput[i] == 'e' && i + 5 < indx) {
    if (printoutput[i + 1] == 'x' && printoutput[i + 2] == 't' &&
        printoutput[i + 3] == 'e' && printoutput[i + 4] == 'r' &&
        printoutput[i + 5] == 'n') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'x';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'e';
      finalOutput[outputIndx++] = 'r';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // static
  if (printoutput[i] == 's' && i + 5 < indx) {
    if (printoutput[i + 1] == 't' && printoutput[i + 2] == 'a' &&
        printoutput[i + 3] == 't' && printoutput[i + 4] == 'i' &&
        printoutput[i + 5] == 'c') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 's';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'a';
      finalOutput[outputIndx++] = 't';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'c';
      finalOutput[outputIndx++] = ']';

      return i + 5;
    }
  }

  // union
  if (printoutput[i] == 'u' && i + 4 < indx) {
    if (printoutput[i + 1] == 'n' && printoutput[i + 2] == 'i' &&
        printoutput[i + 3] == 'o' && printoutput[i + 4] == 'n') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'u';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = 'i';
      finalOutput[outputIndx++] = 'o';
      finalOutput[outputIndx++] = 'n';
      finalOutput[outputIndx++] = ']';

      return i + 4;
    }
  }

  // EOF
  if (printoutput[i] == 'E' && i + 2 < indx) {
    if (printoutput[i + 1] == 'O' && printoutput[i + 2] == 'F') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'E';
      finalOutput[outputIndx++] = 'O';
      finalOutput[outputIndx++] = 'F';
      finalOutput[outputIndx++] = ']';

      return i + 2;
    }
  }

  // FILE
  if (printoutput[i] == 'F' && i + 3 < indx) {
    if (printoutput[i + 1] == 'I' && printoutput[i + 2] == 'L' &&
        printoutput[i + 3] == 'E') {
      preCheckKeyword();
      finalOutput[outputIndx++] = 'F';
      finalOutput[outputIndx++] = 'I';
      finalOutput[outputIndx++] = 'L';
      finalOutput[outputIndx++] = 'E';
      finalOutput[outputIndx++] = ']';

      return i + 3;
    }
  }
  return -1;
}

/******************************************
*********** Operator **********************
******************************************/

void preCheckOperator() {
  finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'o';
  finalOutput[outputIndx++] = 'p';
  finalOutput[outputIndx++] = ' ';
}
int checkOperator(int i) {

  if (printoutput[i] == '|' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '|';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '^' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '^';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '+' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '+';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '-' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '!';
      finalOutput[outputIndx++] = '-';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '*' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '*';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '/' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '/';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '%' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '%';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '<' && i + 2 < indx) {
    if (printoutput[i + 1] == '<' || printoutput[i + 2] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '<';
      finalOutput[outputIndx++] = '<';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 2;
    }
  }

  if (printoutput[i] == '>' && i + 2 < indx) {
    if (printoutput[i + 1] == '>' || printoutput[i + 2] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '>';
      finalOutput[outputIndx++] = '>';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 2;
    }
  }

  if (printoutput[i] == '&' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '&';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '<' && i + 1 < indx) {
    if (printoutput[i + 1] == '<') {
      preCheckOperator();
      finalOutput[outputIndx++] = '<';
      finalOutput[outputIndx++] = '<';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '>' && i + 1 < indx) {
    if (printoutput[i + 1] == '>') {
      preCheckOperator();
      finalOutput[outputIndx++] = '>';
      finalOutput[outputIndx++] = '>';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '>' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '>';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }
  if (printoutput[i] == '<' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '<';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '&' && i + 1 < indx) {
    if (printoutput[i + 1] == '&') {
      preCheckOperator();
      finalOutput[outputIndx++] = '&';
      finalOutput[outputIndx++] = '&';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '|' && i + 1 < indx) {
    if (printoutput[i + 1] == '|') {
      preCheckOperator();
      finalOutput[outputIndx++] = '|';
      finalOutput[outputIndx++] = '|';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '+' && i + 1 < indx) {
    if (printoutput[i + 1] == '+') {
      preCheckOperator();
      finalOutput[outputIndx++] = '+';
      finalOutput[outputIndx++] = '+';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '-' && i + 1 < indx) {
    if (printoutput[i + 1] == '-') {
      preCheckOperator();
      finalOutput[outputIndx++] = '-';
      finalOutput[outputIndx++] = '-';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '=' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  if (printoutput[i] == '!' && i + 1 < indx) {
    if (printoutput[i + 1] == '=') {
      preCheckOperator();
      finalOutput[outputIndx++] = '!';
      finalOutput[outputIndx++] = '=';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }

  //+
  if (printoutput[i] == '+') {
    preCheckOperator();
    finalOutput[outputIndx++] = '+';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  //-
  if (printoutput[i] == '-') {
    preCheckOperator();
    finalOutput[outputIndx++] = '-';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  //*
  if (printoutput[i] == '*') {
    preCheckOperator();
    finalOutput[outputIndx++] = '*';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  // /
  if (printoutput[i] == '/') {
    preCheckOperator();
    finalOutput[outputIndx++] = '/';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '%') {
    preCheckOperator();
    finalOutput[outputIndx++] = '%';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '>') {
    preCheckOperator();
    finalOutput[outputIndx++] = '>';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '<') {
    preCheckOperator();
    finalOutput[outputIndx++] = '<';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '!') {
    preCheckOperator();
    finalOutput[outputIndx++] = '!';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '&') {
    preCheckOperator();
    finalOutput[outputIndx++] = '&';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '~') {
    preCheckOperator();
    finalOutput[outputIndx++] = '~';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '|') {
    preCheckOperator();
    finalOutput[outputIndx++] = '|';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '^') {
    preCheckOperator();
    finalOutput[outputIndx++] = '^';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '=') {
    preCheckOperator();
    finalOutput[outputIndx++] = '=';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  if (printoutput[i] == '?' && i + 1 < indx) {
    if (printoutput[i + 1] == ':') {
      preCheckOperator();
      finalOutput[outputIndx++] = '?';
      finalOutput[outputIndx++] = ':';
      finalOutput[outputIndx++] = ']';

      return i + 1;
    }
  }
  return -1;
}

/******************************************
*********** Parenthesis **********************
******************************************/

void preCheckParenthesis() {
  finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'p';
  finalOutput[outputIndx++] = 'a';
  finalOutput[outputIndx++] = 'r';
  finalOutput[outputIndx++] = ' ';
}

int checkParenthesis(int i) {
  // (
  if (printoutput[i] == '(') {
    preCheckParenthesis();
    finalOutput[outputIndx++] = '(';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  // )
  if (printoutput[i] == ')') {
    preCheckParenthesis();
    finalOutput[outputIndx++] = ')';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  // [
  if (printoutput[i] == '[') {
    preCheckParenthesis();
    finalOutput[outputIndx++] = '[';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  // ]
  if (printoutput[i] == ']') {
    preCheckParenthesis();
    finalOutput[outputIndx++] = ']';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  // {
  if (printoutput[i] == '{') {
    preCheckParenthesis();
    finalOutput[outputIndx++] = '{';
    finalOutput[outputIndx++] = ']';

    return i;
  }

  // }
  if (printoutput[i] == '}') {
    preCheckParenthesis();
    finalOutput[outputIndx++] = '}';
    finalOutput[outputIndx++] = ']';

    return i;
  }
}

/******************************************
*********** Number **********************
******************************************/
int checkNumber(int i) {
  finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'n';
  finalOutput[outputIndx++] = 'u';
  finalOutput[outputIndx++] = 'm';
  finalOutput[outputIndx++] = ' ';
  while (1) {
    if ((printoutput[i] >= '0' && printoutput[i] <= '9') ||
        printoutput[i] == '.') {
      finalOutput[outputIndx++] = printoutput[i];
    } else {
      finalOutput[outputIndx++] = ']';
      break;
    }
    i++;
  }
  return i - 1;
}

/******************************************
*********** Separator **********************
******************************************/
int checkSeparator(int i) {
  finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 's';
  finalOutput[outputIndx++] = 'e';
  finalOutput[outputIndx++] = 'p';
  finalOutput[outputIndx++] = ' ';
  if (printoutput[i] == ';') {
    finalOutput[outputIndx++] = ';';
    finalOutput[outputIndx++] = ']';
    return i;
  }

  if (printoutput[i] == ',') {
    finalOutput[outputIndx++] = ',';
    finalOutput[outputIndx++] = ']';
    return i;
  }

  if (printoutput[i] == ';') {
    finalOutput[outputIndx++] = ';';
    finalOutput[outputIndx++] = ']';
    return i;
  }

  if (printoutput[i] == '\'') {
    finalOutput[outputIndx++] = '\'';
    finalOutput[outputIndx++] = ']';
    return i;
  }

  if (printoutput[i] == '"') {
    finalOutput[outputIndx++] = '"';
    finalOutput[outputIndx++] = ']';
    return i;
  }
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
    } else if (printoutput[demoIndx] == ';' || printoutput[demoIndx] == ',' ||
               printoutput[demoIndx] == '=' || printoutput[demoIndx] == '(' ||
               printoutput[demoIndx] == ' ') {

      for (int j = 0; j < demoIn; j++) {
        finalOutput[outputIndx++] = demo[j];
      }
      finalOutput[outputIndx++] = ']';
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
int checkUnknown(int i) {
  finalOutput[outputIndx++] = '[';
  finalOutput[outputIndx++] = 'u';
  finalOutput[outputIndx++] = 'n';
  finalOutput[outputIndx++] = 'w';
  finalOutput[outputIndx++] = 'n';
  finalOutput[outputIndx++] = ' ';

  while (1) {
    if (printoutput[i] == ' ' || printoutput[i] == '"' ||
        printoutput[i] == '\n' || printoutput[i] == '\'' ||
        printoutput[i] == '+' || printoutput[i] == '-' ||
        printoutput[i] == '=' || printoutput[i] == ')' ||
        printoutput[i] == '(' || printoutput[i] == '{' ||
        printoutput[i] == '}' || printoutput[i] == '[' || printoutput[i] == ']')
      break;
    finalOutput[outputIndx++] = printoutput[i];
    i++;
  }
  finalOutput[outputIndx++] = ']';
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
        finalOutput[outputIndx++] = '[';
        finalOutput[outputIndx++] = 'h';
        finalOutput[outputIndx++] = 'd';
        finalOutput[outputIndx++] = ' ';
        while (printoutput[i] != '>')
          finalOutput[outputIndx++] = printoutput[i++];
        finalOutput[outputIndx++] = '>';
        finalOutput[outputIndx++] = ']';
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

        temp = checkSeparator(i);
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
          temp = checkOperator(i);

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
          temp = (checkUnknown(i));
        }
      } else if (printoutput[i] != ' ' && printoutput[i] != '\n' &&
                 printoutput[i] != '\0' && printoutput[i] != '"' &&
                 printoutput[i] != '\'') {
        temp = checkUnknown(i);
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

  // Printint Portion
  file = fopen("outputfile.txt", "r");
  while ((c = fgetc(file)) != EOF)
    printf("%c", c);
  fclose(file);

  return 0;
}