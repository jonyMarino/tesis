/**
 * C Object System
 * COS example01 -- main
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

#include "gfunction.h"
#include "gfunction2.h"
#include "gfunction3.h"
#include "value.h"
#include <stdlib.h>
#include <stdio.h>
#include <cos/Number.h>

useclass( Parent, Child, P_value,Object);



int main(void)
{

  OBJ parent = gnew(Parent);
  OBJ child = gnew(Child);


  gputAt(child, P_value,aInt(3));

  gfunction(parent, parent);
  gfunction(child, parent);

  gfunction2(child, child);

  gfunction3(child , 3);

  grelease(parent);
  grelease(child);

  return EXIT_SUCCESS;
}

