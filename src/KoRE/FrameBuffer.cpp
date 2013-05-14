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

#include "KoRE/FrameBuffer.h"
#include "KoRE/RenderManager.h"
#include "KoRE/Log.h"
#include "KoRE/GLerror.h"
#include "KoRE/ResourceManager.h"
#include "KoRE/IDManager.h"
#include <algorithm>

// Create the backbuffer as a static const pointer.
const kore::FrameBuffer* kore::FrameBuffer::BACKBUFFER = new kore::FrameBuffer(0);

kore::FrameBuffer::FrameBuffer(const std::string& name)
: _name(name),
  _handle(KORE_GLUINT_HANDLE_INVALID),
  kore::BaseResource() {
  glGenFramebuffers(1, &_handle);
}

// Private constructor - only for internal use!
kore::FrameBuffer::FrameBuffer(GLuint handle)
  : _name("BACKBUFFER"),
    _handle(handle),
    kore::BaseResource() {
  ResourceManager::getInstance()->addFramebuffer(this);
}

kore::FrameBuffer::~FrameBuffer(void) {
  destroy();
}

void kore::FrameBuffer::setName(const std::string& name) {
  if (this == kore::FrameBuffer::BACKBUFFER
    || name == kore::FrameBuffer::BACKBUFFER->getName()) {
    return;
  }
  _name = name;
}

void kore::FrameBuffer::destroy() {
  if (_handle == KORE_GLUINT_HANDLE_INVALID
      || _handle == 0) {
        return;
  }

  glDeleteFramebuffers(1, &_handle);
  _handle = 0;

  // Maybe we want to use the Textures elsewhere,
  // or they are bound to another FBO
  /* for (uint i = 0; i < _textures.size(); ++i) {
    ResourceManager::getInstance()->removeTexture(_textures[i]);
  }*/
  _textures.clear();
  for (uint i = 0; i < _textureInfos.size(); ++i) {
    KORE_SAFE_DELETE(_textureInfos[i]);
  }

  _textureOutputs.clear();
  _textureInfos.clear();
}

void kore::FrameBuffer::addTextureAttachment(const Texture* tex,
                                             GLuint attatchment) {
  // check if we have a valid FrameBuffer
  if (!tex || _handle == 0 || _handle == KORE_GLUINT_HANDLE_INVALID) {
    return;
  }

  // check if attachment is already bound, clear for overwrite
  for (uint i = 0; i<_activeBuffers.size(); i++) {
    if (attatchment == _activeBuffers[i]) {
      _textures.erase(_textures.begin()+i);
      _textureInfos.erase(_textureInfos.begin()+i);
      _textureOutputs.erase(_textureOutputs.begin()+i);
      _activeBuffers.erase(_activeBuffers.begin()+i);
      break;
    }
  }

  if (std::find(_textures.begin(), _textures.end(), tex) != _textures.end()) {
    Log::getInstance()
      ->write("[ERROR] '%s' : Cannot attach '%s', Texture already attached!\n",
              _name.c_str(), tex->getName().c_str());
    return;
  }

  kore::RenderManager::getInstance()->bindFrameBuffer(GL_FRAMEBUFFER, _handle);
  kore::RenderManager::getInstance()
    ->bindTexture(tex->getProperties().targetType, _handle);

  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         attatchment,
                         tex->getProperties().targetType,
                         tex->getHandle(), 0);
  _textures.push_back(tex);

  _activeBuffers.push_back(attatchment);

  STextureInfo* texInfo = new STextureInfo;
  texInfo->texLocation = tex->getHandle();
  texInfo->texTarget = tex->getProperties().targetType;
  texInfo->internalFormat = tex->getProperties().internalFormat;
  _textureInfos.push_back(texInfo);

  ShaderData textureData;
  textureData.name = tex->getName();
  textureData.type =
    TextureSampler::getSamplerTypeFromTexType(tex->getProperties().targetType);
  textureData.data = texInfo;
  _textureOutputs.push_back(textureData);
}

void kore::FrameBuffer::
      addTextureAttachment(const STextureProperties& properties,
                           const std::string& name,
                           const GLuint attatchment ) {
  if (_handle == 0 || _handle == KORE_GLUINT_HANDLE_INVALID) {
    return;
  }

  Texture* pTex = new Texture;
  bool bSuccess = pTex->create(properties, name);
  if (bSuccess) {
    ResourceManager::getInstance()->addTexture(pTex);
    addTextureAttachment(pTex, attatchment);
  } else {
    Log::getInstance()->write("[ERROR] Requested Texture could not be"
                              "created for the FBO '%s'", _name.c_str());
    KORE_SAFE_DELETE(pTex);
  }
}

const kore::Texture*
  kore::FrameBuffer::getTexture(const std::string& name) const {
    for(uint i = 0; i < _textures.size(); ++i) {
      if (_textures[i]->getName() == name) {
        return _textures[i];
      }
    }
    return NULL;
}

bool kore::FrameBuffer::checkFBOcompleteness() {
  if (_handle == KORE_GLUINT_HANDLE_INVALID) {
    return false;
  }
  RenderManager::getInstance()->bindFrameBuffer(GL_FRAMEBUFFER, _handle);
  return GLerror::gl_ValidateFBO(_name);
}