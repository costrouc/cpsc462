#include "statistics.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;
  
  double *positionMean = (double *) malloc(sizeof(double) * numDimensions);

  for (i = 0; i< numDimensions; i++)
    {
      positionMean[i] = 0.0;
    }
  
  Particle *p;
  for (i = 0; i<numParticles; i++)
    {
      p = &(particleContainer->_particles[i]);
      for (j = 0; j<numDimensions; j++)
	{
	  positionMean[j] += p->_position[j];
	}
    }

  for (i = 0; i<numDimensions; i++)
    {
      positionMean[i] *= 1.0 / numParticles;
    }

  particleContainer->_particleStats->_positionMean = positionMean;

  return NO_ERROR;
}

Error pCalcPositionVariance(ParticleContainer *particleContainer)
{
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  double *positionMean = particleContainer->_particleStats->_positionMean;
  
  double *positionVariance = (double *) malloc(sizeof(double) * particleContainer->_numDimensions);

  for (i = 0; i < numDimensions; i++)
    {
      positionVariance[i] = 0.0;
    }
  
  Particle *p;
  for (i = 0; i < numParticles; i++)
    {
      p = &(particleContainer->_particles[i]);
      for (j = 0; j < numDimensions; j++)
	{
	  positionVariance[j] += pow((positionMean[j] - p->_position[j]), 2);
	}
    }

  for (i = 0; i < numDimensions; i++)
    {
      positionVariance[i] *= 1.0 / numParticles;
    }

  particleContainer->_particleStats->_positionVariance = positionVariance;

  return NO_ERROR;
}

Error pCalcDistanceMean(ParticleContainer *particleContainer)
{
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  Error error;

  double distanceMeanSum = 0.0;
  double distanceParticle = 0.0;
  double distanceParticleSum = 0.0;

  Particle *p;
  Particle *q;
  
  for (i = 0; i < numParticles; i++)
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
      distanceMeanSum += distanceParticleSum / (numParticles - 1);
    }

  particleContainer->_particleStats->_distanceMean = distanceMeanSum / numParticles;

  return NO_ERROR;
}

Error pCalcDistanceVariance(ParticleContainer *particleContainer)
{
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  double distanceMean = particleContainer->_particleStats->_distanceMean;

  Error error;

  double distanceVarianceSum = 0.0;
  double distanceParticle = 0.0;
  double distanceParticleSum = 0.0;

  Particle *p;
  Particle *q;
  
  for (i = 0; i < numParticles; i++)
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
      distanceVarianceSum += distanceParticleSum / (numParticles - 1);
    }

  particleContainer->_particleStats->_distanceVariance = distanceVarianceSum / numParticles;

  return NO_ERROR;
}

Error pCalcDistanceInvSqrMean(ParticleContainer *particleContainer)
{
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  Error error;

  double invSqrDistanceMeanSum = 0.0;
  double invSqrDistanceParticle = 0.0;
  double invSqrDistanceParticleSum = 0.0;

  Particle *p;
  Particle *q;
  
  for (i = 0; i < numParticles; i++)
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
      invSqrDistanceMeanSum += invSqrDistanceParticleSum / (numParticles - 1);
    }

  particleContainer->_particleStats->_distanceInvSqrMean = invSqrDistanceMeanSum / numParticles;

  return NO_ERROR;
}

Error pCalcDistanceInvSqrVariance(ParticleContainer *particleContainer)
{
  unsigned int i;
  unsigned int j;

  unsigned int numDimensions = particleContainer->_numDimensions;
  unsigned int numParticles = particleContainer->_numParticles;

  double invSqrDistanceMean = particleContainer->_particleStats->_distanceInvSqrMean;

  Error error;

  double invSqrDistanceVarianceSum = 0.0;
  double invSqrDistanceParticle = 0.0;
  double invSqrDistanceParticleSum = 0.0;

  Particle *p;
  Particle *q;
  
  for (i = 0; i < numParticles; i++)
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
      invSqrDistanceVarianceSum += invSqrDistanceParticleSum / (numParticles - 1);
    }

  particleContainer->_particleStats->_distanceInvSqrVariance = invSqrDistanceVarianceSum / numParticles;

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
