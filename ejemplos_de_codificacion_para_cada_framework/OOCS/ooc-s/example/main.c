/*
 o---------------------------------------------------------------------o
 |
 | OOC-S example main
 |
 o---------------------------------------------------------------------o
 |
 | Object Oriented C - Simplified release
 |
 | Copyright (c) 2007+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/oopc.html#OOC-S
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the Simplified Object Oriented C package.
 |
 | OOC-S is free software; you can redistribute it and/or modify it
 | under the terms of the GNU Lesser General Public License as
 | published by the Free Software Foundation; either version 2.1 of
 | the License, or (at your option) any later version.
 |
 | OOC-S is distributed in the hope that it will be useful, but
 | WITHOUT ANY WARRANTY; without even the implied warranty of
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 | Lesser General Public License for more details.
 |
 | You should have received a copy of the GNU Lesser General Public
 | License along with this library; if not, write to the Free
 | Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 | Boston, MA 02110-1301 USA
 |
 o---------------------------------------------------------------------o
*/

#include <stdio.h>
#include <stdlib.h>


#include "parent.h"

int main(int argc, char *argv[])
{

  struct parent * p  =parent_new();
  p->i->method1(p);
  p->i->method2(p);

  struct interface_example_interface * i = INTERFACE_CAST(p,interface_example);
  i->method2((struct interface_example*)p);
  p->i->release(p);
  
  return EXIT_SUCCESS;
}
