#ifndef PARTICLE_H
#define PARTICLE_H

#include "error.h"

#define PI 3.1415926535897932385

typedef struct
{
  unsigned int _id;
  char *_name;
} ParticleProperties;

typedef struct
{
  double *_positionMean;
  double *_positionVariance;
  double _distanceMean;
  double _distanceVariance;
  double _distanceInvSqrMean;
  double _distanceInvSqrVariance;

} ParticleStats;

typedef struct
{
  ParticleProperties *_properties;
  double *_position;
} Particle;

typedef enum
  {
    SQUARE,
    DISK
  } Shape;

typedef struct
{
  unsigned int _numParticles;
  unsigned int _numDimensions;
  Shape _shape;
  double _radius;
  
  Particle *_particles;
  ParticleStats *_particleStats;
} ParticleContainer;

Error pCreateParticles(ParticleContainer **particleContainer, unsigned int numParticles, Shape shape, double radius);

Error pPlaceUniform(ParticleContainer *particleContainer);
Error pPlaceUniformDisk(ParticleContainer *particleContainer);
Error pPlaceUniformSquare(ParticleContainer *particleContainer);

Error pDistance(Particle *p, Particle *q, unsigned int numDimensions, double *distance);
Error pInverseSquareDistance(Particle *p, Particle *q, unsigned int numDimensions, double *invSqrDistance);

#endif
