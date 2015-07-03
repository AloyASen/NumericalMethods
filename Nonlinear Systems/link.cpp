#include <iostream>
#include <cmath>
#include "radians.h"
#include "iterative.h"
#include "newton.h"

using namespace std;

class Link {
protected:
  const double alpha = deg_to_rad(40.0);
public:
  double f(double x) {
    return (5.0/3.0)*cos(this->alpha)-(5.0/2.0)*cos(x)+(11.0/6.0)-cos(this->alpha-x);
  }
};

class Iterative_Link: public Link, public Iterative<double> {
public:
  Iterative_Link(double a, double b, double e) : Iterative(a, b, e) {};
  double f(double x) {
    return Link::f(x);
  }
};

class Newton_Link: public Link, public Newton<double> {
public:
  Newton_Link(double initial_guess, double e) : Newton(initial_guess, e) {};
  double f(double x) {
    return Link::f(x);
  }
  double df(double x) {
    return (5.0/2.0)*sin(x) - sin(this->alpha-x);
  }
};


int main() {
  double a = deg_to_rad(30.0);
  double b = deg_to_rad(40.0);
  double e = .000001;
  cout.precision(dbl::digits10);

  Iterative_Link il = Iterative_Link(a, b, e);
  cout << "Bisection: " << rad_to_deg(il.iterate_bisection()) << endl;
  cout << "False Position: " << rad_to_deg(il.iterate_false_position()) << endl;
  cout << "Secant: " << rad_to_deg(il.iterate_secant()) << endl;

  Newton_Link nl = Newton_Link(a, e);
  cout << "Newton: " << rad_to_deg(nl.iterate()) << endl;

  return 0;
}
