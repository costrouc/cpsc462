#include <time.h>

void Compute ( float effort )
{
  struct timespec rqtp;
  struct timespec rmtp;

  rqtp.tv_sec  = (long) effort;
  rqtp.tv_nsec = (effort - ((long) effort) ) * 1000000000 ;

  nanosleep(&rqtp, &rmtp);
}
