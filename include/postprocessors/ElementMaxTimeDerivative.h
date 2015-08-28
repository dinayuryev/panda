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

#ifndef ELEMENTMAXTIMEDERIVATIVE_H
#define ELEMENTMAXTIMEDERIVATIVE_H

#include "ElementVariablePostprocessor.h"

//Forward Declarations
class ElementMaxTimeDerivative;

// Input parameters
template<>
InputParameters validParams<ElementMaxTimeDerivative>();

/// A postprocessor for collecting the max time derivative value

class ElementMaxTimeDerivative : public ElementVariablePostprocessor
{
public:
  ElementMaxTimeDerivative(const InputParameters & parameters);
  virtual void initialize();
  virtual Real getValue();
  virtual void threadJoin(const UserObject & y);

protected:
  /// Get the extreme value at each quadrature point
  virtual void computeQpValue();

  /// The extreme value
  Real _value;
};

#endif
