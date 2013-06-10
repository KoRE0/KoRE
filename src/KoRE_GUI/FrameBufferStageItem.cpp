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

#include "KoRE_GUI/FrameBufferStageItem.h"

#include <QPainter>
#include <QCursor>
#include <QStaticText>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "KoRE_GUI/FrameBufferEditor.h"
#include "KoRE_GUI/RenderViewer.h"

#include "KoRE/RenderManager.h"

koregui::FrameBufferStageItem::FrameBufferStageItem(QGraphicsItem* parent)
                                          : _frameBuffer(NULL),
                                            _name("<empty>"),
                                            QGraphicsItem(parent) {
  setData(0, "FRAMEBUFFERSTAGE");
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setCursor(QCursor(Qt::CursorShape::ArrowCursor));
  _bufferstage = new kore::FrameBufferStage();
  kore::RenderManager::getInstance()->addFramebufferStage(_bufferstage);
  refresh();
}

koregui::FrameBufferStageItem::~FrameBufferStageItem(void){
  while (_programs.size() > 0) {
    delete(_programs[0]);
  }
  kore::RenderManager::getInstance()->removeFrameBufferStage(_bufferstage);
}

void koregui::FrameBufferStageItem::refresh(void){
  prepareGeometryChange();
  if(_frameBuffer) {
    _name = _frameBuffer->getName();
  }
  _bufferheight = 40;
  _bufferwidth = 200;
  for (uint i = 0; i < _programs.size(); i++) {
    _programs[i]->setPos(-10, _bufferheight);
    _bufferheight += _programs[i]->getHeight() + 20;
  }
  for (uint i = 0; i < _outputs.size(); i++) {
    _outputs[i]->setPos(192, _bufferheight);
    _outputs[i]->show();
    _bufferheight += 30;
  }
}

QRectF koregui::FrameBufferStageItem::boundingRect() const{
  return QRectF(0, 0, _bufferwidth, _bufferheight);
}

void koregui::FrameBufferStageItem::paint(QPainter* painter,
                                     const QStyleOptionGraphicsItem* option,
                                     QWidget* widget) {
  QBrush b;
  QPen p;
  QFont font("Arial");
  QStaticText text;
 
  p.setStyle(Qt::PenStyle::NoPen);
  b.setColor((isSelected())?QColor(86,86,86):QColor(44,44,44));
  b.setStyle(Qt::BrushStyle::SolidPattern);
  painter->setPen(p);
  painter->setBrush(b);
  painter->drawRect(0, 0, _bufferwidth, _bufferheight);
 
  font.setBold(true);
  font.setPointSize(12);
  painter->setFont(font);
 
  text.setText(_name.c_str());
  p.setColor(QColor(255,255,255));
  p.setStyle(Qt::PenStyle::SolidLine);
  painter->setPen(p);
  painter->drawStaticText(10,10, text);
  painter->drawImage(_bufferwidth - 26, 10, QImage("./assets/icons/gear.png"));

  for (uint i = 0; i<_outputs.size(); i++) {
    text.setText((_outputs[i]->getData()->name.c_str()));
    font.setFamily("Consolas");
    painter->setFont(font);
    p.setStyle(Qt::PenStyle::SolidLine);
    p.setColor(QColor(220,220,220));
    painter->setPen(p);
    painter->drawStaticText(14,_bufferheight - 30 - i * 30, text);
  }
}

void koregui::FrameBufferStageItem
  ::mousePressEvent(QGraphicsSceneMouseEvent* event) {
  if (event->button() == Qt::MouseButton::LeftButton) {
    QPointF p = event->pos();
    if (p.y() < 26 && p.x() > _bufferwidth - 26) {
      koregui::FrameBufferEditor* ed = new koregui::FrameBufferEditor(this);
      ed->setFramebuffer(QString(_name.c_str()));
      ed->show();
    }
  }
  QGraphicsItem::mousePressEvent(event);
}

void koregui::FrameBufferStageItem
  ::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  koregui::RenderViewer* rview
    = static_cast<koregui::RenderViewer*>(scene()->parent());
  rview->framebufferMoved(this);
  QGraphicsItem::mouseMoveEvent(event);
}

void koregui::FrameBufferStageItem
  ::setFrameBuffer(kore::FrameBuffer* framebuffer) {
  _frameBuffer = framebuffer;
  _bufferstage->setFrameBuffer(_frameBuffer);
  for (uint i = 0; i < _outputs.size(); i++) {
    delete(_outputs[i]);
  }
  _outputs.clear();
  std::vector<kore::ShaderData>& sdata = _frameBuffer->getOutputs();
  for (uint i = 0; i < sdata.size(); i++) {
    _outputs.push_back(new ShaderDataItem(&sdata[i], NULL, this));
  }
  refresh();
}

void koregui::FrameBufferStageItem
  ::addShaderPass(koregui::ShaderPassItem* pass) {
  _bufferstage->addProgramPass(pass->getProgramPass());
  _programs.push_back(pass);
  refresh();
}

void koregui::FrameBufferStageItem
  ::removeShaderPass(koregui::ShaderPassItem* pass) {
  for (auto it = _programs.begin();  it != _programs.end(); it++) {
    if (*it == pass) {
      _bufferstage->removeProgramPass((*it)->getProgramPass());
      _programs.erase(it);
      refresh();
      return;
    }
  }
}

void koregui::FrameBufferStageItem
  ::shaderMoved(koregui::ShaderPassItem* pass) {
  uint i = 0;
  bool change = false;
  // find program index
  for (i; i < _programs.size(); i++) {
    if (_programs[i] == pass) {
      break;
    }
  }
  // compare to previous shaderPass, if any
  if (i > 0) {
    if( _programs[i]->pos().y() < _programs[i-1]->pos().y()) {
      std::swap(_programs[i],_programs[i-1]);
      _bufferstage->swapPasses(_programs[i]->getProgramPass(),
                               _programs[i-1]->getProgramPass());
      change = true;
    }
  }
  // compare to next shaderPass, if any
  if( i < (_programs.size() - 1)) {
    if( _programs[i]->pos().y() > _programs[i+1]->pos().y()) {
      std::swap(_programs[i],_programs[i+1]);
      _bufferstage->swapPasses(_programs[i]->getProgramPass(),
                               _programs[i+1]->getProgramPass());
      change = true;
    }
  }
  if(change) {
    refresh();
  }
}
