#include "MainWidget.h"

#include "KoRE_GUI/SceneViewer.h"
#include "KoRE_GUI/RenderViewer.h"
#include "KoRE_GUI/ResourceViewer.h"
#include "KoRE_GUI/OperationFlow.h"
#include "KoRE_GUI/GLWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
  

  /*// need of GL-Context
  ui.GL_view = new GLWidget;

  // now  other widgets
  ui.renderview = new koregui::RenderViewer;
  ui.flow = new koregui::OperationFlow;
  ui.sceneview = new koregui::SceneViewer(static_cast<koregui::RenderViewer*>(ui.renderview));*/
  ui.setupUi(this);
}

MainWidget::~MainWidget()
{

}
