/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/
#ifndef COUPLEDFUNCTIONAUX_H
#define COUPLEDFUNCTIONAUX_H

#include "AuxKernel.h"


//Forward Declarations
class CoupledFunctionAux;

template<>
InputParameters validParams<CoupledFunctionAux>();

/**
 * Function auxiliary value
 */
class CoupledFunctionAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  CoupledFunctionAux(const InputParameters & parameters);


protected:
  virtual Real computeValue();

  const VariableValue & _coupled_val;

  Real _value;
};

#endif // COUPLEDFUNCTIONAUX_H
