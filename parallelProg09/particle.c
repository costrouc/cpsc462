#include "particle.h"

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

Error pCreateParticleContainer(ParticleContainer **particleContainer)
{
  if ((*particleContainer = (ParticleContainer *) malloc(sizeof(ParticleContainer))) == NULL)
    {
      return MEMORY_ERROR;
    }

  return NO_ERROR;
}

Error pInitializeParticleContainer(ParticleContainer *particleContainer, unsigned int numParticles, Shape shape, double radius)
{
  particleContainer->_numParticles = numParticles;
    
  particleContainer->_shape = shape;
  particleContainer->_radius = radius;
  particleContainer->_particles = NULL;
  particleContainer->_particleStats = NULL;

  switch (particleContainer->_shape)
    {
    case DISK:
      particleContainer->_numDimensions = 2;
      break;
    case SQUARE:
      particleContainer->_numDimensions = 2;
      break;
    }
  
  pCreateParticles(particleContainer);
  
  return NO_ERROR;
}

Error pCreateParticles(ParticleContainer *particleContainer)
{
  if ((particleContainer->_particles = (Particle *) malloc(sizeof(Particle) * particleContainer->_numParticles)) == NULL)
    {
      return MEMORY_ERROR;
    }

  return NO_ERROR;
}

Error pInitializeParticles(ParticleContainer *particleContainer)
{
  pPlaceUniform(particleContainer);
  
  return NO_ERROR;
}

Error pSyncParticles(ParticleContainer *particleContainer)
{
  MPI_Datatype ParticleContainerMPI;
  int PCCount = 3;
  
  //Assemble and distribute particle container data

  int PCBlocks[] = {2, 1, 1};
  MPI_Datatype PCTypes[] = {MPI_UNSIGNED, MPI_INT, MPI_DOUBLE};
  MPI_Aint PCDisplacements[] = {0, 8, 12};
  
  MPI_Type_create_struct(PCCount, PCBlocks, PCDisplacements, PCTypes, &ParticleContainerMPI);
  MPI_Type_commit(&ParticleContainerMPI);

  MPI_Bcast(particleContainer, 1 , ParticleContainerMPI, 0, MPI_COMM_WORLD);

  MPI_Type_free(&ParticleContainerMPI);

  //Assemble and distribute particle data

  MPI_Datatype ParticleMPI;
  int PCount = 1;

  int PBlocks[]  = {3};
  MPI_Datatype PTypes[] = {MPI_DOUBLE};
  MPI_Aint PDisplacements[] = {0};
  
  MPI_Type_create_struct(PCount, PBlocks, PDisplacements, PTypes, &ParticleMPI);
  MPI_Type_commit(&ParticleMPI);
  
  MPI_Bcast(particleContainer->_particles, particleContainer->_numParticles, ParticleMPI, 0, MPI_COMM_WORLD);

  MPI_Type_free(&ParticleMPI);
  
  return NO_ERROR;
}

Error pPlaceUniform(ParticleContainer *particleContainer)
{
  Error error;
  switch (particleContainer->_shape)
    {
    case DISK:
      error = pPlaceUniformDisk(particleContainer);
      break;
    case SQUARE:
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

      /* To generate points uniformly within a disk a special transormation
         that takes into account the shrinking perimiter of each r
         see https://mathworld.wolfram.com/DiskPointPicking for more info*/
      double theta = 2 * PI * drand48();  /* 0 .. 2 PI */
      double r =  drand48();	          /* 0 .. 1 */
      
      p->_position[0] = radius * sqrt(r) * cos(theta);
      p->_position[1] = radius * sqrt(r) * sin(theta);
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
      
      /* Center [0, 1, 0, 1] move -> [-0.5, 0.5, -0.5, 0.5]
         [-0.5, 0.5, -0.5, 0.5] scale by (2.0 * radius) */
      double x = drand48();	/* 0 ... 1 */
      double y = drand48();	/* 0 ... 1 */

      p->_position[0] = 2.0 * radius * (x - 0.5);
      p->_position[1] = 2.0 * radius * (y - 0.5);
    }
  return NO_ERROR;
}

Error pPrintParticleContainer(ParticleContainer *particleContainer)
{
  printf("Particle Container:\n");
  printf("numParticles: %u\n", particleContainer->_numParticles);
  printf("numDimensions: %u\n", particleContainer->_numDimensions);

  printf("shape: ");
  switch (particleContainer->_shape)
    {
    case DISK:
      printf("disk\n");
      break;
    case SQUARE:
      printf("square\n");
      break;
    }
  
  printf("radius: %f\n", particleContainer->_radius);

  pPrintParticles(particleContainer->_particles, particleContainer->_numParticles);

  return NO_ERROR;
}

Error pPrintParticles(Particle *particles, unsigned int numParticles)
{
  printf("Particles:\n");

  int i;
  for (i=0; i<numParticles; i++)
    {
      printf("%d: x - %2.2f y - %2.2f\n", i, particles[i]._position[0], particles[i]._position[1]);
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
  
