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

#include "KoRE/Operations/DrawIndirectOp.h"
#include "KoRE/ShaderProgram.h"
#include "KoRE/RenderManager.h"

kore::DrawIndirectOp::DrawIndirectOp() : _mode(0), _bufOffset(0) {
    _type = OP_DRAWINDIRECT;
}

kore::DrawIndirectOp::
  DrawIndirectOp(const GLenum mode, const GLuint bufOffset)
  : _mode(0), _bufOffset(0) {
    _type = OP_DRAWINDIRECT;
    connect(mode, bufOffset);
}

kore::DrawIndirectOp::~DrawIndirectOp() {
}

void kore::DrawIndirectOp::update(void) {
}

void kore::DrawIndirectOp::reset(void) {
}

bool kore::DrawIndirectOp::isValid() const {
  return true;
}

bool kore::DrawIndirectOp::dependsOn(const void* thing) const {
  return true;
}

void kore::DrawIndirectOp::doExecute() const {
 glDrawArraysIndirect(_mode, (void*)_bufOffset);
}

void kore::DrawIndirectOp::connect(const GLenum mode, const GLuint bufOffset) {
  _mode = mode;
  _bufOffset = bufOffset;
}
