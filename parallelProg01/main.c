#include "readNumbers.h"
#include "parseFlags.h"

#include <time.h>
#include <stdio.h>

void Usage ( char *progName )
{
  printf ( "usage: %s src1 sourceFile1  computeEffort 0.001\n", progName );
}

int main(int argc, char **argv)
{
  char   nullString[] = "\0";
  char   *srcName1 = nullString;
  double computeEffort = 0.0;
  
  commandLineFlagType flag[] =
    {
      {"src1", _string,  &srcName1 },
      {"computeEffort", _double,  &computeEffort  }
    };
  
  int numFlags = sizeof ( flag ) / sizeof ( commandLineFlagType );
  
  usageErrorType parseErrorCode = parseArgs ( argc, argv, numFlags, flag ) ;

  if ( parseErrorCode == argError  || parseErrorCode == parseError )
    {
      Usage( argv[0] );
      return ( 1 );
   }

  ReadNumberFile(srcName1, computeEffort);
    
  return 0;
}
