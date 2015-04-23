#include "SmoothCirclesIC.h"


template<>
InputParameters validParams<SmoothCirclesIC>()
{
  InputParameters params = validParams<SmoothCircleBaseIC>();
  params.addRequiredParam<unsigned int>("numbub", "The number of bubbles to be placed on GB");
  params.addRequiredParam<Real>("bubspac", "minimum spacing of bubbles, measured from center to center");
  params.addParam<unsigned int>("numrows", 1, "The number of rows (1 or 2)");
  params.addRequiredParam<Real>("x1", "x coordinate of row of bubbles");
  params.addRequiredParam<Real>("y1", "y coordinate of row of bubbles");
  params.addParam<Real>("z1", 0.0, "z coordinate of row of bub");
  params.addParam<Real>("z2",0.0, "height of second row of bubbles");
  params.addRequiredParam<Real>("radius", "radius of bubbles");
  return params;
}

SmoothCirclesIC::SmoothCirclesIC(const std::string & name,
                                         InputParameters parameters) 
    :SmoothCircleBaseIC(name, parameters),
    _numbub(getParam<unsigned int>("numbub")),
    _numrows(getParam<unsigned int>("numrows")),
    _bubspac(getParam<Real>("bubspac")),
    _x1(parameters.get<Real>("x1")),
    _y1(parameters.get<Real>("y1")),
    _z1(parameters.get<Real>("z1")),
    _z2(getParam<Real>("z2")),
    _radius(parameters.get<Real>("radius"))   

{
}




void
SmoothCirclesIC::computeCircleRadii()

{
if (_numrows == 1)
   {
  _radii.resize(_numbub);

  for (unsigned int i = 0; i < _numbub; i++)
  {
 	_radii[i] = _radius;	
  }
}

if (_numrows == 2)
{
  _radii.resize(2 * _numbub);

for (unsigned int k = 0; k < 2; k++)
{   Real ycor = _y1 + k * _z2;
  for (unsigned int i = 0; i < _numbub; i++)
  {
    _radii[i+ _numbub*k] = _radius;
}

}
}
}

void
SmoothCirclesIC::computeCircleCenters()
{
if (_numrows == 1)
   {
  _centers.resize(_numbub);


  for (unsigned int i = 0; i < _numbub; i++)
  {
    //Determine positions for each bubble

    Real rr = 0.0;
    Point newcenter = 0.0;

      newcenter(0) = _x1+i*_bubspac;
      newcenter(1) = _y1;

      if (_z1 != 0.0)
        newcenter(2) = _z1;

    _centers[i] = newcenter;
  }
}

else if (_numrows == 2)
{
  _centers.resize(2 * _numbub);

for (unsigned int k = 0; k < 2; k++) 
{   Real ycor = _y1 + k * _z2;
  for (unsigned int i = 0; i < _numbub; i++)
  {
    //Determine positions for each bubble

    Real rr = 0.0;
    Point newcenter = 0.0;

      newcenter(0) = _x1+i*_bubspac;
      newcenter(1) = ycor;

      if (_z1 != 0.0)
        newcenter(2) = _z1;

    _centers[i+_numbub*k] = newcenter;
  }
}
}
}


