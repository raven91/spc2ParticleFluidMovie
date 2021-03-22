//
// Created by Nikita Kruk on 2019-03-05.
//

#include "SimulationModel.hpp"

#include <string>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <cmath>

SimulationModel::SimulationModel(ParameterContainer *parameter_container) :
    parameter_container_(parameter_container),
    t_(0.0),
    particle_system_state_(),
    continuum_system_state_(),
    colors_(),
    indexes_(),
    number_of_particles_(parameter_container->GetNumberOfParticles()),
    number_of_particle_state_variables_(parameter_container->GetNumberOfParticleStateVariables()),
    number_of_cells_(parameter_container->GetNumberOfCells()),
    number_of_cell_state_variables_(parameter_container->GetNumberOfCellStateVariables())
{
  simulation_file_.open(parameter_container->GetSimulationFileName(), std::ios::binary | std::ios::in);
  assert(simulation_file_.is_open());
  particle_system_state_.resize(number_of_particle_state_variables_ * number_of_particles_, 0.0f);
  continuum_system_state_.resize(number_of_cell_state_variables_ * number_of_cells_, 0.0f);

  for (int i = 0; i < parameter_container_->GetN(); ++i)
  {
    for (int j = 0; j < parameter_container_->GetM(); ++j)
    {
      for (int k = 0; k < parameter_container_->GetL(); ++k)
      {
        int idx_cur = 0;
        ThreeDimIdxToOneDimIdx(i, j, k, idx_cur);
        continuum_system_state_[number_of_cell_state_variables_ * idx_cur] =
            GLfloat((i + 0.5) * parameter_container_->GetDx()); // x : left to right
        continuum_system_state_[number_of_cell_state_variables_ * idx_cur + 1] =
            GLfloat(
                (parameter_container_->GetM() - j - 1 + 0.5) * parameter_container_->GetDy());  // y : into the screen
        continuum_system_state_[number_of_cell_state_variables_ * idx_cur + 2] =
            GLfloat((k + 0.5) * parameter_container_->GetDphi()); // phi : bottom to top
        continuum_system_state_[number_of_cell_state_variables_ * idx_cur + 3] = 0.0;
      } // k
    } // j
  } // i
}

SimulationModel::~SimulationModel()
{
  simulation_file_.close();
}

void SimulationModel::ReadNewState()
{
  Real t = 0.0f;
//  std::vector<Real> system_state(number_of_particles_ * number_of_particle_state_variables_, 0.0);
  simulation_file_.read((char *) &t, sizeof(Real));
  t_ = t;
  simulation_file_.read((char *) &particle_system_state_[0],
                        number_of_particles_ * number_of_particle_state_variables_ * sizeof(Real));

  std::vector<Real> density(number_of_cells_, 0.0);
  for (int i = 0; i < number_of_particles_; ++i)
  {
    Real x_i = particle_system_state_[number_of_particle_state_variables_ * i];
    x_i -= std::floor(x_i * parameter_container_->GetXRsize()) * parameter_container_->GetXSize();
    Real y_i = particle_system_state_[number_of_particle_state_variables_ * i + 1];
    y_i -= std::floor(y_i * parameter_container_->GetYRSize()) * parameter_container_->GetYSize();
    Real phi_i = particle_system_state_[number_of_particle_state_variables_ * i + 2];
    phi_i -= std::floor(phi_i * parameter_container_->GetPhiRSize()) * parameter_container_->GetPhiSize();

    int cell_idx_x = int(x_i / parameter_container_->GetXSize() * parameter_container_->GetN());
    int cell_idx_y = int(y_i / parameter_container_->GetYSize() * parameter_container_->GetM());
    int cell_idx_phi = int(phi_i / parameter_container_->GetPhiSize() * parameter_container_->GetL());
    int cell_idx = 0;
    ThreeDimIdxToOneDimIdx(cell_idx_x, cell_idx_y, cell_idx_phi, cell_idx);
    density[cell_idx] += 1.0 / (number_of_particles_ * parameter_container_->GetDifferentialVolume());
  } // i
  std::cout << "system density: "
            << std::accumulate(density.begin(), density.end(), 0.0) * parameter_container_->GetDifferentialVolume()
            << std::endl;

  FindMinmaxDensity(density);
  std::cout << "min:" << min_density_ << ", max:" << max_density_ << std::endl;

  for (int idx_cur = 0; idx_cur < density.size(); ++idx_cur)
  {
    continuum_system_state_[number_of_cell_state_variables_ * idx_cur + 3] =
        NormalizedValue(density[idx_cur], min_density_, max_density_);
  }

  std::cout << "t:" << t << std::endl;
}

void SimulationModel::SkipTimeUnits(int t, int delta_t_recip)
{
  simulation_file_.seekg(
      int(t * delta_t_recip) * (1l + number_of_particle_state_variables_ * number_of_particles_) * sizeof(Real),
      std::ios::cur);
}

void SimulationModel::FindMinmaxDensity(const std::vector<Real> &density)
{
  std::pair<std::vector<Real>::const_iterator, std::vector<Real>::const_iterator>
      min_max = std::minmax_element(density.begin(), density.end());
  min_density_ = *min_max.first;
  max_density_ = *min_max.second;

//  std::vector<Real>::const_iterator second_max_iter;
//  Real second_max = 0.0;
//  for (std::vector<Real>::const_iterator cit = density.begin(); cit != density.end(); ++cit)
//  {
//    if (cit != min_max.second)
//    {
//      if (*cit > second_max)
//      {
//        second_max = *cit;
//        second_max_iter = cit;
//      }
//    }
//  } // cit
//  max_density_ = second_max;
//  max_density_ *= 0.01;
}

GLfloat SimulationModel::GetCurrentTime()
{
  return t_;
}

const std::vector<GLfloat> &SimulationModel::GetContinuumSystemState()
{
  return continuum_system_state_;
}

const std::map<int, std::vector<GLfloat>> &SimulationModel::GetColors()
{
  return colors_;
}

const std::vector<int> &SimulationModel::GetIndexes()
{
  return indexes_;
}

void SimulationModel::ThreeDimIdxToOneDimIdx(int x, int y, int phi, int &idx)
{
  // the winding order is x->y->phi
//    idx = x + kN * (y + kM * phi);
  // the winding order is phi->x->y
  idx = phi + parameter_container_->GetL() * (x + parameter_container_->GetN() * y);
}

void SimulationModel::OneDimIdxToThreeDimIdx(int idx, int &x, int &y, int &phi)
{
  // the winding order is x->y->phi
//    phi = idx / (kN * kM);
//    y = (idx % (kN * kM)) / kN;
//    x = idx % kN;
  // the winding order is phi->x->y
  y = idx / (parameter_container_->GetL() * parameter_container_->GetN());
  x = (idx % (parameter_container_->GetL() * parameter_container_->GetN())) / parameter_container_->GetL();
  phi = idx % parameter_container_->GetL();
}

template<typename T>
T SimulationModel::NormalizedValue(T value, T min, T max)
{
  return (value - min) / (max - min);
//  return value;
}