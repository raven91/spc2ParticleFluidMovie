//
// Created by Nikita Kruk on 2019-03-05.
//

#ifndef SPC2PARTICLEFLUIDMOVIE_PARAMETERCONTAINER_HPP
#define SPC2PARTICLEFLUIDMOVIE_PARAMETERCONTAINER_HPP

#include "Definitions.hpp"

#include <GLEW/glew.h>

#include <string>

class ParameterContainer
{
 public:

  ParameterContainer();
  ~ParameterContainer();

  int GetNumberOfParticles();
  int GetNumberOfParticleStateVariables();
  int GetN();
  int GetM();
  int GetL();
  int GetNumberOfCells();
  int GetNumberOfCellStateVariables();
  const std::string &GetSimulationFileName();
  int GetDtRecip();
  GLfloat GetXSize();
  GLfloat GetXRsize();
  GLfloat GetYSize();
  GLfloat GetYRSize();
  GLfloat GetPhiSize();
  GLfloat GetPhiRSize();
  GLfloat GetDx();
  GLfloat GetDy();
  GLfloat GetDphi();
  GLfloat GetDifferentialVolume();

 private:

  std::string simulation_file_name_;
  int number_of_particles_;
  int number_of_particle_state_variables_;
  int n_;
  int m_;
  int l_;
  int number_of_cell_state_variables_;
  int dt_recip_;

  GLfloat x_size_;
  GLfloat y_size_;
  GLfloat x_rsize_;
  GLfloat y_rsize_;
  GLfloat phi_size_;
  GLfloat phi_rsize_;
  GLfloat dx_;
  GLfloat dy_;
  GLfloat dphi_;

};

#endif //SPC2PARTICLEFLUIDMOVIE_PARAMETERCONTAINER_HPP
