//
// Created by Nikita Kruk on 2019-03-05.
//

#include "ParameterContainer.hpp"

#include <cmath>

ParameterContainer::ParameterContainer() :
    number_of_particles_(50000),
    number_of_particle_state_variables_(3),
    n_(50),
    m_(50),
    l_(64),
    number_of_cell_state_variables_(4),
    dt_recip_(1),
    x_size_(1.0f),
    y_size_(1.0f),
    x_rsize_(1.0f / x_size_),
    y_rsize_(1.0f / y_size_),
    phi_size_(2.0f * M_PI),
    phi_rsize_(1.0f / phi_size_),
    dx_(x_size_ / n_),
    dy_(y_size_ / m_),
    dphi_(phi_size_ / l_)
{
//  std::string folder("/Users/nikita/Documents/Projects/spc2/spc2OdeIntegration/");
  std::string folder("/Volumes/Kruk/spc2/spc2OdeIntegration/continued/");
  simulation_file_name_ =
      folder + std::string("v0_0.01_sigma_1_rho_0.01_alpha_1.07_Dphi_0.145_N_")
          + std::to_string(number_of_particles_) + std::string("_0_0.bin");
}

ParameterContainer::~ParameterContainer()
{

}

int ParameterContainer::GetNumberOfParticles()
{
  return number_of_particles_;
}

int ParameterContainer::GetNumberOfParticleStateVariables()
{
  return number_of_particle_state_variables_;
}

int ParameterContainer::GetN()
{
  return n_;
}

int ParameterContainer::GetM()
{
  return m_;
}

int ParameterContainer::GetL()
{
  return l_;
}

int ParameterContainer::GetNumberOfCells()
{
  return n_ * m_ * l_;
}

int ParameterContainer::GetNumberOfCellStateVariables()
{
  return number_of_cell_state_variables_;
}

const std::string &ParameterContainer::GetSimulationFileName()
{
  return simulation_file_name_;
}

int ParameterContainer::GetDtRecip()
{
  return dt_recip_;
}

GLfloat ParameterContainer::GetXSize()
{
  return x_size_;
}

GLfloat ParameterContainer::GetXRsize()
{
  return x_rsize_;
}

GLfloat ParameterContainer::GetYSize()
{
  return y_size_;
}

GLfloat ParameterContainer::GetYRSize()
{
  return y_rsize_;
}

GLfloat ParameterContainer::GetPhiSize()
{
  return phi_size_;
}

GLfloat ParameterContainer::GetPhiRSize()
{
  return phi_rsize_;
}

GLfloat ParameterContainer::GetDx()
{
  return dx_;
}

GLfloat ParameterContainer::GetDy()
{
  return dy_;
}

GLfloat ParameterContainer::GetDphi()
{
  return dphi_;
}

GLfloat ParameterContainer::GetDifferentialVolume()
{
  return dx_ * dy_ * dphi_;
}