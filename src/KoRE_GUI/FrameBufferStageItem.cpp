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
#include <QGraphicsSceneMouseEvent>

#include "KoRE_GUI/FrameBufferEditor.h"

#include "KoRE/RenderManager.h"

koregui::FrameBufferStageItem::FrameBufferStageItem(QGraphicsItem* parent)
                                          : _frameBuffer(NULL),
                                            _name("<empty>"),
                                            QGraphicsItem(parent) {
  setData(0, "FRAMEBUFFER");
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setCursor(QCursor(Qt::CursorShape::ArrowCursor));
  _bufferstage = new kore::FrameBufferStage();
  kore::RenderManager::getInstance()->addFramebufferStage(_bufferstage);
  refresh();
}

koregui::FrameBufferStageItem::~FrameBufferStageItem(void){
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
  ::setFrameBuffer(kore::FrameBuffer* framebuffer) {
  _frameBuffer = framebuffer;
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
      _programs.erase(it);
    }
  }
}

void koregui::FrameBufferStageItem
  ::shaderMoved(koregui::ShaderPassItem* pass) {
  uint i = 0;
  bool change = false;
  for (i; i < _programs.size(); i++) {
    if (_programs[i] == pass) {
      break;
    }
  }
  //compare to previous shaderPass, if any
  if (i > 0) {
    if( _programs[i]->pos().y() < _programs[i-1]->pos().y()) {
      std::swap(_programs[i],_programs[i-1]);
      change = true;
    }
  }
  //compare to next shaderPass, if any
  if( i < (_programs.size() - 1)) {
    if( _programs[i]->pos().y() > _programs[i+1]->pos().y()) {
      std::swap(_programs[i],_programs[i+1]);
      change = true;
    }
  }
  if(change) {
    refresh();
  }
}
