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
#ifndef GROWTHFUNCTIONAUX_H
#define GROWTHFUNCTIONAUX_H

#include "AuxKernel.h"
#include "Function.h"

//Forward Declarations
class GrowthFunctionAux;

template<>
InputParameters validParams<GrowthFunctionAux>();

/**
 * Function auxiliary value
 */
class GrowthFunctionAux : public AuxKernel
{
public:
  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  GrowthFunctionAux(const InputParameters & parameters);

  virtual ~GrowthFunctionAux() {}

protected:
  virtual Real computeValue();

  VariableValue & _coupled_val;


  Real _value;

  Function & _func;

};

#endif // GROWTHFUNCTIONAUX_H
