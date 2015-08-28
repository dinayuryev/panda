#include "PandaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

#include "SmoothCirclesIC.h"
#include "WettingNeumannBC.h"
#include "CoupledFunctionAux.h"
#include "EnergyCoupledAux.h"
#include "ElementIntegralGradPostprocessor.h"
#include "PatternedBC.h"
#include "ElementMaxTimeDerivative.h"
#include "GrowthFunctionAux.h"
#include "WettingAngleNeumannBC.h"
#include "NoEvapFreeEnergy.h"
#include "LayerSingleDefectIC.h"
template<>
InputParameters validParams<PandaApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PandaApp::PandaApp(InputParameters parameters) :
    MooseApp(parameters)
{

  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  PandaApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  PandaApp::associateSyntax(_syntax, _action_factory);
}

PandaApp::~PandaApp()
{
}

void
PandaApp::registerApps()
{
  registerApp(PandaApp);
}

void
PandaApp::registerObjects(Factory & factory)
{
registerInitialCondition(SmoothCirclesIC);
registerInitialCondition(LayerSingleDefectIC);
registerBoundaryCondition(WettingNeumannBC);
registerBoundaryCondition(PatternedBC);
registerBoundaryCondition(WettingAngleNeumannBC);
registerAux(CoupledFunctionAux);
registerMaterial(NoEvapFreeEnergy);
registerAux(EnergyCoupledAux);
registerAux(GrowthFunctionAux);
registerPostprocessor(ElementIntegralGradPostprocessor);
registerPostprocessor(ElementMaxTimeDerivative);
}

void
PandaApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
