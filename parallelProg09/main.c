#include "parseFlags.h"
#include "particle.h"
#include "statistics.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Usage ( char *progName )
{
  printf ( "Usage: %s numParticles 10000 shape square radius 1.0\n", progName );
}

int main(int argc, char *argv[])
{
  char   nullString[] = "\0";
  unsigned int numParticles = 0;
  char   *shapeStr = nullString;
  double radius = 0.0;
  
  commandLineFlagType flag[] =
    {
      {"numParticles", _uint,  &numParticles },
      {"shape", _string,  &shapeStr  },
      {"radius", _double, &radius }
    };
  
  int numFlags = sizeof ( flag ) / sizeof ( commandLineFlagType );
  
  usageErrorType parseErrorCode = parseArgs ( argc, argv, numFlags, flag ) ;

  /* Check that input given is valid */
  Shape shape;
  if (strcmp(shapeStr, "square") == 0)
    {
      shape = SQUARE;
    }
  else if (strcmp(shapeStr, "disk") == 0)
    {
      shape = DISK;
    }
  else
    {
      parseErrorCode = argError;
    }

  if (radius <= 0.0)
    {
      parseErrorCode = argError;
    }

  if (numParticles <= 0)
    {
      parseErrorCode = argError;
    }
  
  if ( parseErrorCode == argError  || parseErrorCode == parseError )
    {
      Usage( argv[0] );
      return ( 1 );
   }

  // Ensure random numbers each time
  srand48(time(0));

  int comm_sz;
  int my_rank;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  ParticleContainer *particleContainer;

  pCreateParticleContainer(&particleContainer);
  pInitializeParticleContainer(particleContainer, numParticles, shape, radius);
  
  if (my_rank == 0)
    {
      pInitializeParticles(particleContainer);
    }

  pSyncParticles(particleContainer);

  //pPrintParticleContainer(particleContainer);
  
  pGenStatistics(particleContainer);

  if (my_rank == 0)
    {
      pPrintStatistics(particleContainer);
    }

  MPI_Finalize();

  return 0;
}
