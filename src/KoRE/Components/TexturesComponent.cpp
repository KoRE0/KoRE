#include "KoRE/Components/TexturesComponent.h"
#include "KoRE/ResourceManager.h"
<<<<<<< HEAD
=======
#include <algorithm>
>>>>>>> hax

kore::TexturesComponent::TexturesComponent(void) {
}

kore::TexturesComponent::~TexturesComponent(void) {
  for (uint i = 0; i < _vTextureInfos.size(); ++i) {
    KORE_SAFE_DELETE(_vTextureInfos[i]);
  }
}

void kore::
<<<<<<< HEAD
  TexturesComponent::addTexture(TexturePtr tex,
=======
  TexturesComponent::addTexture(Texture* tex,
>>>>>>> hax
                                const bool useMipMaps /*=true*/,
                                const TextureSampler* sampler /*= NULL*/ ) {
  if (std::find(_vTextures.begin(),
                _vTextures.end(), tex) != _vTextures.end()) {
    return;
  }

  STextureInfo* texInfo = new STextureInfo;
  texInfo->texLocation = tex->getHandle();
  texInfo->texTarget = tex->getProperties().targetType;
<<<<<<< HEAD
=======
  texInfo->internalFormat = tex->getProperties().internalFormat;
>>>>>>> hax
  _vTextureInfos.push_back(texInfo);

  ShaderData shaderdata;
  shaderdata.type = GL_TEXTURE;
  shaderdata.name = tex->getName();
  shaderdata.data = texInfo;
  shaderdata.component = this;
  _shaderData.push_back(shaderdata);
  // Tex unit is defined by shader
}
