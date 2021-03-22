#include "ParameterContainer.hpp"
#include "SimulationModel.hpp"
#include "Renderer.hpp"

int main(int argc, const char *argv[])
{
  ParameterContainer parameter_container;
  SimulationModel simulation_model(&parameter_container);
  Renderer renderer(&simulation_model, &parameter_container);
  renderer.Start();

  return 0;
}