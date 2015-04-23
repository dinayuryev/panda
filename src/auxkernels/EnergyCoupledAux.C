#include "EnergyCoupledAux.h"


template<>
InputParameters validParams<EnergyCoupledAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("coupled", "Coupled variable");
  return params;
}

EnergyCoupledAux::EnergyCoupledAux(const std::string & name, InputParameters parameters) :
    AuxKernel(name, parameters),


    // We can couple in a value from one of our kernels with a call to coupledValueAux
    _coupled_val(coupledValue("coupled"))
{
}

/**
 * Auxiliary Kernels override computeValue() instead of computeQpResidual().  Aux Variables
 * are calculated either one per elemenet or one per node depending on whether we declare
 * them as "Elemental (Constant Monomial)" or "Nodal (First Lagrange)".  No changes to the
 * source are necessary to switch from one type or the other.
 */
Real
EnergyCoupledAux::computeValue()
{
  return (_coupled_val[_qp]) * (_coupled_val[_qp]) * (_coupled_val[_qp]) * (_coupled_val[_qp]) * (_coupled_val[_qp])/4 - (_coupled_val[_qp]) * (_coupled_val[_qp]) * (_coupled_val[_qp])/2 ;
}


