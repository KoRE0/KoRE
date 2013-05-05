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


kore::BindBuffer::BindBuffer() : _buf(NULL), _bufTarget(0) {
    _type = OP_BINDBUFFER;
}

kore::BindBuffer::
  BindBuffer(const GLenum bufferTarget, const IndexedBuffer* buf)
    : _buf(NULL), _bufTarget(0) {
    _type = OP_BINDBUFFER;
    connect(bufferTarget, buf);
}

kore::BindBuffer::~BindBuffer() {
}

void kore::BindBuffer::update(void) {
}

void kore::BindBuffer::reset(void) {
}

bool kore::BindBuffer::isValid() const {
  // Has a bool-operator overloaded
  return _buf != NULL;
}

bool kore::BindBuffer::dependsOn(const void* thing) const {
  return thing == _buf;
}

void kore::BindBuffer::doExecute() const {
 if (_buf) {
   _renderManager->bindBuffer(_bufTarget, _buf->getHandle());
 }
}

void kore::BindBuffer::connect(const GLenum bufferTarget,
                               const IndexedBuffer* buf) {
  _bufTarget = bufferTarget;
  _buf = buf;
}
