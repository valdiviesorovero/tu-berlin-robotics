#include "SpringDamperMass.hpp"

// TODO Define your methods here
SpringDamperMass::SpringDamperMass(double pos_init, double vel_init, double pos_eqm, double vel_eqm, double _damping_coeff) 
: SpringMass(pos_init, vel_init, pos_eqm, vel_eqm), damping_coeff(_damping_coeff), init_state({pos_init, vel_init}) 
{
  this->t=0;
  this->simDataSpringDamperMass.push_back(this->init_state);
}

SpringDamperMass::~SpringDamperMass() {}

// TODO SpringMass simulation step
int SpringDamperMass::step() 
{
  this->next_state.y = (1 - (this->damping_coeff / SpringMass::MASS))*this->vel_init - (SpringMass::SPRING_CONST / SpringMass::MASS)*(this->pos_init - this->pos_eqm);

  this->next_state.x = this->pos_init + this->next_state.y;

  this->simDataSpringDamperMass.push_back(this->next_state);
  
  this->vel_init = this->next_state.y;

  this->pos_init = this->next_state.x;

  this->t++;
  
  if (this->t == 500) 
  {
    std::ofstream file("simDataSpringDamperMass.csv");
    file << "x,y\n";
    for (int i = 0; i < 501; ++i) 
    {
      file << simDataSpringDamperMass[i].x << "," << simDataSpringDamperMass[i].y << "\n";
    }
  }

  return this->t;
}

bool SpringDamperMass::getConfiguration(int t, Vec2d& state) const 
{
  if (t > this->t) {
    return false;
  }
  state=this->simDataSpringDamperMass[t];
  return true;
}

