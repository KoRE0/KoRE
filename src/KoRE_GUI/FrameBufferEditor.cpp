#include "FrameBufferEditor.h"
#include "KoRE/ResourceManager.h"
#include "KoRE/Common.h"
#include "KoRE/Texture.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QSizePolicy>
#include <QCheckBox>

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
  ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  ui.tableWidget->horizontalHeader()->resizeSection(0, 70);
  ui.tableWidget->horizontalHeader()->resizeSection(1, 140);
  ui.tableWidget->horizontalHeader()->resizeSection(2, 110);
  ui.tableWidget->horizontalHeader()->resizeSection(3, 130);
  ui.tableWidget->horizontalHeader()->resizeSection(4, 200);

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
  ui.tableWidget->setRowCount(ui.tableWidget->rowCount() + 1);

  //ui.tableWidget
  // Attachments
  QComboBox* combo = new QComboBox();
  combo->addItem("COLOR", QVariant(GL_COLOR_ATTACHMENT0));
  combo->addItem("DEPTH", QVariant(GL_DEPTH_ATTACHMENT));
  combo->addItem("STENCIL", QVariant(GL_STENCIL_ATTACHMENT));
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 0, combo);

  // Resolution
  QWidget* reswidget = new QWidget();
  QHBoxLayout* hlay = new QHBoxLayout();
  QLineEdit* lineedit = new QLineEdit("512");
  lineedit->setValidator(new QIntValidator());
  hlay->addWidget(lineedit);
  QLabel* label = new QLabel("x");
  hlay->addWidget(label);
  lineedit = new QLineEdit("512");
  lineedit->setValidator(new QIntValidator());
  hlay->addWidget(lineedit);
  QCheckBox* cbox = new QCheckBox("auto");
  cbox->setFixedWidth(50);
  hlay->addWidget(cbox);
  hlay->setContentsMargins(QMargins(0,0,0,0));
  reswidget->setLayout(hlay);
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 1, reswidget);

  // Format
  combo = new QComboBox();
  combo->addItem("RGBA", QVariant(GL_RGBA));
  combo->addItem("RGB", QVariant(GL_RGB));
  combo->addItem("RG", QVariant(GL_RG));
  combo->addItem("R", QVariant(GL_RED));
  combo->addItem("DEPTH", QVariant(GL_DEPTH_COMPONENT));
  combo->addItem("DEPTH_STENCIL", QVariant(GL_DEPTH_STENCIL));
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 2, combo);

  // Internal format
  combo = new QComboBox();
  this->setInternalFormatCombo(GL_RGBA, combo);
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 3, combo);

  // Pixel type
  combo = new QComboBox();
  combo->addItem("UNSIGNED_BYTE", QVariant(GL_UNSIGNED_BYTE));
  combo->addItem("BYTE", QVariant(GL_BYTE));
  combo->addItem("UNSIGNED_SHORT", QVariant(GL_UNSIGNED_SHORT));
  combo->addItem("SHORT", QVariant(GL_SHORT));
  combo->addItem("UNSIGNED_INT", QVariant(GL_UNSIGNED_INT));
  combo->addItem("INT", QVariant(GL_INT));
  combo->addItem("FLOAT", QVariant(GL_FLOAT));
  combo->addItem("UNSIGNED_BYTE_3_3_2",
    QVariant(GL_UNSIGNED_BYTE_3_3_2));
  combo->addItem("UNSIGNED_BYTE_2_3_3_REV",
    QVariant(GL_UNSIGNED_BYTE_2_3_3_REV));
  combo->addItem("UNSIGNED_SHORT_5_6_5",
    QVariant(GL_UNSIGNED_SHORT_5_6_5));
  combo->addItem("UNSIGNED_SHORT_5_6_5_REV",
    QVariant(GL_UNSIGNED_SHORT_5_6_5_REV));
  combo->addItem("UNSIGNED_SHORT_4_4_4_4",
    QVariant(GL_UNSIGNED_SHORT_4_4_4_4));
  combo->addItem("UNSIGNED_SHORT_5_5_5_1",
    QVariant(GL_UNSIGNED_SHORT_5_5_5_1));
  combo->addItem("UNSIGNED_SHORT_1_5_5_5_REV",
    QVariant(GL_UNSIGNED_SHORT_1_5_5_5_REV));
  combo->addItem("UNSIGNED_INT_8_8_8_8",
    QVariant(GL_UNSIGNED_INT_8_8_8_8));
  combo->addItem("UNSIGNED_INT_8_8_8_8_REV",
    QVariant(GL_UNSIGNED_INT_8_8_8_8_REV));
  combo->addItem("UNSIGNED_INT_10_10_10_2",
    QVariant(GL_UNSIGNED_INT_10_10_10_2));
  combo->addItem("UNSIGNED_INT_2_10_10_10_REV",
    QVariant(GL_UNSIGNED_INT_2_10_10_10_REV));
  ui.tableWidget->setCellWidget(ui.tableWidget->rowCount() -1, 4, combo);
}

void koregui::FrameBufferEditor::applySettings(void) {
  if(!_currentbuffer) return;
  uint colortarget = 0;
  for(int i = 0; i < ui.tableWidget->rowCount(); i++) {
    kore::STextureProperties props;
    props.targetType = GL_TEXTURE_2D;

    QHBoxLayout* hlay =
      static_cast<QHBoxLayout*>(ui.tableWidget->cellWidget(i, 1)->layout());
    QLineEdit* res = static_cast<QLineEdit*>(hlay->itemAt(0)->widget());
    uint resx = res->text().toUInt();
    res = static_cast<QLineEdit*>(hlay->itemAt(2)->widget());
    uint resy = res->text().toUInt();
    QCheckBox* cb = static_cast<QCheckBox*>(hlay->itemAt(3)->widget());
    bool autores = (cb->isChecked())?true:false;

    props.width = resx;
    props.height = resy;

    QComboBox* cbox =
      static_cast<QComboBox*>(ui.tableWidget->cellWidget(i, 2));
    props.format = cbox->itemData(cbox->currentIndex()).toUInt();
    cbox = static_cast<QComboBox*>(ui.tableWidget->cellWidget(i, 3));
    props.internalFormat = cbox->itemData(cbox->currentIndex()).toUInt();
    cbox = static_cast<QComboBox*>(ui.tableWidget->cellWidget(i, 4));
    props.pixelType = cbox->itemData(cbox->currentIndex()).toUInt();

    cbox = static_cast<QComboBox*>(ui.tableWidget->cellWidget(i, 0));
    GLuint target = cbox->itemData(cbox->currentIndex()).toUInt();

    switch(target) {
    case GL_COLOR_ATTACHMENT0:
      _currentbuffer->addTextureAttachment(props,
                                           "Color",
                                           GL_COLOR_ATTACHMENT0 + colortarget);
      colortarget++;
      break;
    case GL_DEPTH_ATTACHMENT:
      _currentbuffer->addTextureAttachment(props,
                                           "Depth",
                                           GL_DEPTH_ATTACHMENT);
      break;
    case GL_STENCIL_ATTACHMENT:
      _currentbuffer->addTextureAttachment(props,
                                           "Stencil",
                                           GL_STENCIL_ATTACHMENT);
      break;
    default:
      // ERROR
      break;
    }
  }
  _currentitem->setFrameBuffer(_currentbuffer);
  refresh();
}

void koregui::FrameBufferEditor::refresh(void) {
  if(_currentbuffer) ui.nameEdit->setText(_currentbuffer->getName().c_str());
  ui.tableWidget->clearContents();
  ui.tableWidget->setRowCount(0);
  //
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

void koregui::FrameBufferEditor::setInternalFormatCombo(GLuint internalFormat,
                                                        QComboBox* cbox ){
  cbox->clear();
  switch (internalFormat) {
  case GL_RGBA:
  case GL_BGRA:
    cbox->addItem("RGBA8", QVariant(GL_RGBA8));    
    cbox->addItem("RGBA12", QVariant(GL_RGBA12));
    cbox->addItem("RGBA16", QVariant(GL_RGBA16));
    cbox->addItem("RGBA16F", QVariant(GL_RGBA16F));
    cbox->addItem("RGBA32F", QVariant(GL_RGBA32F));
    cbox->addItem("RGBA8I", QVariant(GL_RGBA8I));
    cbox->addItem("RGBA8UI", QVariant(GL_RGBA8UI));
    cbox->addItem("RGBA16I", QVariant(GL_RGBA16I));
    cbox->addItem("RGBA16UI", QVariant(GL_RGBA16UI));
    cbox->addItem("RGBA32I", QVariant(GL_RGBA32I));
    cbox->addItem("RGBA32UI", QVariant(GL_RGBA32UI));
    cbox->addItem("RGBA8_SNORM", QVariant(GL_RGBA8_SNORM));
    cbox->addItem("RGB10_A2", QVariant(GL_RGB10_A2));
    cbox->addItem("RGB10_A2UI", QVariant(GL_RGB10_A2UI));
    cbox->addItem("SRGB8_ALPHA8", QVariant(GL_SRGB8_ALPHA8));
    cbox->addItem("RGB5_A1", QVariant(GL_RGB5_A1));
    break;
  case GL_RGB:
  case GL_BGR:
    cbox->addItem("RGB8", QVariant(GL_RGB8));
    cbox->addItem("RGB8_SNORM", QVariant(GL_RGB8_SNORM));
    cbox->addItem("RGB4", QVariant(GL_RGB4));
    cbox->addItem("RGB5", QVariant(GL_RGB5));
    cbox->addItem("RGB10", QVariant(GL_RGB10));
    cbox->addItem("RGB12", QVariant(GL_RGB12));
    cbox->addItem("RGB16_SNORM", QVariant(GL_RGB16_SNORM));
    cbox->addItem("RGBA2", QVariant(GL_RGBA2));
    cbox->addItem("RGBA4", QVariant(GL_RGBA4));
    cbox->addItem("SRGB8", QVariant(GL_SRGB8));
    cbox->addItem("RGB16F", QVariant(GL_RGB16F));
    cbox->addItem("RGB32F", QVariant(GL_RGB32F));
    cbox->addItem("RGB9_E5", QVariant(GL_RGB9_E5));
    cbox->addItem("RGB8I", QVariant(GL_RGB8I));
    cbox->addItem("RGB8UI", QVariant(GL_RGB8UI));
    cbox->addItem("RGB16I", QVariant(GL_RGB16I));
    cbox->addItem("RGB16UI", QVariant(GL_RGB16UI));
    cbox->addItem("RGB32I", QVariant(GL_RGB32I));
    cbox->addItem("RGB32UI", QVariant(GL_RGB32UI));
    cbox->addItem("R3_G3_B2", QVariant(GL_R3_G3_B2));
    cbox->addItem("R11F_G11F_B10F", QVariant(GL_R11F_G11F_B10F));
    cbox->addItem("R11F_G11F_B10F", QVariant(GL_R11F_G11F_B10F));
    break;
  case GL_RG:
    cbox->addItem("RG8", QVariant(GL_RG8));
    cbox->addItem("RG8_SNORM", QVariant(GL_RG8_SNORM));
    cbox->addItem("RG16", QVariant(GL_RG16));
    cbox->addItem("RG16_SNORM", QVariant(GL_RG16_SNORM));
    cbox->addItem("RG16F", QVariant(GL_RG16F));
    cbox->addItem("RG32F", QVariant(GL_RG32F));
    cbox->addItem("RG8I", QVariant(GL_RG8I));
    cbox->addItem("RG8UI", QVariant(GL_RG8UI));
    cbox->addItem("RG16I", QVariant(GL_RG16I));
    cbox->addItem("RG16UI", QVariant(GL_RG16UI));
    cbox->addItem("RG32I", QVariant(GL_RG32I));
    cbox->addItem("RG32UI", QVariant(GL_RG32UI));
    break;
  case GL_RED:
    cbox->addItem("R8", QVariant(GL_R8));
    cbox->addItem("R8_SNORM", QVariant(GL_R8_SNORM));
    cbox->addItem("R16", QVariant(GL_R16));
    cbox->addItem("R16_SNORM", QVariant(GL_R16_SNORM));
    cbox->addItem("R16F", QVariant(GL_R16F));
    cbox->addItem("R32F", QVariant(GL_R32F));
    cbox->addItem("R8I", QVariant(GL_R8I));
    cbox->addItem("R8UI", QVariant(GL_R8UI));
    cbox->addItem("R16I", QVariant(GL_R16I));
    cbox->addItem("R16UI", QVariant(GL_R16UI));
    cbox->addItem("R32I", QVariant(GL_R32I));
    cbox->addItem("R32UI", QVariant(GL_R32UI));
    break;
  case GL_DEPTH_COMPONENT:
    cbox->addItem("DEPTH_COMPONENT16", QVariant(GL_DEPTH_COMPONENT16));
    cbox->addItem("DEPTH_COMPONENT24", QVariant(GL_DEPTH_COMPONENT24));
    cbox->addItem("DEPTH_COMPONENT32", QVariant(GL_DEPTH_COMPONENT32));
    cbox->addItem("DEPTH_COMPONENT32F", QVariant(GL_DEPTH_COMPONENT32F));
    break;
  case GL_DEPTH_STENCIL:
    cbox->addItem("DEPTH24_STENCIL8", QVariant(GL_DEPTH24_STENCIL8));
  default:
    // TODO(dospelt) ERROR!
    break;
  }
}
