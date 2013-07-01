
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

#include "KoRE/Operations/CullFaceOp.h"
#include "KoRE/GLerror.h"
#include "KoRE/Log.h"
#include "KoRE/RenderManager.h"

kore::CullFaceOp::CullFaceOp()
  : _face(GL_BACK),
    kore::Operation() {
  _type = OP_CULLFACE;
}

kore::CullFaceOp::CullFaceOp(const GLenum face)
 : kore::Operation() {
  _face = face;
  _type = OP_CULLFACE;
  connect(_face);
}

kore::CullFaceOp::~CullFaceOp() {
}

void kore::CullFaceOp::connect(const GLenum face) {
  _face = _face;
}

void kore::CullFaceOp::doExecute(void) const {
  _renderManager->setCullFace(_face);
}

void kore::CullFaceOp::update(void) {
}

void kore::CullFaceOp::reset(void) {
}

bool kore::CullFaceOp::dependsOn(const void* thing) const {
  return false;
}

bool kore::CullFaceOp::isValid(void) const {
  return true;
}
