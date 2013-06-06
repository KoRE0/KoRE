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

#include "KoRE_GUI/BindPathItem.h"
#include "KoRE_GUI/NodeItem.h"
#include <QPainter>
#include <QCursor>

#include "KoRE/Operations/BindOperations/BindAttribute.h"
#include "KoRE/Operations/BindOperations/BindUniform.h"
#include "KoRE/Operations/BindOperations/BindTexture.h"
#include "KoRE/Operations/BindOperations/BindImageTexture.h"
#include "KoRE/Operations/RenderMesh.h"

koregui::BindPathItem::BindPathItem(ShaderDataItem* start,
                                    ShaderInputItem* end,
                                    QGraphicsItem* parent)
                                  : _start(start),
                                    _end(end),
                                    _bindOP(NULL),
                                    _dragend(0,0),
                                    _animOffset(0),
                                    _animated(false),
                                    QGraphicsPathItem(parent){
  setData(0, "BINDPATH");
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setCursor(QCursor(Qt::CursorShape::WhatsThisCursor));
  setZValue(-10);
}

koregui::BindPathItem::~BindPathItem(void) {
  removeBinding();
  setEnd(NULL);
}

QRectF koregui::BindPathItem::boundingRect() const {
  return path().boundingRect().adjusted(-2,-2,2,2);
}

void koregui::BindPathItem::paint(QPainter* painter,
                                  const QStyleOptionGraphicsItem* option,
                                  QWidget* widget) {
  // TODO(dospelt) use QPainterPathStroker
  QPointF start = mapFromItem(_start,6,6);
  QPointF dest = (_end)?mapFromItem(_end,6,6):_dragend;
  QPointF dist = QPointF((dest.x()- start.x())/2, 0);
  QPainterPath path(start);
  path.cubicTo(start + dist, dest - dist, dest);
  setPath(path);

  QPen p;
  p.setWidth(2);

  if (isSelected()) {
    p.setColor(QColor(100, 255, 255));
  } else {
    p.setColor(QColor(200, 200, 200));
  }
  if(_animated) {
    QVector<qreal> dashes;
    dashes << 4 << 3;
    p.setDashPattern(dashes);
    p.setDashOffset(_animOffset);
  }
  painter->setPen(p);
  painter->drawPath(path);
}

bool koregui::BindPathItem::checkBinding(koregui::ShaderInputItem* target) {
  // TODO(dospelt) implement check
  return true;
}

bool koregui::BindPathItem::initBinding(void) {
  kore::NodePass* nodePass = NULL;
  if(_start->getData()->component != NULL) {
    // see if nodePass already exists
    std::vector<kore::NodePass*> npasses =
      _end->getShaderPass()->getProgramPass()->getNodePasses();
    for (uint i = 0; i < npasses.size(); i++) {
      if(npasses[i]->getSceneNode() == _start->getNodeItem()->getSceneNode()) {
        nodePass = npasses[i];
        break;
      }
    }
    // if not, create new
    if(!nodePass) {
      nodePass = new kore::NodePass(_start->getNodeItem()->getSceneNode());
      _end->getShaderPass()->getProgramPass()->addNodePass(nodePass);
    }
  }
  kore::ShaderInput* target = const_cast<kore::ShaderInput*>(_end->getInput());
  kore::ShaderProgram* prog = const_cast<kore::ShaderProgram*>(
    _end->getShaderPass()->getProgramPass()->getShaderProgram());

  // attribute binding
  if (target->input_type == GL_ACTIVE_ATTRIBUTES) {
    _bindOP = new kore::BindAttribute(_start->getData(), _end->getInput());
    nodePass->addOperation(_bindOP);
    if(_start->getData()->component->getType() == kore::COMPONENT_MESH) {
      // add renderMesh Op, if necessary
      std::vector<kore::Operation*> finishOps =
          nodePass->getFinishOperations();
      for(auto it = finishOps.begin(); it != finishOps.end(); it++) {
        if ((*it)->getType() == kore::OP_RENDERMESH) return true;
      }
      kore::RenderMesh* _renderOP = new kore::RenderMesh(
        static_cast<kore::MeshComponent*>(_start->getData()->component));
      nodePass->addOperation(_renderOP);
    }
   return true;
  }

  // uniform binding
  if(target->input_type == GL_ACTIVE_UNIFORMS) {
    if(target->isImageType()) {
      _bindOP = new kore::BindImageTexture(_start->getData(),
                                           _end->getInput());
    } else if (target->isSamplerType()) {
       _bindOP = new kore::BindTexture(_start->getData(),
                                       _end->getInput());
    } else {
      _bindOP = new kore::BindUniform(_start->getData(),
                                      _end->getInput());
    }
    if(nodePass) {
      nodePass->addOperation(_bindOP);
    } else {
      // non-node-binding
      kore::ShaderProgramPass* progpass = 
        static_cast<kore::ShaderProgramPass*>(_end->getShaderPass()
                                                  ->getProgramPass());
      progpass->addStartupOperation(_bindOP);
    }
    return true;
  }
  return false;
}

void koregui::BindPathItem::removeBinding() {
  kore::NodePass* nodePass = NULL;
  std::vector<kore::NodePass*> npasses =
    _end->getShaderPass()->getProgramPass()->getNodePasses();
  for (uint i = 0; i < npasses.size(); i++) {
    if(npasses[i]->getSceneNode() == _start->getNodeItem()->getSceneNode()) {
      nodePass = npasses[i];
      break;
    }
  }
  if (nodePass) {
    nodePass->removeOperation(_bindOP);
  }
}

void koregui::BindPathItem::animate() {
  _animOffset -= 1;
  if(_animOffset <= -7) _animOffset += 7;
  update();
}
