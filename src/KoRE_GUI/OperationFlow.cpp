#include "KoRE_GUI/OperationFlow.h"

koregui::OperationFlow::OperationFlow(QWidget* parent)
                                    : QGraphicsView(parent) {
  setWindowTitle("OperationFlow");
  _scene.setBackgroundBrush(QBrush(QColor(23,23,23)));
  _scene.setParent(this);
  setScene(&_scene);
  setMinimumSize(800,200);
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
