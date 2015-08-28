
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

#include "GrowthFunctionAux.h"
#include "Function.h"

template<>
InputParameters validParams<GrowthFunctionAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addParam<Real>("value", 0.0, "Scalar value used for our auxiliary calculation");
  params.addRequiredCoupledVar("coupled", "Coupled variable");
  params.addRequiredParam<FunctionName>("function", "The function to use as the value");
  return params;
}

GrowthFunctionAux::GrowthFunctionAux(const InputParameters & parameters) :
    AuxKernel(parameters),


    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _coupled_val(coupledValue("coupled")),

 // Set our member scalar value from InputParameters (read from the input file)
    _value(getParam<Real>("value")),

    _func(getFunction("function"))
{
}

/**
 * Auxiliary Kernels override computeValue() instead of computeQpResidual().  Aux Variables
 * are calculated either one per elemenet or one per node depending on whether we declare
 * them as "Elemental (Constant Monomial)" or "Nodal (First Lagrange)".  No changes to the
 * source are necessary to switch from one type or the other.
 */
Real
GrowthFunctionAux::computeValue()
{
  return (1+_value * _func.value(_t, _q_point[_qp])) * (_coupled_val[_qp] + 1) - 1 ;
}

