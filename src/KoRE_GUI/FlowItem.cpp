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

#include "KoRE_GUI/FlowItem.h"

#include <QPainter>
#include <QStaticText>

koregui::FlowItem::FlowItem(EFlowType flowType, QGraphicsItem* parent)
  : _type(flowType),
    _stage(NULL),
    _programpass(NULL),
    _nodepass(NULL),
    _op(NULL),
    _itemheight(35),
    _itemwidth(150),
    QGraphicsItem(parent){

}

koregui::FlowItem::~FlowItem(void) {
}

void koregui::FlowItem::refresh(void) {

}

QRectF koregui::FlowItem::boundingRect() const {
  return QRectF(0,0,150,35);
}

void koregui::FlowItem::paint(QPainter* painter,
                              const QStyleOptionGraphicsItem* option,
                              QWidget* widget ) {
  QBrush b;
  QPen p;
  QStaticText t;
  QFont font("Arial");

  font.setBold(true);
  font.setPointSize(9);
  painter->setFont(font);
  p.setStyle(Qt::PenStyle::NoPen);
  painter->setPen(p);
  b.setStyle(Qt::BrushStyle::SolidPattern);

  switch (_type) {
  case FLOW_FRAMEBUFFERSTAGE:
    b.setColor(QColor(255,254,186));
    if(_stage->getFrameBuffer()) {
      t.setText(_stage->getFrameBuffer()->getName().c_str());
    } else {
      t.setText("<empty>");
    }
    break;
  case FLOW_PROGRAMPASS:
    b.setColor(QColor(252,210,89));
    if(_programpass->getShaderProgram()) {
      t.setText(_programpass->getShaderProgram()->getName().c_str());
    } else {
      t.setText("<empty>");
    }
    break;
  case FLOW_NODEPASS:
    b.setColor(QColor(35,203,173));
    if(_nodepass->getSceneNode()) {
      t.setText(_nodepass->getSceneNode()->getName().c_str());
    } else {
      t.setText("<empty>");
    }
    break;
  case FLOW_OPERATION:
    b.setColor(QColor(250,123,28));
    t.setText("OPERATION");
    break;
  default:
    b.setColor(Qt::GlobalColor::red);
    t.setText("UNKNOWN");
  }
  painter->setBrush(b);
  painter->drawRect(0,0,150,35);

  // text
  p.setColor(QColor(33,33,33));
  p.setStyle(Qt::PenStyle::SolidLine);
  p.setWidth(2);
  painter->setPen(p);
  painter->drawStaticText(10, 10, t);
}
