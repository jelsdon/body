#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_NAME "body"

void usage (int status) {
  printf ("Usage: %s [FILE]\n", PROGRAM_NAME);
  printf ("Print the middlish part of the FILE to standard output.\n"); 
  exit (status);
}


/* Open the file */
FILE* open_file (char *filename) {
  FILE *fp;
  fp=fopen(filename, "r");
  if (fp == NULL) {
    printf("Err opening file\n");
    exit(1);
  }

  return fp;
}

/* http://pubs.opengroup.org/onlinepubs/9699919799/functions/getline.html */
size_t file_lines (FILE *fp) {
  char *line = NULL;
  size_t len = 0;
  size_t lines = 0;
  ssize_t read;
  if ( fp == NULL )
    exit(1);

  while ((read = getline(&line, &len, fp)) != -1) {
    // printf("Retrieved line of length %zu :\n", read);
    // printf("%s", line);
    lines++;
  }

  if (ferror(fp)) {
    printf ("err'd out\n");
    exit(1);
  }

  free(line);

  return lines;

}


int main (int argc, char **argv) {
  FILE *fp;
  size_t lines;

  if (argc != 2){
    printf("Only one file supported\n");
    exit(1);
  }

  /* ...try open the file */
  fp=open_file(argv[1]);

  lines=file_lines(fp);

  if (lines == 0) {
    printf("No lines in this file...\n");
    fclose(fp);
    exit(1);
  }

  if (lines == 1) {
    printf("Aint no body in this file...may I suggest cat?\n");
    fclose(fp);
    exit(1);
  }

  if (lines == 2) {
    printf("Aint no body in this file...may I suggest cat?\n");
    fclose(fp);
    exit(1);
  }

  fclose(fp);
  return 0;
}
