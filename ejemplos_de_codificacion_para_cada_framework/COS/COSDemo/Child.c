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

#include "Child.h"
#include "gfunction.h"
#include "gfunction2.h"

#include <cos/gen/message.h>
#include <stdio.h>

makclass(Child, Parent);

useclass(Class1);

defmethod(OBJ, ginit, Child)
  self->class1 = gnew(Class1);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Child)
  grelease(self->class1);
  retmethod(_1);
endmethod


defmethod(void, gfunction, Child, Object)
  printf("gfunction de Child: %d!!!\n", (int)self->attribute);
endmethod

defalias(void, (gfunction )gfunction2, Child, Object);

defmethod(void, (gfunction), Child, Object)
	printf("Around gfunction1 : Estoy antes de gfunction1!!!\n");
	next_method(self1,self2);
endmethod

defmethod(void, (gfunction2), Child, Object)
	printf("Around gfunction2 : Estoy antes de gfunction2!!!\n");
	next_method(self1,self2);
endmethod


defmethod(void, gunrecognizedMessage1, Child)
	if(gunderstandMessage1(self->class1,_sel) == True)
			forward_message(self->class1); // delegate
endmethod

