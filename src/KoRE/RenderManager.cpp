/*
  Copyright © 2012 The KoRE Project

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

#include <vector>
#include <algorithm>

#include "core/rendermanager.h"
#include "core/log.h"

kore::RenderManager* kore::RenderManager::getInstance(void) {
  static kore::RenderManager theInstance;
  return &theInstance;
}

kore::RenderManager::RenderManager(void) {
}

kore::RenderManager::~RenderManager(void) {
}

const glm::ivec2& kore::RenderManager::getRenderResolution() const {
    return _renderResolution;
}

void kore::RenderManager::
    setRenderResolution(const glm::ivec2& newResolution) {
    _renderResolution = newResolution;
    resolutionChanged();
}

void kore::RenderManager::renderFrame(void) {
    OperationList::const_iterator it;
    for (it = _operations.begin(); it != _operations.end(); ++it) {
        (*it)->execute();
    }
}

void kore::RenderManager::resolutionChanged() {
    // Update all resolution-dependant resources here
    // (e.g. GBuffer-Textures...)
}

void kore::RenderManager::addOperation(const OperationPtr& op) {
    if (!hasOperation(op)) {
       _operations.push_back(op);
    }
}

void kore::RenderManager::addOperation(const OperationPtr& op,
                                       const OperationPtr& targetOp,
                                       const EOpInsertPos insertPos) {
     if (!hasOperation(targetOp) || hasOperation(op)) {
            return;
     }

     OperationList::const_iterator it =
         std::find(_operations.begin(), _operations.end(), targetOp);

     switch (insertPos) {
     case INSERT_AFTER:
         _operations.insert(it, op);
         break;
     case INSERT_BEFORE:
         _operations.insert(--it, op);
         break;
     }
}

bool kore::RenderManager::hasOperation(const OperationPtr& op) {
    return std::find(_operations.begin(), _operations.end(), op) !=
                                                             _operations.end();
}
