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


#include "ElementIntegralGradPostprocessor.h"

template<>
InputParameters validParams<ElementIntegralGradPostprocessor>()
{
  InputParameters params = validParams<ElementIntegralVariablePostprocessor>();
  return params;
}

ElementIntegralGradPostprocessor::ElementIntegralGradPostprocessor(const std::string & name, InputParameters parameters) :
    ElementIntegralVariablePostprocessor(name, parameters)
{}
  

Real
ElementIntegralGradPostprocessor::computeQpIntegral()
{
  return (_grad_u[_qp]*_grad_u[_qp]);
}

