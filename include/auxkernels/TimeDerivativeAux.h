#ifndef TIMEDERIVATIVEAUX_H
#define TIMEDERIVATIVEAUX_H

#include "AuxKernel.h"


//Forward Declarations
class TimeDerivativeAux;

template<>
InputParameters validParams<TimeDerivativeAux>();

/**
 * Function auxiliary value
 */
class TimeDerivativeAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  TimeDerivativeAux(const InputParameters & parameters);


protected:
  virtual Real computeValue();

virtual ~TimeDerivativeAux();
};

#endif // TIMEDERIVATIVEAUX_H

