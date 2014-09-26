#include "SmoothCirclesIC.h"


template<>
InputParameters validParams<SmoothCirclesIC>()
{
  InputParameters params = validParams<SmoothCircleIC>();
  params.addRequiredParam<unsigned int>("numbub", "The number of bubbles to be placed on GB");
  params.addRequiredParam<Real>("bubspac", "minimum spacing of bubbles, measured from center to center");
  params.addParam<unsigned int>("numrows", 1, "The number of rows (1 or 2)");
  params.addRequiredParam<Real>("z2", "height of second row of bubbles");
  return params;
}

SmoothCirclesIC::SmoothCirclesIC(const std::string & name,
                                         InputParameters parameters) 
    :SmoothCircleIC(name, parameters),
    _numbub(getParam<unsigned int>("numbub")),
    _numrows(getParam<unsigned int>("numrows")),
    _bubspac(getParam<Real>("bubspac")),
    _z2(getParam<Real>("z2"))
{
}


void
SmoothCirclesIC::initialSetup()
{
if (_numrows == 1)
   {
  _bubcent.resize(_numbub);
  _bubradi.resize(_numbub);

  for (unsigned int i = 0; i < _numbub; i++)
  {
    _bubradi[i] = _radius;
    //Determine positions for each bubble

    Real rr = 0.0;
    Point newcenter = 0.0;

      newcenter(0) = _x1+i*_bubspac;
      newcenter(1) = _y1;

      if (_z1 != 0.0)
        newcenter(2) = _z1;

    _bubcent[i] = newcenter;
  }
}


else if (_numrows == 2)
{
  _bubcent.resize(2 * _numbub);
  _bubradi.resize(2 * _numbub);

for (unsigned int k = 0; k < 2; k++) 
{   Real ycor = _y1 + k * _z2;
  for (unsigned int i = 0; i < _numbub; i++)
  {
    _bubradi[i+ _numbub*k] = _radius;
    //Determine positions for each bubble

    Real rr = 0.0;
    Point newcenter = 0.0;

      newcenter(0) = _x1+i*_bubspac;
      newcenter(1) = ycor;

      if (_z1 != 0.0)
        newcenter(2) = _z1;

    _bubcent[i+_numbub*k] = newcenter;
  }
}
}
}

Real
SmoothCirclesIC::value(const Point & p)
{
  // if outvalue were larger than invalue, no bubbles would be generated
  Real val = _outvalue;
  Real val2 = 0.0;
if (_numrows == 1)
   {
for (unsigned int i = 0; i < _numbub && val < _invalue; i++)
{   _radius = _bubradi[i];
    _center = _bubcent[i];

    val2 = SmoothCircleIC::value(p);
    if (val2 > val) val = val2;
  }
}

if (_numrows == 2)
   {
for (unsigned int k = 0; k < 2; k++)
{
for (unsigned int i = 0; i < _numbub && val < _invalue; i++)
{   _radius = _bubradi[i + _numbub * k];
    _center = _bubcent[i + _numbub * k];

    val2 = SmoothCircleIC::value(p);
    if (val2 > val) val = val2;
  }
}
}

  return val;
}



RealGradient
SmoothCirclesIC::gradient(const Point & p)
{
  RealGradient grad = Gradient(0.0, 0.0, 0.0);
  Real val = _outvalue;
  Real val2 = 0.0;

if (_numrows == 1)
   {
  // iterate over all bubbles, or until we hit an interior point
  for (unsigned int i = 0; i < _numbub && val < _invalue; i++)
  {
    _radius = _bubradi[i];
    _center = _bubcent[i];

    val2 = SmoothCircleIC::value(p);
    if (val2 > val) {
      val = val2;
      grad = SmoothCircleIC::gradient(p);
    }
  }
}
if (_numrows == 2)
   {
for (unsigned int k = 0; k < 2; k++)
{
  // iterate over all bubbles, or until we hit an interior point
  for (unsigned int i = 0; i < _numbub && val < _invalue; i++)
  {
    _radius = _bubradi[i + _numbub * k];
    _center = _bubcent[i + _numbub * k];

    val2 = SmoothCircleIC::value(p);
    if (val2 > val) {
      val = val2;
      grad = SmoothCircleIC::gradient(p);
    }
}
  }
}

  return grad;
}
