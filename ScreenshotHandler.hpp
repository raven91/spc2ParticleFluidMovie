//
// Created by Nikita Kruk on 2019-03-05.
//

#ifndef SPC2PARTICLEFLUIDMOVIE_SCREENSHOTHANDLER_HPP
#define SPC2PARTICLEFLUIDMOVIE_SCREENSHOTHANDLER_HPP

#include "Definitions.hpp"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sstream>

extern "C"
{
#include <png.h>
}

//#define SAVE_WITH_ALPHA_CHANNEL

class ScreenshotHandler
{
 public:

  ScreenshotHandler();
  ~ScreenshotHandler();

  void TakeScreenshotPpm(int width, int height);
  void TakeScreenshotPng(unsigned int width, unsigned int height, int image_index);

};

#endif //SPC2PARTICLEFLUIDMOVIE_SCREENSHOTHANDLER_HPP
