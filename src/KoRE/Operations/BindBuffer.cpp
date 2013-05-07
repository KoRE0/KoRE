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

#include "KoRE/Operations/BindBuffer.h"

#include "KoRE/ShaderProgram.h"
#include "KoRE/RenderManager.h"
#include "KoRE/IndexedBuffer.h"


kore::BindBuffer::BindBuffer() : _buf(0), _bufTarget(0) {
    _type = OP_BINDBUFFER;
}

kore::BindBuffer::
  BindBuffer(const GLenum bufferTarget, const GLuint bufLoc)
    : _buf(0), _bufTarget(0) {
    _type = OP_BINDBUFFER;
    connect(bufferTarget, bufLoc);
}

kore::BindBuffer::~BindBuffer() {
}

void kore::BindBuffer::update(void) {
}

void kore::BindBuffer::reset(void) {
}

bool kore::BindBuffer::isValid() const {
  return true;;
}

bool kore::BindBuffer::dependsOn(const void* thing) const {
  return false;
}

void kore::BindBuffer::doExecute() const {
 if (_buf) {
   _renderManager->bindBuffer(_bufTarget, _buf);
 }
}

void kore::BindBuffer::connect(const GLenum bufferTarget, const GLuint bufLoc) {
  _bufTarget = bufferTarget;
  _buf = bufLoc;
}
