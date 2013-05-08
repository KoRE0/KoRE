#include "KoRE_GUI/OperationFlow.h"

#include <QMouseEvent>

#include "KoRE_GUI/FlowItem.h"

#include "KoRE/RenderManager.h"

koregui::OperationFlow::OperationFlow(QWidget* parent)
                                    : QGraphicsView(parent) {
  setWindowTitle("OperationFlow");
  _scene.setBackgroundBrush(QBrush(QColor(23,23,23)));
  _scene.setParent(this);
  setScene(&_scene);
  setMinimumSize(800,200);
  setFixedHeight(200);
}

koregui::OperationFlow::~OperationFlow() {
  clearScene();
}

void koregui::OperationFlow::clearScene(void) {
  QList<QGraphicsItem*> sceneset = _scene.items();
  for (unsigned int i = 0; i < sceneset.size(); i++) {
    QGraphicsItem* itemPtr = sceneset[i];
    _scene.removeItem(itemPtr);
    delete(itemPtr);
  }
}

void koregui::OperationFlow::showFlow() {
  clearScene();
  std::vector<kore::FrameBufferStage*> &stages =
    kore::RenderManager::getInstance()->getFrameBufferStages();
  int stagewidth = 0;
  for (uint i = 0; i < stages.size(); i++) {
    koregui::FlowItem* stageit = new koregui::FlowItem(FLOW_FRAMEBUFFERSTAGE);
    stageit->setFrameBufferStage(stages[i]);
    stageit->setPos(stagewidth, 0);
    stagewidth += 150;
    _scene.addItem(stageit);
  }
}

int koregui::OperationFlow
  ::initNodeOperations(kore::NodePass* pass, int startcoord) {
  return startcoord + 0;
}

int koregui::OperationFlow
  ::initShaderOperations(kore::ShaderProgramPass* pass, int startcoord) {
  return startcoord + 0;
}

int koregui::OperationFlow
  ::initFBOOperations(kore::FrameBufferStage* stage, int startcoord) {
  return startcoord + 0;
}

void koregui::OperationFlow::mousePressEvent(QMouseEvent * event) {
  QGraphicsItem* item = itemAt(event->pos());
  if (item) {
    
  }
  showFlow();

  QGraphicsView::mousePressEvent(event);
}
