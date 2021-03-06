#include <math.h>
#include <stdio.h>
#include <string.h>


int main() {
  
  printf("\n\nEnter your input Code & write 'end' to finish input:\n\n\n");
  FILE *file;
  char str[100], save[100], printoutput[100], c;
  int in = 0, singlecomment = 0, multicomment = 0, indx = 0;

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

    if (!multicomment && !singlecomment && save[i] != '\n')
      printoutput[indx++] = save[i];
  }
  fputs(printoutput, file);
  fclose(file);

  // Printint Portion
  file = fopen("outputfile.txt", "r");
  while ((c = fgetc(file)) != EOF)
    printf("%c", c);
  fclose(file);

  return 0;
}
