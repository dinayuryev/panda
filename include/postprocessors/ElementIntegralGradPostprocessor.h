#ifndef ELEMENTINTEGRALGRADPOSTPROCESSOR_H
#define ELEMENTINTEGRALGRADPOSTPROCESSOR_H

#include "ElementIntegralVariablePostprocessor.h"
#include "MooseVariableInterface.h"

//Forward Declarations
class ElementIntegralGradPostprocessor;

template<>
InputParameters validParams<ElementIntegralGradPostprocessor>();

/**
 * This postprocessor computes a volume integral of the specified variable.
 *
 * Note that specializations of this integral are possible by deriving from this
 * class and overriding computeQpIntegral().
 */
class ElementIntegralGradPostprocessor :
  public ElementIntegralVariablePostprocessor
{
public:
  ElementIntegralGradPostprocessor(const InputParameters & parameters);

protected:
  virtual Real computeQpIntegral();

};

#endif

