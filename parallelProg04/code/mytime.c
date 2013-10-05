#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  char *command = (char *) malloc(sizeof(char *) * 512);
  char *p;

  p = command;
  
  if (argc == 1)
    {
      fprintf(stderr, "%s <command with arguments to run>", argv[0]);
      return 0;
    }

  int i;

  for (i=1; i<argc; i++)
    {
      while (*argv[i] != '\0')
	{
	  *(command++) = *(argv[i]++);
	}
      *(command++) = ' ';
    }
  *command = '\0';

  command = p;

  /* Time the shell command */

  struct timeval t0, t1;
  int status;

  gettimeofday(&t0, NULL);
  status = system(command);
  gettimeofday(&t1, NULL);

  double timeElapsed = (double) t1.tv_sec-t0.tv_sec + ((double) t0.tv_usec - t1.tv_usec)/ 1000000.0;
  double timeStart =  (double) t0.tv_sec + (double) t0.tv_usec / 1000000.0;
  double timeEnd =  (double) t1.tv_sec + (double) t1.tv_usec / 1000000.0;

  fprintf(stderr, "timeStart %3.2f timeEnd %3.2f timeElapsed %3.2f\n", timeStart, timeEnd, timeElapsed);
  
  return 0;
}
