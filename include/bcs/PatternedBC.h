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

#ifndef PATTERNEDBC_H
#define PATTERNEDBC_H

#include "IntegratedBC.h"


//Forward Declarations
class PatternedBC;


template<>
InputParameters validParams<PatternedBC>();

/**
 * Boundary condition of a Robin style whose value and type (Dirichlet or Neumann) depends on position
 */
class PatternedBC : public IntegratedBC
{
public:
  PatternedBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  /// The wetting angle used for the Neumann condition
  const Real & _value;
};

#endif // PATTERNEDBC_H
