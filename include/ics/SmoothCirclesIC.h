#ifndef SMOOTHCIRCLESIC_H
#define SMOOTHCIRCLESIC_H

#include "Kernel.h"
#include "InitialCondition.h"
#include "SmoothCircleIC.h"

#include <string>
// create a user specified number of smooth circular grains IC

class SmoothCirclesIC;

template<>
InputParameters validParams<SmoothCirclesIC>();

class SmoothCirclesIC : public SmoothCircleIC
{
public:

  SmoothCirclesIC(const std::string & name,
                       InputParameters parameters);

  virtual void initialSetup();

  virtual Real value(const Point & p);

  virtual RealGradient gradient(const Point & p);

protected:

  unsigned int _numbub;
  unsigned int _numrows;
  Real _bubspac;
  Real _z2;

 

  
 std::vector<Point> _bubcent;
  std::vector<Real> _bubradi;
};

#endif //SMOOTHCIRCLESIC_H
