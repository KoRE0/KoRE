
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

#include "KoRE/Operations/ClearOp.h"
#include "KoRE/GLerror.h"
#include "KoRE/Log.h"
#include "KoRE/RenderManager.h"

kore::ClearOp::ClearOp() :
    kore::Operation() {
  _type = OP_CLEAR;
  _clearcolor = glm::vec4(0,0,0,1);
  _clear_bit = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT;
}

kore::ClearOp::ClearOp(bool color,
                       bool depth,
                       bool stencil,
                       glm::vec4 clearcolor) :
                       _clearcolor(clearcolor),
                       kore::Operation() {
  _type = OP_CLEAR;
  _clear_bit = 0;
  if (color) _clear_bit = _clear_bit | GL_COLOR_BUFFER_BIT;
  if (depth) _clear_bit = _clear_bit | GL_DEPTH_BUFFER_BIT;
  if (stencil) _clear_bit = _clear_bit | GL_STENCIL_BUFFER_BIT;
}

kore::ClearOp::~ClearOp() {
}

void kore::ClearOp::doExecute(void) const {
  if (_clear_bit != 0) {
    glClearColor(_clearcolor.x,
                 _clearcolor.y,
                 _clearcolor.z,
                 _clearcolor.w);
    glClear(_clear_bit);
  }
}

void kore::ClearOp::update(void) {
}

void kore::ClearOp::reset(void) {
}

bool kore::ClearOp::dependsOn(const void* thing) const {
  return false;
}

bool kore::ClearOp::isValid(void) const {
  return true;
}

void kore::ClearOp::connect(bool color,
                            bool depth,
                            bool stencil,
                            glm::vec4 clearcolor) {
  _clearcolor = clearcolor;
  _clear_bit = 0;
  if (color) _clear_bit = _clear_bit | GL_COLOR_BUFFER_BIT;
  if (depth) _clear_bit = _clear_bit | GL_DEPTH_BUFFER_BIT;
  if (stencil) _clear_bit = _clear_bit | GL_STENCIL_BUFFER_BIT;
}
