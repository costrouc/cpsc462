#include "statistics.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

Error pGenStatistics(ParticleContainer *particleContainer)
{
  particleContainer->_particleStats = (ParticleStats *) malloc(sizeof(ParticleStats));

  /* TODO In the future initialize all the values */

  pCalcPositionMean(particleContainer);
  
  pCalcPositionVariance(particleContainer);
  
  pCalcDistanceMean(particleContainer);
  
  pCalcDistanceVariance(particleContainer);
  
  pCalcDistanceInvSqrMean(particleContainer);
  
  pCalcDistanceInvSqrVariance(particleContainer);
    
  return NO_ERROR;
}

Error pCalcPositionMean(ParticleContainer *particleContainer)
{
  int my_rank;
  int comm_sz;
  
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;
  
  double *gPositionMean = (double *) malloc(sizeof(double) * numDimensions);
  double *lPositionMean = (double *) malloc(sizeof(double) * numDimensions);

  for (i = 0; i< numDimensions; i++)
    {
      lPositionMean[i] = 0.0;
    }
  
  Particle *p;

  unsigned int my_start = my_rank * (numParticles / comm_sz);
  unsigned int my_end = (my_rank + 1) * (numParticles / comm_sz);

  // Keep in mind that this may not use all the particles! But it is close
  for (i = my_start; i < my_end; i++)
    {
      p = &(particleContainer->_particles[i]);
      for (j = 0; j<numDimensions; j++)
	{
	  lPositionMean[j] += p->_position[j];
	}
    }

  for (i = 0; i<numDimensions; i++)
    {
      lPositionMean[i] *= 1.0 / numParticles;
    }

  MPI_Reduce(lPositionMean, gPositionMean, numDimensions, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
  particleContainer->_particleStats->_positionMean = gPositionMean;
  
  return NO_ERROR;
}

Error pCalcPositionVariance(ParticleContainer *particleContainer)
{
  int my_rank;
  int comm_sz;
  
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  double *positionMean = particleContainer->_particleStats->_positionMean;
  
  double *lPositionVariance = (double *) malloc(sizeof(double) * particleContainer->_numDimensions);
  double *gPositionVariance = (double *) malloc(sizeof(double) * particleContainer->_numDimensions);


  for (i = 0; i < numDimensions; i++)
    {
      lPositionVariance[i] = 0.0;
    }
  
  Particle *p;

  unsigned int my_start = my_rank * (numParticles / comm_sz);
  unsigned int my_end = (my_rank + 1) * (numParticles / comm_sz);

  for (i = my_start; i < my_end; i++)
    {
      p = &(particleContainer->_particles[i]);
      for (j = 0; j < numDimensions; j++)
	{
	  lPositionVariance[j] += pow((positionMean[j] - p->_position[j]), 2);
	}
    }

  for (i = 0; i < numDimensions; i++)
    {
      lPositionVariance[i] *= 1.0 / numParticles;
    }

  MPI_Reduce(lPositionVariance, gPositionVariance, numDimensions, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  particleContainer->_particleStats->_positionVariance = gPositionVariance;

  return NO_ERROR;
}

Error pCalcDistanceMean(ParticleContainer *particleContainer)
{
  int my_rank;
  int comm_sz;
  
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  Error error;

  double lDistanceMeanSum = 0.0;
  double gDistanceMeanSum = 0.0;
  
  double distanceParticle = 0.0;
  double distanceParticleSum = 0.0;

  Particle *p;
  Particle *q;

  unsigned int my_start = my_rank * (numParticles / comm_sz);
  unsigned int my_end = (my_rank + 1) * (numParticles / comm_sz);
  
  for (i = my_start; i < my_end; i++)
    {
      distanceParticleSum = 0.0;
      p = &(particleContainer->_particles[i]);
      
      for (j = 0; j < numParticles; j++)
	{
	  q = &(particleContainer->_particles[j]);
	  
	  if ( i == j )
	    {
	      continue;
	    }
	  
	  if ((error = pDistance(p, q, numDimensions, &distanceParticle)) != NO_ERROR)
	    {
	      return error;
	    }

	  distanceParticleSum += distanceParticle;
	  
	}
      lDistanceMeanSum += distanceParticleSum / (numParticles- 1);
    }

  lDistanceMeanSum *= 1.0 / numParticles;

  MPI_Reduce(&lDistanceMeanSum, &gDistanceMeanSum, 1, MPI_DOUBLE, MPI_SUM,0, MPI_COMM_WORLD);

  particleContainer->_particleStats->_distanceMean = gDistanceMeanSum;

  return NO_ERROR;
}

Error pCalcDistanceVariance(ParticleContainer *particleContainer)
{
  int my_rank;
  int comm_sz;
  
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  double distanceMean = particleContainer->_particleStats->_distanceMean;

  Error error;

  double lDistanceVarianceSum = 0.0;
  double gDistanceVarianceSum = 0.0;

  double distanceParticle = 0.0;
  double distanceParticleSum = 0.0;

  Particle *p;
  Particle *q;
  
  unsigned int my_start = my_rank * (numParticles / comm_sz);
  unsigned int my_end = (my_rank + 1) * (numParticles / comm_sz);
  
  for (i = my_start; i < my_end; i++)
    {
      distanceParticleSum = 0.0;
      p = &(particleContainer->_particles[i]);
      
      for (j = 0; j < numParticles; j++)
	{
	  q = &(particleContainer->_particles[j]);
	  
	  if ( i == j )
	    {
	      continue;
	    }
	  
	  if ((error = pDistance(p, q, numDimensions, &distanceParticle)) != NO_ERROR)
	    {
	      return error;
	    }

	  distanceParticleSum += pow(distanceParticle - distanceMean, 2);
	  
	}
      lDistanceVarianceSum += distanceParticleSum / (numParticles - 1);
    }

  lDistanceVarianceSum *= 1.0 / numParticles;
  
  MPI_Reduce(&lDistanceVarianceSum, &gDistanceVarianceSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  particleContainer->_particleStats->_distanceVariance = gDistanceVarianceSum;

  return NO_ERROR;
}

Error pCalcDistanceInvSqrMean(ParticleContainer *particleContainer)
{
  int my_rank;
  int comm_sz;
  
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  Error error;

  double lInvSqrDistanceMeanSum = 0.0;
  double gInvSqrDistanceMeanSum = 0.0;
  
  double invSqrDistanceParticle = 0.0;
  double invSqrDistanceParticleSum = 0.0;

  Particle *p;
  Particle *q;

  unsigned int my_start = my_rank * (numParticles / comm_sz);
  unsigned int my_end = (my_rank + 1) * (numParticles / comm_sz);
  
  for (i = my_start; i < my_end; i++)
    {
      invSqrDistanceParticleSum = 0.0;
      p = &(particleContainer->_particles[i]);
      
      for (j = 0; j < numParticles; j++)
	{
	  q = &(particleContainer->_particles[j]);
	  
	  if ( i == j )
	    {
	      continue;
	    }
	  
	  if ((error = pInverseSquareDistance(p, q, numDimensions, &invSqrDistanceParticle)) != NO_ERROR)
	    {
	      return error;
	    }

	  invSqrDistanceParticleSum += invSqrDistanceParticle;
	  
	}
      lInvSqrDistanceMeanSum += invSqrDistanceParticleSum / (numParticles - 1);
    }

  lInvSqrDistanceMeanSum *= 1.0 / numParticles;

  MPI_Reduce(&lInvSqrDistanceMeanSum, &gInvSqrDistanceMeanSum, 1, MPI_DOUBLE, MPI_SUM,0, MPI_COMM_WORLD);
  
  particleContainer->_particleStats->_distanceInvSqrMean = gInvSqrDistanceMeanSum;

  return NO_ERROR;
}

Error pCalcDistanceInvSqrVariance(ParticleContainer *particleContainer)
{
  int my_rank;
  int comm_sz;
  
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  double invSqrDistanceMean = particleContainer->_particleStats->_distanceInvSqrMean;
  

  Error error;

  double lInvSqrDistanceVarianceSum = 0.0;
  double gInvSqrDistanceVarianceSum = 0.0;
  
  double invSqrDistanceParticle = 0.0;
  double invSqrDistanceParticleSum = 0.0;

  Particle *p;
  Particle *q;

  unsigned int my_start = my_rank * (numParticles / comm_sz);
  unsigned int my_end = (my_rank + 1) * (numParticles / comm_sz);
  
  for (i = my_start; i < my_end; i++)
    {
      invSqrDistanceParticleSum = 0.0;
      p = &(particleContainer->_particles[i]);
      
      for (j = 0; j < numParticles; j++)
	{
	  q = &(particleContainer->_particles[j]);
	  
	  if ( i == j )
	    {
	      continue;
	    }
	  
	  if ((error = pInverseSquareDistance(p, q, numDimensions, &invSqrDistanceParticle)) != NO_ERROR)
	    {
	      return error;
	    }

	  invSqrDistanceParticleSum += pow(invSqrDistanceParticle - invSqrDistanceMean, 2);
	  
	}
      lInvSqrDistanceVarianceSum += invSqrDistanceParticleSum / (numParticles - 1);
    }

  lInvSqrDistanceVarianceSum *= 1.0 / numParticles;
  
  MPI_Reduce(&lInvSqrDistanceVarianceSum, &gInvSqrDistanceVarianceSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  particleContainer->_particleStats->_distanceInvSqrVariance = gInvSqrDistanceVarianceSum;

  return NO_ERROR;
}

void pPrintStatistics(ParticleContainer *particleContainer)
{
  printf("numParticles %u\n", particleContainer->_numParticles);

  switch (particleContainer->_shape)
    {
    case DISK:
      printf("shape disk\n");
      break;
    case SQUARE:
      printf("shape square\n");
      break;
    }

  ParticleStats *particleStats = particleContainer->_particleStats;
  
  char *positions[] = {"x", "y", "z", "t"};
  unsigned int i;
  for (i=0; i<particleContainer->_numDimensions; i++)
    {
      printf("%sMean %f\n", positions[i], particleStats->_positionMean[i]);
    }
  
  for (i=0; i<particleContainer->_numDimensions; i++)
    {
      printf("%sVariance %f\n", positions[i], particleStats->_positionVariance[i]);
    }

  printf("distanceMean %f\n", particleStats->_distanceMean);

  printf("distanceVariance %f\n", particleStats->_distanceVariance);
    
  printf("distanceInverseSquareMean %f\n", particleStats->_distanceInvSqrMean);

  printf("distanceInverseSquaredVariance %f\n", particleStats->_distanceInvSqrVariance);
}
