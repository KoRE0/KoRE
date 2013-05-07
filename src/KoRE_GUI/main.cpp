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

/************************************************************************/
/* \author Dominik Ospelt                                               */
/************************************************************************/

#include <GL/glew.h>
#include <QApplication>
#include <QMainWindow>
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCommonStyle>

#include "KoRE/SceneManager.h"
#include "KoRE/ResourceManager.h"
#include "KoRE/RenderManager.h"

#include "KoRE/Components/TexturesComponent.h"

#include "KoRE_GUI/SceneViewer.h"
#include "KoRE_GUI/RenderViewer.h"
#include "KoRE_GUI/ResourceViewer.h"
#include "KoRE_GUI/OperationFlow.h"
#include "KoRE_GUI/GLWidget.h"
#include "KoRE_GUI/MainWidget.h"

int main(int argc, char *argv[]) {
  // initialize Qt
  QApplication app(argc, argv);

  //MainWidget* editor = new MainWidget();
  //editor->show();

  // need of GL-Context
  GLWidget* win = new GLWidget;

  // now  other widgets
  koregui::RenderViewer* rview = new koregui::RenderViewer;
  koregui::ResourceViewer* resview = new koregui::ResourceViewer;
  koregui::OperationFlow* oview = new koregui::OperationFlow;
  koregui::SceneViewer* sview = new koregui::SceneViewer(rview);

  /*QWidget* central = new QWidget;
  QTabWidget* tab = new QTabWidget;
  tab->addTab(rview, "RenderView");
  tab->addTab(sview, "SceneViewe");


  QHBoxLayout* hbox = new QHBoxLayout;
  hbox->setMargin(0);
  hbox->setSpacing(0);
  hbox->addWidget(tab);
  hbox->addWidget(win);
 
  QVBoxLayout* vbox = new QVBoxLayout;
  vbox->setMargin(0);
  vbox->setSpacing(0);
  vbox->addLayout(hbox);
  vbox->addWidget(oview);

  central->setLayout(vbox);
  central->show();*/

  win->show();
  sview->show();
  rview->show();

  // demo startup loading
  kore::ResourceManager::getInstance()->loadScene("./assets/meshes/cube.dae");
  std::vector<kore::SceneNode*> cube;
  kore::SceneManager::getInstance()->getSceneNodesByName("Cube", cube);
  kore::Texture* tex = kore::ResourceManager::getInstance()->loadTexture("./assets/textures/checkerboard.png");
  kore::Texture* tex2 = kore::ResourceManager::getInstance()->loadTexture("./assets/textures/stonewall.png");
  kore::TexturesComponent* pTexComponent = new kore::TexturesComponent;
  pTexComponent->addTexture(tex);
  pTexComponent->addTexture(tex2);
  cube[0]->addComponent(pTexComponent);
  kore::SceneManager::getInstance()->update();
  sview->showScene(kore::SceneManager::getInstance()->getRootNode());

  return app.exec();
}
