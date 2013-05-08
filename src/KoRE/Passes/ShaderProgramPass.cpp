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

kore::ShaderProgramPass::ShaderProgramPass(ShaderProgram* prog)
  : _program(NULL) {
  setShaderProgram(prog);
}

kore::ShaderProgramPass::~ShaderProgramPass(void) {
  for (uint i = 0; i < _startupOperations.size(); ++i) {
    KORE_SAFE_DELETE(_startupOperations[i]);
  }
  for (uint i = 0; i < _internalStartup.size(); ++i) {
    KORE_SAFE_DELETE(_internalStartup[i]);
  }
  for (uint i = 0; i < _finishOperations.size(); ++i) {
    KORE_SAFE_DELETE(_finishOperations[i]);
  }
  for (uint i = 0; i < _internalFinish.size(); ++i) {
    KORE_SAFE_DELETE(_internalFinish[i]);
  }
  for (uint i = 0; i < _nodePasses.size(); ++i) {
    KORE_SAFE_DELETE(_nodePasses[i]);
  }
}

void kore::ShaderProgramPass::setShaderProgram(ShaderProgram* program) {
  if (_program == program) return;
  if (_program != NULL) {
    for (uint i = 0; i < _internalStartup.size(); ++i) {
      KORE_SAFE_DELETE(_internalStartup[i]);
    }
    _internalStartup.clear();
    _internalFinish.clear();
  }

  _program = program;

  UseShaderProgram* pUseProgram = new UseShaderProgram;
  pUseProgram->connect(program);

  _internalStartup.push_back(pUseProgram);
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

void kore::ShaderProgramPass::addStartupOperation(Operation* op) {
  if (std::find(_startupOperations.begin(), _startupOperations.end(), op)
    != _startupOperations.end()) {
      return;
  }
  _startupOperations.push_back(op);
}

void kore::ShaderProgramPass::removeStartupOperation(Operation* op) {
  auto it = std::find(_startupOperations.begin(), _startupOperations.end(), op);
  if(it != _startupOperations.end()) {
    _startupOperations.erase(it);
  }
}

void kore::ShaderProgramPass::addFinishOperation(Operation* op) {
  if (std::find(_finishOperations.begin(), _finishOperations.end(), op)
    != _finishOperations.end()) {
      return;
  }
  _finishOperations.push_back(op);
}

void kore::ShaderProgramPass::removeFinishOperation(Operation* op) {
  auto it = std::find(_finishOperations.begin(), _finishOperations.end(), op);
  if(it != _finishOperations.end()) {
    _finishOperations.erase(it);
  }
}
