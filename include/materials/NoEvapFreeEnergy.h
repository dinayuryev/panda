/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef NOEVAPFREEENERGY_H
#define NOEVAPFREEENERGY_H

#include "DerivativeFunctionMaterialBase.h"

//Forward Declarations
class NoEvapFreeEnergy;

template<>
InputParameters validParams<NoEvapFreeEnergy>();

/**
 * Material class that creates a piecewise free energy with supressed evaporation and its derivatives
 * for use with CHParsed and SplitCHParsed. F = .
 */
class NoEvapFreeEnergy : public DerivativeFunctionMaterialBase
{
public:
  NoEvapFreeEnergy(const InputParameters & parameters);

protected:
  virtual Real computeF();
  virtual Real computeDF(unsigned int j_var);
  virtual Real computeD2F(unsigned int j_var, unsigned int k_var);

private:
  /// Coupled variable value for the concentration \f$ \c \f$.
  VariableValue & _c;
  unsigned int _c_var;
};

#endif //NOEVAPFREEENERGY_H
