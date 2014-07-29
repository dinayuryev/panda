#include "PandaApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"

template<>
InputParameters validParams<PandaApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

PandaApp::PandaApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

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
}

void
PandaApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
