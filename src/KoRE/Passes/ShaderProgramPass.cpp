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

#include "KoRE/Passes/ShaderProgrampass.h"
#include "KoRE/Operations/UseShaderProgram.h"
#include "KoRE/Log.h"


kore::ShaderProgramPass::ShaderProgramPass(void)
  : _program(NULL) {
}

kore::ShaderProgramPass::ShaderProgramPass(const ShaderProgram* prog)
  : _program(NULL) {
  setShaderProgram(prog);
}

kore::ShaderProgramPass::~ShaderProgramPass(void) {
  for (uint i = 0; i < _startupOperations.size(); ++i) {
    KORE_SAFE_DELETE(_startupOperations[i]);
  }

  for (uint i = 0; i < _nodePasses.size(); ++i) {
    KORE_SAFE_DELETE(_nodePasses[i]);
  }
}

void kore::ShaderProgramPass::setShaderProgram(const ShaderProgram* program) {
  if (_program == program) return;
  if (_program != NULL) {
    for (uint i = 0; i < _startupOperations.size(); ++i) {
      KORE_SAFE_DELETE(_startupOperations[i]);
    }
    _startupOperations.clear();
  }

  _program = program;

  UseShaderProgram* pUseProgram = new UseShaderProgram;
  pUseProgram->connect(program);

  _startupOperations.push_back(pUseProgram);
}

void kore::ShaderProgramPass::addNodePass(NodePass* pass) {
  if (std::find(_nodePasses.begin(), _nodePasses.end(), pass)
      != _nodePasses.end()) {
    return;
  }
  _nodePasses.push_back(pass);
}

void kore::ShaderProgramPass::removeNodePass(NodePass* pass) {
  auto it = std::find(_nodePasses.begin(), _nodePasses.end(), pass);
  if (it == _nodePasses.end()) {
      return;
  } else {
    _nodePasses.erase(it);
  }
}

void kore::ShaderProgramPass
  ::swapNodePass(NodePass* which, NodePass* towhere) {
  auto it = std::find(_nodePasses.begin(), _nodePasses.end(), which);
  auto it2 = std::find(_nodePasses.begin(), _nodePasses.end(), towhere);
  if(it != _nodePasses.end() && it2 != _nodePasses.end()) {
  std::iter_swap(it, it2);
  }
}
