#include "ProjectLoader.h"

#include <tinyxml/tinyxml.h>
#include <tinyxml/tinystr.h>
#include <string>
#include <time.h>
#include <map>

#include "KoRE/ResourceManager.h"
#include "KoRE/SceneManager.h"
#include "KoRE/RenderManager.h"
#include "KoRE/Log.h"

kore::ProjectLoader* kore::ProjectLoader::getInstance() {
  static ProjectLoader instance;
  return &instance;
}

void kore::ProjectLoader::loadProject(const std::string& path) {
  kore::Log::getInstance()->write("[Debug] Loading '%s'\n", path.c_str());
  // loading resources
  // loading scenegraph
  // loading renderflow
}

void kore::ProjectLoader::saveProject(const std::string& path) {
  ResourceManager* ResMgr = ResourceManager::getInstance();

  TiXmlDocument doc;
  TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "yes");
  doc.LinkEndChild(decl);

  TiXmlComment * comment = new TiXmlComment();
  time_t rawtime;
  time(&rawtime);
  comment->SetValue(ctime(&rawtime));
  doc.LinkEndChild(comment);

  // Resources
  TiXmlElement* resources = new TiXmlElement("Resources");
  doc.LinkEndChild(resources);

  // Textures
  TiXmlElement* texture;
  for(auto texIt = ResMgr->_textures.begin();
      texIt != ResMgr->_textures.end();
      texIt++) {
    texture = new TiXmlElement("Texture");
    STextureProperties prop = texIt->second->getProperties();
    texture->SetAttribute("name", texIt->second->getName().c_str());
    texture->SetAttribute("width", prop.width);
    texture->SetAttribute("height", prop.height);
    resources->LinkEndChild(texture);
  }
  // Meshes

  // TODO(dospelt) the rest

  TiXmlElement* scene = new TiXmlElement("Scene");
  kore::SceneNode* root = kore::SceneManager::getInstance()->getRootNode();
  saveSceneNode(scene, root);
  doc.LinkEndChild(scene);

  // finally, save to file
  if(doc.SaveFile(path.c_str())) {
    kore::Log::getInstance()->write("[DEBUG] writing file '%s'\n",
                                    path.c_str());
  } else {
    kore::Log::getInstance()->write("[ERROR] could not write file '%s'\n",
                                    path.c_str());
  }

  // TODO(dospelt) runtime error when deleting created pointers.
  // it seems they get automatically deleted when saving File -> tinyxmlDoku?

  // delete resources;
  // delete comment;
}

void kore::ProjectLoader::saveSceneNode(TiXmlElement* parent,
                                        kore::SceneNode* node) {
  TiXmlElement* scenenode = new TiXmlElement("Node");
  scenenode->SetAttribute("ID", node->getID());
  scenenode->SetAttribute("Name", node->getName().c_str());
  node->getComponents();
  //for (uint);
  std::vector<kore::SceneNode*> children = node->getChildren();
  for (uint i = 0; i < children.size(); i++) {
    saveSceneNode(scenenode, children[i]);
  }
  parent->LinkEndChild(scenenode);
}
