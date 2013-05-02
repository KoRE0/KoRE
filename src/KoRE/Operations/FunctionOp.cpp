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

#include "KoRE/Operations/FunctionOp.h"

#include "KoRE/ShaderProgram.h"
#include "KoRE/RenderManager.h"
#include "KoRE/IndexedBuffer.h"


kore::FunctionOp::FunctionOp() : _function(nullptr) {
    _type = OP_FUNCTION;
}

kore::FunctionOp::
  FunctionOp(FuncT function) : _function(nullptr) {
    _type = OP_FUNCTION;
    connect(function);
}

kore::FunctionOp::~FunctionOp() {
}

void kore::FunctionOp::update(void) {
}

void kore::FunctionOp::reset(void) {
}

bool kore::FunctionOp::isValid() const {
  // Has a bool-operator overloaded
  return _function;
}

bool kore::FunctionOp::dependsOn(const void* thing) const {
  return thing == _function.target<void>();
}

void kore::FunctionOp::doExecute() const {
 if (_function) {
   _function();
 }
}

void kore::FunctionOp::connect(FuncT function) {
  _function = function;
}
