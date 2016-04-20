/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#include "NoEvapFreeEnergy.h"

template<>
InputParameters validParams<NoEvapFreeEnergy>()
{
  InputParameters params = validParams<DerivativeFunctionMaterialBase>();
  params.addClassDescription("Material that implements the math free energy and its derivatives: \nF = 1/4(1 + c)^2*(1 - c)^2");
  params.addRequiredCoupledVar("c","Concentration variable");
  return params;
}

NoEvapFreeEnergy::NoEvapFreeEnergy(const InputParameters &  parameters):DerivativeFunctionMaterialBase(parameters),
    _c(coupledValue("c")),
    _c_var(coupled("c"))
{
}

Real
NoEvapFreeEnergy::computeF()
{
  return 3.0/4.0*(1.0 + _c[_qp])*(1.0 + _c[_qp])*(1.0 - _c[_qp])*(1.0 - _c[_qp]);
}

Real
NoEvapFreeEnergy::computeDF(unsigned int j_var)
{
  if (j_var == _c_var) //Note that these checks are only really necessary when the material has more than one coupled variable
    return 3*_c[_qp]*(_c[_qp]*_c[_qp] - 1.0);
  else
    return 0.0;
}

Real
NoEvapFreeEnergy::computeD2F(unsigned int j_var, unsigned int k_var)
{
  if ( (j_var == _c_var) && (k_var == _c_var) )
    return 9*_c[_qp]*_c[_qp] - 1.0;
  else
    return 0.0;
}

