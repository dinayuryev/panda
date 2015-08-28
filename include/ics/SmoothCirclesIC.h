#ifndef SMOOTHCIRCLESIC_H
#define SMOOTHCIRCLESIC_H

#include "Kernel.h"
#include "SmoothCircleBaseIC.h"

#include <string>
// create a user specified number of smooth circular grains IC

class SmoothCirclesIC;

template<>
InputParameters validParams<SmoothCirclesIC>();

class SmoothCirclesIC : public SmoothCircleBaseIC
{
public:

  SmoothCirclesIC(const InputParameters & parameters);


  virtual void computeCircleRadii();

  virtual void computeCircleCenters();

protected:

  unsigned int _numbub;
  unsigned int _numrows;
  Real _bubspac;
  Real _x1;
  Real _y1;
  Real _z1;
  Real _z2;
  Real _radius;
  
};

#endif //SMOOTHCIRCLESIC_H
