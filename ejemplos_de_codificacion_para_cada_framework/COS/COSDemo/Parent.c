/**
 * C Object System
 * COS example01 -- Stream (abstract) class
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Parent.h"
#include <stdio.h>
#include "gfunction.h"
#include "gfunction3.h"

makclass(Parent);

defmethod(void, gfunction, Parent, Object)
  printf("gfunction de Parent!!!\n");
endmethod


defmethod(OBJ, ginit, Parent)
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Parent)
  retmethod(_1);
endmethod
