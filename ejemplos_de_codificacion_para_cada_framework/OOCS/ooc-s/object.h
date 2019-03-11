#ifndef OBJECT_H
#define OBJECT_H

/*
 o---------------------------------------------------------------------o
 |
 | OOC-S root class
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

#include <stddef.h>

#define TYPE      struct object
#define INTERFACE struct object_interface

#define OBJECT_INTERFACE                        \
  void*  (*interface  )(TYPE*,void*);           \
  void*  (*cast       )(TYPE*,void*);           \
  int    (*equal      )(TYPE*,TYPE*);           \
  size_t (*hash       )(TYPE*);                 \
  TYPE*  (*alloc      )(size_t);                \
  void   (*free       )(TYPE*);                 \
  TYPE*  (*retain     )(TYPE*);                 \
  void   (*release    )(TYPE*);                 \
  TYPE*  (*autorelease)(TYPE*);                 \
  TYPE*  (*init       )(TYPE*);                 \
  TYPE*  (*deinit     )(TYPE*);

TYPE {
  INTERFACE *i;
};

INTERFACE {
  struct super_interface *super;
  OBJECT_INTERFACE
};

INTERFACE *object_interface(void);

#undef TYPE
#undef INTERFACE

/* o-----------------------------------------------------------------------o */

/*
 * Type and interface downcast
 */

#define INTERFACE_CAST(obj,itf) \
  ((struct itf##_interface*)((obj)->i->interface((obj),&itf##_interface)))

#define TYPE_CAST(obj,typ) \
  ((struct typ*)((obj)->i->cast((obj),typ##_interface())))

/*
 * Reference counting (special values)
 */

#define REFCNT_AUTO()   ((unsigned) 0)
#define REFCNT_UNIT()   ((unsigned) 1)
#define REFCNT_LAST()   ((unsigned)-2)
#define REFCNT_STATIC() ((unsigned)-1)

/*
 * Thread local storage
 */

#ifndef _USE_TLS
#define _USE_TLS
#endif

#endif /* OBJECT_H */
