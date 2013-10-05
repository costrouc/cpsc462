#include "compute.h"

#include <stdio.h>

void ReadNumberFile(char *filename, float effort)
{
  FILE *inputfile;

  /* Read from inputfile */
  /* printf ( "Opening file %s \n", filename); */

  inputfile = fopen (filename, "r" );
  
  if ( inputfile != NULL)
    {
      printf("Reading from %s...\n", filename);

      int randomNumber;
      
      while (fscanf(inputfile, "%d", &randomNumber) == 1)
	{
	  /* We supposedly do something with randomNumber */
	  Compute(effort);
	}
      
      fclose ( inputfile );
    }
  else
    {
      fprintf (stderr, "Could not open inputfile = %s (pointer %ld) \n", filename, (long) inputfile);
      return;
    }
  
  
}

