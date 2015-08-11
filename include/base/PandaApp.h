#ifndef PANDAAPP_H
#define PANDAAPP_H

#include "MooseApp.h"

class PandaApp;

template<>
InputParameters validParams<PandaApp>();

class PandaApp : public MooseApp
{
public:
  PandaApp(InputParameters parameters);
  virtual ~PandaApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* PANDAAPP_H */
