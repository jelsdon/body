#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_NAME "body"

void usage (int status) {
  printf ("Usage: %s [FILE]\n", PROGRAM_NAME);
  printf ("Print the middlish part of the FILE to standard output.\n"); 
  exit (status);
}


/* Open the file */
FILE open_file (char *filename) {
  FILE *fp;
  fp=fopen(filename, "r");
  if (fp == NULL) {
    printf("Err opening file\n");
    exit(1);
  }

  return *fp;
}

/* http://pubs.opengroup.org/onlinepubs/9699919799/functions/getline.html */
size_t file_lines (FILE *fp) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  
  if ( fp == NULL )
    exit(1);

  while ((read = getline(&line, &len, fp)) != -1) {
    printf("Retrieved line of length %zu :\n", read);
    printf("%s", line);
  }

  if (ferror(fp)) {
    printf ("err'd out\n");
    exit(1);
  }

  free(line);

  return 0;

}


int main (int argc, char **argv) {
  FILE *fp;

  if (argc != 2){
    printf("Only one file supported\n");
    exit(1);
  }

  /* ...try open the file */
  *fp=open_file(argv[1]);
  

  fclose(fp);
  return 0;
}
