#ifndef AUTORELEASE_H
#define AUTORELEASE_H

/*
 o---------------------------------------------------------------------o
 |
 | OOC-S autorelease pool
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

#include "object.h"

#define TYPE      struct autorelease
#define INTERFACE struct autorelease_interface

TYPE {
  INTERFACE *i;
};

INTERFACE {
  struct object_interface *super;
  /* final type */
  OBJECT_INTERFACE
  void (*addObject)(TYPE*,struct object*);
};

TYPE      *autorelease_new(void);
INTERFACE *autorelease_interface(void);

/* current autorelease pool, global state */
extern _USE_TLS TYPE *autorelease_pool;

#undef TYPE
#undef INTERFACE

#endif /* AUTORELEASE_H */
