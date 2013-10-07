#ifndef STATISTICS_H
#define STATISTICS_H

#include "particle.h"
#include "error.h"

Error pGenStatistics(ParticleContainer *particleContainer);
Error pCalcPositionMean(ParticleContainer *particleContainer);
Error pCalcPositionVariance(ParticleContainer *particleContainer);
Error pCalcDistanceMean(ParticleContainer *particleContainer);
Error pCalcDistanceVariance(ParticleContainer *particleContainer);
Error pCalcDistanceInvSqrMean(ParticleContainer *particleContainer);
Error pCalcDistanceInvSqrVariance(ParticleContainer *particleContainer);

void pPrintStatistics(ParticleContainer *particleContainer);

#endif
