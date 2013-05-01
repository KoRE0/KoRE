/*
  Copyright (c) 2012 The KoRE Project

  This file is part of KoRE.

  KoRE is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  KoRE is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with KoRE.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "KoRE/ShaderInput.h"

kore::ShaderInput::ShaderInput(void)
  : type(GL_NONE),
  size(1),
  texUnit(KORE_GLUINT_HANDLE_INVALID),
  location(KORE_GLINT_HANDLE_INVALID),
  name("UNDEFINED"),
  programHandle(KORE_GLUINT_HANDLE_INVALID),
  shader(NULL){
}

bool kore::ShaderInput::isSamplerType(void) {
  switch (type) {
  case GL_SAMPLER_1D:
  case GL_SAMPLER_2D:
  case GL_SAMPLER_3D:
  case GL_SAMPLER_CUBE:
  case GL_SAMPLER_1D_SHADOW:
  case GL_SAMPLER_2D_SHADOW:
  case GL_SAMPLER_CUBE_SHADOW:
  case GL_SAMPLER_1D_ARRAY:
  case GL_SAMPLER_2D_ARRAY:
  case GL_SAMPLER_1D_ARRAY_SHADOW:
  case GL_SAMPLER_2D_ARRAY_SHADOW:
  case GL_SAMPLER_2D_MULTISAMPLE:
  case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
  case GL_SAMPLER_BUFFER:
  case GL_SAMPLER_2D_RECT:
  case GL_SAMPLER_2D_RECT_SHADOW:
  case GL_INT_SAMPLER_1D:
  case GL_INT_SAMPLER_2D:
  case GL_INT_SAMPLER_3D:
  case GL_INT_SAMPLER_CUBE:
  case GL_INT_SAMPLER_1D_ARRAY:
  case GL_INT_SAMPLER_2D_ARRAY:
  case GL_INT_SAMPLER_2D_MULTISAMPLE:
  case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
  case GL_INT_SAMPLER_BUFFER:
  case GL_INT_SAMPLER_2D_RECT:
  case GL_UNSIGNED_INT_SAMPLER_1D:
  case GL_UNSIGNED_INT_SAMPLER_2D:
  case GL_UNSIGNED_INT_SAMPLER_3D:
  case GL_UNSIGNED_INT_SAMPLER_CUBE:
  case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
  case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
  case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
  case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
  case GL_UNSIGNED_INT_SAMPLER_BUFFER:
  case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
    return true;
  default:
    return false;
  }
}

bool kore::ShaderInput::isImageType(void) {
  switch (type) {
  case GL_IMAGE_1D: 
  case GL_IMAGE_2D: 
  case GL_IMAGE_3D: 
  case GL_IMAGE_2D_RECT: 
  case GL_IMAGE_CUBE: 
  case GL_IMAGE_BUFFER: 
  case GL_IMAGE_1D_ARRAY: 
  case GL_IMAGE_2D_ARRAY: 
  case GL_IMAGE_2D_MULTISAMPLE: 
  case GL_IMAGE_2D_MULTISAMPLE_ARRAY: 
  case GL_INT_IMAGE_1D: 
  case GL_INT_IMAGE_2D: 
  case GL_INT_IMAGE_3D: 
  case GL_INT_IMAGE_2D_RECT: 
  case GL_INT_IMAGE_CUBE: 
  case GL_INT_IMAGE_BUFFER: 
  case GL_INT_IMAGE_1D_ARRAY: 
  case GL_INT_IMAGE_2D_ARRAY: 
  case GL_INT_IMAGE_2D_MULTISAMPLE: 
  case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY: 
  case GL_UNSIGNED_INT_IMAGE_1D: 
  case GL_UNSIGNED_INT_IMAGE_2D: 
  case GL_UNSIGNED_INT_IMAGE_3D: 
  case GL_UNSIGNED_INT_IMAGE_2D_RECT: 
  case GL_UNSIGNED_INT_IMAGE_CUBE: 
  case GL_UNSIGNED_INT_IMAGE_BUFFER: 
  case GL_UNSIGNED_INT_IMAGE_1D_ARRAY: 
  case GL_UNSIGNED_INT_IMAGE_2D_ARRAY: 
  case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE: 
  case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
    return true;
  default:
    return false;
  }
}

bool kore::ShaderInput::isAtomicCounterType(void) {
  return type == GL_UNSIGNED_INT_ATOMIC_COUNTER;
}
