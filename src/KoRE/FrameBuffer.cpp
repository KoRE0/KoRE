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
<<<<<<< HEAD

// Create the backbuffer as a static const sharedptr.
const kore::FrameBuffer kore::FrameBuffer::BACKBUFFER(0);

kore::FrameBuffer::FrameBuffer(void)
: _handle(KORE_GLUINT_HANDLE_INVALID) {

=======
#include "KoRE/ResourceManager.h"
#include "KoRE/IDManager.h"
#include <algorithm>

// Create the backbuffer as a static const sharedptr.
const kore::FrameBuffer* kore::FrameBuffer::BACKBUFFER = new kore::FrameBuffer(0);

kore::FrameBuffer::FrameBuffer(const std::string& name)
: _name(name),
  _handle(KORE_GLUINT_HANDLE_INVALID), 
  kore::BaseResource() {
>>>>>>> hax
  glGenFramebuffers(1, &_handle);
}

// Private constructor - only for internal use!
kore::FrameBuffer::FrameBuffer(GLuint handle) {
<<<<<<< HEAD
  _handle = handle;
=======
  _name = "BACKBUFFER";
  _handle = handle;

  ResourceManager::getInstance()->addFramebuffer(this);
>>>>>>> hax
}

kore::FrameBuffer::~FrameBuffer(void) {
  destroy();
}

<<<<<<< HEAD
void kore::FrameBuffer::destroy() {
  glDeleteFramebuffers(1, &_handle);
  _handle = 0;

=======
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

  for (uint i = 0; i < _textures.size(); ++i) {
    ResourceManager::getInstance()->removeTexture(_textures[i]);
  }
  _textures.clear();

>>>>>>> hax
  for (uint i = 0; i < _textureInfos.size(); ++i) {
    KORE_SAFE_DELETE(_textureInfos[i]);
  }

  _textureOutputs.clear();
  _textureInfos.clear();
}

<<<<<<< HEAD
void kore::FrameBuffer::addTextureAttachment(const TexturePtr& tex,
=======
void kore::FrameBuffer::addTextureAttachment(const Texture* tex,
>>>>>>> hax
                                             GLuint attatchment) {
  if (_handle == 0 || _handle == KORE_GLUINT_HANDLE_INVALID) {
    return;
  }

  if (std::find(_textures.begin(), _textures.end(), tex) != _textures.end()) {
    return;
  }

  kore::RenderManager::getInstance()->bindFrameBuffer(GL_FRAMEBUFFER, _handle);
  kore::RenderManager::getInstance()->
                         bindTexture(tex->getProperties().targetType, _handle);

  glFramebufferTexture2D(GL_FRAMEBUFFER,
                         attatchment,
                         tex->getProperties().targetType,
                         tex->getHandle(), 0);
  _textures.push_back(tex);

<<<<<<< HEAD
  STextureInfo* texInfo = new STextureInfo;
  texInfo->texLocation = tex->getHandle();
  texInfo->texTarget = tex->getProperties().targetType;
=======


  STextureInfo* texInfo = new STextureInfo;
  texInfo->texLocation = tex->getHandle();
  texInfo->texTarget = tex->getProperties().targetType;
  texInfo->internalFormat = tex->getProperties().internalFormat;
>>>>>>> hax
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
<<<<<<< HEAD
  TexturePtr pTex(new Texture);
  bool bSuccess = pTex->create(properties, name);
  if (bSuccess) {
=======
  if (_handle == 0 || _handle == KORE_GLUINT_HANDLE_INVALID) {
    return;
  }

  Texture* pTex = new Texture;
  bool bSuccess = pTex->create(properties, name);
if (bSuccess) {
    ResourceManager::getInstance()->addTexture(pTex);
>>>>>>> hax
    addTextureAttachment(pTex, attatchment);
  } else {
    Log::getInstance()->write("[ERROR] Requested Texture could not be"
                              "created for the FBO");
<<<<<<< HEAD
  }
}

const kore::TexturePtr
=======
    KORE_SAFE_DELETE(pTex);
  }
}

const kore::Texture*
>>>>>>> hax
  kore::FrameBuffer::getTexture( const std::string& name ) const {
    for(uint i = 0; i < _textures.size(); ++i) {
      if (_textures[i]->getName() == name) {
        return _textures[i];
      }
    }

<<<<<<< HEAD
    return TexturePtr(NULL);
=======
    return NULL;
>>>>>>> hax
}

bool kore::FrameBuffer::checkFBOcompleteness() {
  if (_handle == KORE_GLUINT_HANDLE_INVALID) {
    return false;
  }

  RenderManager::getInstance()->bindFrameBuffer(GL_FRAMEBUFFER, _handle);
<<<<<<< HEAD
  return GLerror::gl_ValidateFBO("");
}
=======
  return GLerror::gl_ValidateFBO(_name);
}
>>>>>>> hax
