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

#ifndef SRC_KOREGUI_OPERATIONFLOW_H_
#define SRC_KOREGUI_OPERATIONFLOW_H_

#include <QGraphicsView>
#include "KoRE/Passes/NodePass.h"
#include "KoRE/Passes/ShaderProgramPass.h"
#include "KoRE/Passes/FrameBufferStage.h"

namespace koregui {
  class OperationFlow : public QGraphicsView {
      Q_OBJECT

  public:
    OperationFlow(QWidget *parent = 0);
    ~OperationFlow();

    void clearScene();
    void showFlow();

    int initNodeOperations(kore::NodePass* pass, int startcoord = 0);
    int initShaderOperations(kore::ShaderProgramPass* pass, int startcoord = 0);
    int initFBOOperations(kore::FrameBufferStage* stage, int startcoord = 0);


  public slots:
    void zoomIn(void) {scale(1.2,1.2);}
    void zoomOut(void) {scale(1/1.2,1/1.2);}


  protected:
    void mousePressEvent(QMouseEvent * event);

  private:
      QGraphicsScene _scene;
  };
}
#endif // SRC_KOREGUI_OPERATIONFLOWVIEWER_H_
