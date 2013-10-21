#include "particle.h"

#include <stdlib.h>
#include <math.h>

Error pCreateParticles(ParticleContainer **particleContainer, unsigned int numParticles, Shape shape, double radius)
{
  *particleContainer = (ParticleContainer *) malloc(sizeof(ParticleContainer));

  (*particleContainer)->_numParticles = numParticles;
  (*particleContainer)->_shape = shape;
  (*particleContainer)->_radius = radius;
  (*particleContainer)->_particleStats = NULL;
  
  if (((*particleContainer)->_particles = (Particle *) malloc(sizeof(Particle) * (*particleContainer)->_numParticles)) == NULL)
    {
      return MEMORY_ERROR;
    }

  pPlaceUniform(*particleContainer);
  
  return NO_ERROR;
}

Error pPlaceUniform(ParticleContainer *particleContainer)
{
  Error error;
  switch (particleContainer->_shape)
    {
    case DISK:
      particleContainer->_numDimensions = 2;
      error = pPlaceUniformDisk(particleContainer);
      break;
    case SQUARE:
      particleContainer->_numDimensions = 2;
      error = pPlaceUniformSquare(particleContainer);
      break;
    }
  return error;
}

Error pPlaceUniformDisk(ParticleContainer *particleContainer)
{
  Particle *p;

  unsigned int numParticles = particleContainer->_numParticles;
  double radius = particleContainer->_radius;
  
  unsigned int i;
  for (i=0; i < numParticles; i++)
    {
      p = &(particleContainer->_particles[i]);
      
      /* Allocate 2 points since a disk is 2 Dimentional */
      if ((p->_position = malloc(sizeof(double) * 2)) == NULL)
	{
	  return MEMORY_ERROR;
	}

      /* To generate points uniformly within a disk a special transormation
         that takes into account the shrinking perimiter of each r
         see https://mathworld.wolfram.com/DiskPointPicking for more info*/
      double theta = 2 * PI * drand48();  /* 0 .. 2 PI */
      double r =  drand48();	          /* 0 .. 1 */
      
      p->_position[0] = sqrt(r * radius) * cos(theta);
      p->_position[1] = sqrt(r * radius) * sin(theta);
    }
  return NO_ERROR;
}

Error pPlaceUniformSquare(ParticleContainer *particleContainer)
{
  Particle *p;
  
  unsigned int numParticles = particleContainer->_numParticles;
  double radius = particleContainer->_radius;
  
  unsigned int i;
  for (i=0; i < numParticles; i++)
    {
      p = &(particleContainer->_particles[i]);
      
      /* Allocate 2 points since a disk is 2 Dimentional */
      if ((p->_position = malloc(sizeof(double) * 2)) == NULL)
	{
	  return MEMORY_ERROR;
	}

      /* Center [0, 1, 0, 1] move -> [-0.5, 0.5, -0.5, 0.5]
         [-0.5, 0.5, -0.5, 0.5] scale by (2.0 * radius) */
      double x = drand48();	/* 0 ... 1 */
      double y = drand48();	/* 0 ... 1 */

      p->_position[0] = 2.0 * radius * (x - 0.5);
      p->_position[1] = 2.0 * radius * (y - 0.5);
    }
  return NO_ERROR;
}

Error pDistance(Particle *p, Particle *q, unsigned int numDimensions, double *distance)
{
  unsigned int i;
  *distance = 0.0;
  
  for (i = 0; i<numDimensions; i++)
    {
      *distance += pow((p->_position[i] - q->_position[i]), 2);
    }
  *distance =  sqrt(*distance);

  return NO_ERROR;
}

Error pInverseSquareDistance(Particle *p, Particle *q, unsigned int numDimensions, double *invSqrDistance)
{
  pDistance(p, q, numDimensions, invSqrDistance);

  if (*invSqrDistance == 0.0)
    {
      return DIVIDE_BY_ZERO_ERROR;
    }
    
  *invSqrDistance = 1.0 / (*invSqrDistance * *invSqrDistance);

  return NO_ERROR;
}
  
