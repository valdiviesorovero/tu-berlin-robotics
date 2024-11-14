#include "SpringMass.hpp"

// define gravity constant
const double SpringMass::GRAVITY = 10;
const double SpringMass::SPRING_CONST = 7;
const double SpringMass::MASS = 30;

// TODO SpringMass constructor and destructor
SpringMass::SpringMass(double pos_init, double vel_init, double pos_eqm, double vel_eqm) 
: pos_init(pos_init), vel_init(vel_init), pos_eqm(pos_eqm), vel_eqm(vel_eqm), init_state({pos_init, vel_init}) 
{
  this->t = 0;
  this->simDataSpringMass.push_back(this->init_state);
}

SpringMass::~SpringMass() {}

// TODO SpringMass simulation step
int SpringMass::step() 
{
  this->next_state.y = this->vel_init - (SpringMass::SPRING_CONST / SpringMass::MASS)*(this->pos_init - this->pos_eqm);

  this->next_state.x = this->pos_init + this->next_state.y;
  
  this->simDataSpringMass.push_back(this->next_state);

  this->vel_init = this->next_state.y;

  this->pos_init = this->next_state.x;

  this->t++;

  if (this->t == 500) 
  {
    std::ofstream file("simDataSpringMass.csv");
    file << "x,y\n";
    for (int i = 0; i < 501; ++i) 
    {
      file << simDataSpringMass[i].x << "," << simDataSpringMass[i].y << "\n";
    }
  }

  return this->t;
}

// TODO SpringMass configuration getter
bool SpringMass::getConfiguration(int t, Vec2d& state) const 
{
  if (t > this->t) {
    return false;
  }
  state=this->simDataSpringMass[t];
  return true;
}

// TODO SpringMass current simulation time getter
int SpringMass::getCurrentSimulationTime() const 
{
  return this->t;
}
