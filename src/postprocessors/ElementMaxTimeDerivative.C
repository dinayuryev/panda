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

#include "ElementMaxTimeDerivative.h"

#include <algorithm>
#include <limits>

template<>
InputParameters validParams<ElementMaxTimeDerivative>()
{

  // Define the parameters
  InputParameters params = validParams<ElementVariablePostprocessor>();

  return params;
}

ElementMaxTimeDerivative::ElementMaxTimeDerivative(const InputParameters & parameters):ElementVariablePostprocessor(parameters),
  _value(-std::numeric_limits<Real>::max())
{}

void
ElementMaxTimeDerivative::initialize()
{
  _value = -std::numeric_limits<Real>::max();
}

void
ElementMaxTimeDerivative::computeQpValue()
{
_value = std::max(_value, _u_dot[_qp]);
}

Real
ElementMaxTimeDerivative::getValue()
{
  gatherMax(_value);
  return _value;
}

void
ElementMaxTimeDerivative::threadJoin(const UserObject & y)
{
  const ElementMaxTimeDerivative & pps = static_cast<const ElementMaxTimeDerivative &>(y);
      _value = std::max(_value, pps._value);
}




