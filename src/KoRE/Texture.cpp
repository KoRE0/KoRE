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

#include "KoRE/Texture.h"
#include "KoRE/Log.h"
#include "KoRE/GLerror.h"
#include "KoRE/IDManager.h"

kore::Texture::Texture()
                    : _handle(KORE_GLUINT_HANDLE_INVALID),
                      _resourcepath(""),
                      kore::BaseResource() {
}

kore::Texture::~Texture() {
  destroy();
}

void kore::Texture::destroy() {
  if (_handle == KORE_GLUINT_HANDLE_INVALID) {
    return;
  }

  glDeleteTextures(1, &_handle);
  _handle = KORE_GLUINT_HANDLE_INVALID;
  _resourcepath = "";
  _properties = STextureProperties();
}

bool kore::Texture::init(const STextureProperties& properties,
                           const std::string& name,
                           const GLvoid* pixelData /*= NULL*/) {
  GLuint texTarget;

  if (properties.width > 0 && properties.height == 0 && properties.depth == 0 
    && properties.targetType == GL_TEXTURE_1D) {

    texTarget = GL_TEXTURE_1D;

  } else if (properties.width > 0 && properties.height > 0 
            && properties.depth == 0
            && properties.targetType == GL_TEXTURE_2D) {

    texTarget = GL_TEXTURE_2D;

  } else if (properties.width > 0 && properties.height > 0 &&
             properties.depth > 0 && properties.targetType == GL_TEXTURE_3D) {

    texTarget = GL_TEXTURE_3D;

  } else {
    Log::getInstance()
      ->write("[ERROR] '%s' : Invalid texture dimensions provided.\n",
              name.c_str());
    return false;
  }

  GLerror::gl_ErrorCheckStart();
  if(_handle != KORE_GLUINT_HANDLE_INVALID) {
    glGenTextures(1, &_handle);
  }

  glBindTexture(texTarget, _handle);
  
  switch(texTarget) {
  case GL_TEXTURE_1D:
    if (_handle != KORE_GLUINT_HANDLE_INVALID) {
      glTexImage1D(texTarget,
        0,
        _properties.internalFormat,
        _properties.width,
        _properties.border,
        _properties.format,
        _properties.pixelType,
        NULL);
    }
    glTexImage1D(texTarget,
      0,
      properties.internalFormat,
      properties.width,
      properties.border,
      properties.format,
      properties.pixelType,
      pixelData);
    break;
  case GL_TEXTURE_2D:
    if (_handle != KORE_GLUINT_HANDLE_INVALID) {
      glTexImage2D(texTarget,
        0,
        _properties.internalFormat,
        _properties.width,
        _properties.height,
        _properties.border,
        _properties.format,
        _properties.pixelType,
        NULL);
    }
    glTexImage2D(texTarget,
      0,
      properties.internalFormat,
      properties.width,
      properties.height,
      properties.border,
      properties.format,
      properties.pixelType,
      pixelData);
    break;
  case GL_TEXTURE_3D:
    if (_handle != KORE_GLUINT_HANDLE_INVALID) {
      glTexImage3D(texTarget,
        0,
        _properties.internalFormat,
        _properties.width,
        _properties.height,
        _properties.depth,
        _properties.border,
        _properties.format,
        _properties.pixelType,
        NULL);
    }
    glTexImage3D(texTarget,
      0,
      properties.internalFormat,
      properties.width,
      properties.height,
      properties.depth,
      properties.border,
      properties.format,
      properties.pixelType,
      pixelData);
    break;
  default:
    break;
  }

  glBindTexture(texTarget, 0);

  bool bSuccess = GLerror::gl_ErrorCheckFinish("Texture::init()");
  if (!bSuccess) {
    Log::getInstance()->write("[ERROR]:'%s' Texture could not be initialized!",
                              name.c_str());
    destroy();
    return false;
  }

  _resourcepath = name;
  _properties = properties;

  return true;
}

void kore::Texture::genMipmapHierarchy() {
  if (_handle != KORE_GLUINT_HANDLE_INVALID) {
    glBindTexture(_properties.targetType, _handle);
    glGenerateMipmap(_properties.targetType);
  }
}
