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

#ifndef SRC_KOREGUI_FLOWITEM_H_
#define SRC_KOREGUI_FLOWITEM_H_

#include <QGraphicsItem>

#include "KoRE/Passes/FrameBufferStage.h"
#include "KoRE/Passes/ShaderProgramPass.h"
#include "KoRE/Passes/NodePass.h"

namespace koregui {
  enum EFlowType {
    FLOW_FRAMEBUFFERSTAGE,
    FLOW_PROGRAMPASS,
    FLOW_NODEPASS,
    FLOW_OPERATION
  };
  class FlowItem : public QGraphicsItem {
  public:
    FlowItem(EFlowType flowType, QGraphicsItem* parent = 0);
    ~FlowItem(void);

    void refresh(void);
    inline int getHeight(void) {return _itemheight;}
    inline int getWidth(void) {return _itemwidth;}
    inline EFlowType getType(void) {return _type;}

  protected:
    QRectF boundingRect() const;
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem* option,
               QWidget* widget);

  private:
    EFlowType _type;
    kore::FrameBufferStage* _stage;
    kore::ShaderProgramPass* _programpass;
    kore::NodePass* _nodepass;
    kore::Operation* _op;
    int _itemheight, _itemwidth;
  };
}
#endif  // SRC_KOREGUI_FLOWITEM_H_
