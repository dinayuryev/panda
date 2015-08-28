#ifndef ENERGYCOUPLEDAUX_H
#define ENERGYCOUPLEDAUX_H

#include "AuxKernel.h"


//Forward Declarations
class EnergyCoupledAux;

template<>
InputParameters validParams<EnergyCoupledAux>();

/**
 * Function auxiliary value
 */
class EnergyCoupledAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  EnergyCoupledAux(const InputParameters & parameters);


protected:
  virtual Real computeValue();

  VariableValue & _coupled_val;

};

#endif // ENERGYCOUPLEDAUX_H

