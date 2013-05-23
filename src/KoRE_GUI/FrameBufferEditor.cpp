#include "FrameBufferEditor.h"
#include "KoRE/ResourceManager.h"
#include "KoRE/Common.h"
#include "KoRE/Texture.h"

koregui::FrameBufferEditor::FrameBufferEditor(
    koregui::FrameBufferStageItem* stage,
    QWidget *parent)
  : _currentitem(stage),
    _currentbuffer(NULL),
    QWidget(parent) {
  ui.setupUi(this);
  
  std::vector<kore::FrameBuffer*> bufferlist
    = kore::ResourceManager::getInstance()->getFramebuffers();
  if(!_currentbuffer) {
    ui.framebufferselect->addItem("<empty>", QVariant(KORE_ID_INVALID));
  }
  
  for (uint i = 0; i < bufferlist.size(); i++) {
    ui.framebufferselect->addItem(bufferlist[i]->getName().c_str(),
      QVariant(bufferlist[i]->getID()));
  }
  ui.tableWidget->verticalHeader()->hide();

  // add  Qt connections
  connect(ui.newbutton, SIGNAL(clicked()), this, SLOT(addNewFramebuffer()));
  connect(ui.newattach, SIGNAL(clicked()), this, SLOT(addNewAttachment()));
  connect(ui.applyButton, SIGNAL(clicked()), this, SLOT(applySettings()));
  connect(ui.nameEdit, SIGNAL(textEdited(const QString&)),
          this, SLOT(nameChanged(const QString&)));
  connect(ui.framebufferselect,
    SIGNAL(currentIndexChanged(int)),
    this,
    SLOT(framebufferChanged(int)));
}

koregui::FrameBufferEditor::~FrameBufferEditor() {

}

void koregui::FrameBufferEditor::setFramebuffer(const QString& name) {
  if(name != "<empty>") {
    ui.framebufferselect->setCurrentText(name);
  }
}

void koregui::FrameBufferEditor::addNewFramebuffer(void) {
  uint cnt = kore::ResourceManager::getInstance()->getFramebuffers().size();
  char buf[100];
  sprintf(buf, "Framebuffer_%i", cnt);
  kore::FrameBuffer* frabuf = new kore::FrameBuffer(std::string(buf));
  kore::ResourceManager::getInstance()->addFramebuffer(frabuf);
  ui.framebufferselect->addItem(frabuf->getName().c_str(),
                                QVariant(frabuf->getID()));
  ui.framebufferselect->setCurrentText(frabuf->getName().c_str());
  refresh();
}

void koregui::FrameBufferEditor::addNewAttachment(void) {
  if(!_currentbuffer) return;
  /*ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);
  // Attachments
  QComboBox* combo = new QComboBox();
  combo->addItem("GL_COLOR_ATTACHMENT", QVariant(GL_COLOR_ATTACHMENT0));
  combo->addItem("GL_DEPTH_ATTACHMENT", QVariant(GL_DEPTH_ATTACHMENT));
  combo->addItem("GL_STENCIL_ATTACHMENT", QVariant(GL_STENCIL_ATTACHMENT));
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 0, combo);

  // Pixel type
  combo = new QComboBox();
  combo->addItem("GL_FLOAT", QVariant(GL_FLOAT));
  combo->addItem("GL_UNSIGNED_BYTE", QVariant(GL_UNSIGNED_BYTE));
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 1, combo);

  // Format
  combo = new QComboBox();
  combo->addItem("GL_RGBA", QVariant(GL_RGBA));
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 2, combo);

  // Internal format
  combo = new QComboBox();
  combo->addItem("GL_RGBA8", QVariant(GL_RGBA8));
  combo->addItem("GL_FLOAT", QVariant(GL_FLOAT));
  combo->addItem("GL_DEPTH24_STENCIL8", QVariant(GL_DEPTH24_STENCIL8));
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 3, combo);*/

  /*STextureProperties()
    : width(0),
    height(0),
    depth(0),
    border(0),
    pixelType(KORE_GLUINT_HANDLE_INVALID),
    targetType(KORE_GLUINT_HANDLE_INVALID),
    format(KORE_GLUINT_HANDLE_INVALID),
    internalFormat(KORE_GLUINT_HANDLE_INVALID){
  }

  /// The Format of the texture (e.g. GL_RGBA).
  GLuint format;

  /// The Pixel type of the texture (e.g. GL_FLOAT, GL_UNSIGNED_BYTE,...).
  GLuint pixelType;

  /// The Internal format (e.g. GL_RGBA8, GL_FLOAT32,...).
  GLuint internalFormat;*/

  kore::STextureProperties props;
  props.border = 0;
  props.targetType = GL_TEXTURE_2D;
  props.width = 512;
  props.height = 512;
  props.format = GL_RGBA;
  props.internalFormat = GL_RGBA8;
  props.pixelType = GL_UNSIGNED_BYTE;
  if (_currentbuffer) {
    _currentbuffer->addTextureAttachment(props, "newAttachTex", GL_COLOR_ATTACHMENT0);
  }
}

void koregui::FrameBufferEditor::applySettings(void) {
  if(!_currentbuffer) return;
  /*for(int i = 0; i < ui.tableWidget->rowCount(); i++) {
    kore::STextureProperties props;
    props.pixelType = ui.tableWidget->item(i,0)->data(Qt::UserRole).toUInt();
    props.format = ui.tableWidget->item(i,1)->data(Qt::UserRole).toUInt();
  }*/
  refresh();
}

void koregui::FrameBufferEditor::refresh(void) {
  if(_currentbuffer) ui.nameEdit->setText(_currentbuffer->getName().c_str());
  ui.tableWidget->clearContents();
  //_currentbuffer->
}

void koregui::FrameBufferEditor::framebufferChanged(int index) {
  _currentbuffer = kore::ResourceManager::getInstance()
    ->getFramebuffer(ui.framebufferselect->itemData(
      ui.framebufferselect->currentIndex()).toULongLong());
  _currentitem->setFrameBuffer(_currentbuffer);
  int removeidx = ui.framebufferselect->findText("<empty>");
  if(removeidx >= 0) ui.framebufferselect->removeItem(removeidx);
  refresh();
}

void koregui::FrameBufferEditor::nameChanged(const QString& name) {
  if(!_currentbuffer) return;
  ui.framebufferselect->setItemText(ui.framebufferselect->currentIndex(),
                                    name);
  _currentbuffer->setName(name.toStdString());
  _currentitem->refresh();
  _currentitem->update();
}
