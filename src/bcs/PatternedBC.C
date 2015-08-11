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

#include "PatternedBC.h"


template<>
InputParameters validParams<PatternedBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addParam<Real>("value", 0.0, "The cosine of the wetitng angle");
 
  return params;
}

PatternedBC::PatternedBC(const InputParameters & parameters) :
    IntegratedBC(parameters),
    _value(getParam<Real>("value"))
{
}

Real
PatternedBC::computeQpResidual()
{

	return -_test[_i][_qp] * _value * sqrt (_grad_u[_qp] * _grad_u[_qp]);
}

