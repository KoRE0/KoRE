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
    stagewidth = initFBOOperations(stages[i], stagewidth);
  }
}

int koregui::OperationFlow
  ::initNodeOperations(kore::NodePass* pass, int startcoord) {
    koregui::FlowItem* stageit = new koregui::FlowItem(FLOW_NODEPASS);
    stageit->setNodePass(pass);
    stageit->setPos(startcoord, 80);
    _scene.addItem(stageit);
    int nodewidth = startcoord;
    std::vector<kore::Operation*> & operations =
      pass->getOperations();
    nodewidth += 150;
    /*if(operations.size() == 0) nodewidth += 150;
    for (uint i = 0; i < operations.size(); i++) {
      //nodewidth = initNodeOperations(nodepasses[i], nodewidth);
      nodewidth += 150;
    }*/
    return nodewidth;
}

int koregui::OperationFlow
  ::initShaderOperations(kore::ShaderProgramPass* pass, int startcoord) {
  koregui::FlowItem* stageit = new koregui::FlowItem(FLOW_PROGRAMPASS);
  stageit->setProgramPass(pass);
  stageit->setPos(startcoord, 40);
  _scene.addItem(stageit);
  int passwidth = startcoord;
  std::vector<kore::NodePass*> & nodepasses =
    pass->getNodePasses();
  if (nodepasses.size() == 0) passwidth += 155;
  for (uint i = 0; i < nodepasses.size(); i++) {
    passwidth = initNodeOperations(nodepasses[i], passwidth);
  }
  return passwidth;
}

int koregui::OperationFlow
    ::initFBOOperations(kore::FrameBufferStage* stage, int startcoord) {
  koregui::FlowItem* stageit = new koregui::FlowItem(FLOW_FRAMEBUFFERSTAGE);
  stageit->setFrameBufferStage(stage);
  stageit->setPos(startcoord, 0);
  _scene.addItem(stageit);
  int stagewidth = startcoord;
  std::vector<kore::ShaderProgramPass*> &progpasses =
  stage->getShaderProgramPasses();
  if (progpasses.size() == 0) stagewidth += 155;
  for (uint i = 0; i < progpasses.size(); i++) {
   stagewidth = initShaderOperations(progpasses[i], stagewidth);
  }
  return stagewidth;
}

void koregui::OperationFlow::mousePressEvent(QMouseEvent * event) {
  /*QGraphicsItem* item = itemAt(event->pos());
  if (item) {
  }*/
  showFlow();
  QGraphicsView::mousePressEvent(event);
}
