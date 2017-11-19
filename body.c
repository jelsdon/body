#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PROGRAM_NAME "body"
#define DEFBODY 10
#define DEFOFF DEFBODY/2

struct Middle {
  size_t start;
  size_t end;
  size_t middle;
  size_t lines;
};

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

void set_random(struct Middle* middle) {
  srand((unsigned int)time(NULL));

  middle->middle=rand() % (((middle->lines - DEFOFF) ) - (DEFOFF + 1)) + (DEFOFF + 1);
  middle->start=middle->middle - DEFOFF;
  middle->end=middle->middle + DEFOFF;

}

/* 
  set_limits()
  Sets Middle structure's start and end position
  which ref where output (lines) should start and
  end.
*/
// I'm going to have to deal with signed/unsigned sometime
size_t set_limits(struct Middle* middle) {

  middle->middle = middle->lines / 2;
  
  if( ((int)middle->middle - DEFOFF) < 1) {
    middle->start = 1;
  } else {
    middle->start = (int)middle->middle - DEFOFF;
  }

  if( (middle->middle + DEFOFF) >= middle->lines) {
    middle->end = middle->lines-1;
  } else {
    middle->end = middle->middle + DEFOFF;
  }

  return middle->lines;
}

/*
  print_body()
  Using details within the Middle struct, print line
  starting from 'Middle.start' all the way through to
  'Middle.end'.
*/
void print_body(FILE *fp, struct Middle* middle) {
  ssize_t read;
  size_t len = 0;
  char *line = NULL;
  size_t lines = 0;


  // Reset to start of file
  fseek( fp, 0, 0);
  while ((read = getline(&line, &len, fp)) != -1) {
    if(lines++ >= middle->start) {
      printf("%s", line);
    }

    if(lines >= middle->end) {
      break;
    }

  }

}

int main (int argc, char **argv) {
  FILE *fp;
  struct Middle middle;
  size_t lines;


  if (argc != 2){
    printf("Only one file supported\n");
    exit(1);
  }

  /* ...try open the file */
  fp=open_file(argv[1]);

  middle.lines=file_lines(fp);

  if (middle.lines == 0 ) {
    printf("No lines in this file...\n");
    fclose(fp);
    exit(1);
  }

  if (middle.lines == 1 ||
      middle.lines == 2 ||
      middle.lines <= DEFBODY) {
    printf("Aint no body in this file...may I suggest cat?\n");
    fclose(fp);
    exit(1);
  }

  // set default 'middle' body position
  set_limits(&middle);

  // If you want to test out the random handler, uncomment below.
  //set_random(&middle);
  print_body(fp, &middle);

  fclose(fp);
  return 0;
}
