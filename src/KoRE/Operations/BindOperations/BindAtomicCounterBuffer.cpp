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

#include "KoRE/Operations/BindOperations/BindAtomicCounterBuffer.h"

#include "KoRE/ShaderProgram.h"
#include "KoRE/RenderManager.h"
#include "KoRE/IndexedBuffer.h"


kore::BindAtomicCounterBuffer::BindAtomicCounterBuffer() {
  _type = OP_BINDATOMICCOUNTERBUFFER;
}

kore::BindAtomicCounterBuffer::
  BindAtomicCounterBuffer(const ShaderData* data, const ShaderInput* shaderInput) {
  connect(data, shaderInput);
  _type = OP_BINDATOMICCOUNTERBUFFER;
}

kore::BindAtomicCounterBuffer::~BindAtomicCounterBuffer() {
}

void kore::BindAtomicCounterBuffer::update(void) {
}

void kore::BindAtomicCounterBuffer::reset(void) {
}

void kore::BindAtomicCounterBuffer::doExecute() const {
  uint bindingPoint = _shaderUniform->atomicCounterBindingPoint;
  IndexedBuffer* acBuffer =
    static_cast<IndexedBuffer*>(_componentUniform->data);

  if (acBuffer) {
    _renderManager
      ->bindBufferBase(GL_ATOMIC_COUNTER_BUFFER,
                       bindingPoint,
                       acBuffer->getHandle());
  }
}

void kore::BindAtomicCounterBuffer::connect(const ShaderData* data,
                                            const ShaderInput* shaderInput) {
  if (!data || !shaderInput) {
    // Make invalid
    _shaderUniform = NULL;
    _componentUniform = NULL;
  }

  _shaderUniform = shaderInput;
  _componentUniform = data;
}
