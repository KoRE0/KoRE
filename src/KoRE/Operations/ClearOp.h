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

#include "KoRE/Common.h"
#include "KoRE/Operations/Operation.h"

#ifndef KORE_SRC_KORE_OPERATIONS_CLEAROP_H_
#define KORE_SRC_KORE_OPERATIONS_CLEAROP_H_

namespace kore {
  class ClearOp : public Operation {
    public:

      ClearOp();
      //ClearOp(bool color, bool depth, bool stencil, glm::vec4 clearcolor);
      virtual ~ClearOp();

      virtual void update(void);
      virtual void reset(void);
      virtual bool dependsOn(const void* thing) const;
      virtual bool isValid(void) const;

      //void connect(const GLuint glType, const EEnableDisable enableDisable);

  private:
      virtual void doExecute(void) const;

      bool _enable;
      GLuint _glType;
  };
}

#endif  // KORE_SRC_KORE_OPERATIONS_CLEAROP_H_
