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

#ifndef TEXTUREEDITOR_H
#define TEXTUREEDITOR_H

#include <QWidget>
#include "ui_TextureEditor.h"
#include "KoRE/Texture.h"

namespace koregui {
  class TextureEditor : public QWidget {
    Q_OBJECT

  public:
    TextureEditor(QWidget *parent = 0);
    ~TextureEditor();

  public slots:
    void refresh();

  private:
    Ui::TextureEditor ui;
  };
}
#endif  // TEXTUREEDITOR_H
