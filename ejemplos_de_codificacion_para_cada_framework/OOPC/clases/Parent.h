#ifndef Parent_H
#define Parent_H

/*
 ******************************
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * For more information, please see the paper:
 * http://home.cern.ch/ldeniau/html/oopc/oopc.html
 *
 ******************************
 */

#include <ooc.h>

/*----------------------*/
/*   Parent interface   */
/*      base class      */ 
/*----------------------*/

#undef  OBJECT
#define OBJECT Parent

/* Object interface */
BASEOBJECT_INTERFACE

  char const* private(name);
  int private(attribute);

BASEOBJECT_METHODS

  void constMethod(print);

ENDOF_INTERFACE

/* Class interface */
CLASS_INTERFACE

  t_Parent*const classMethod_(new) char const name[] __;
  void method_(init) char const name[] __;
  void method_(copy) t_Parent const*const per __;

ENDOF_INTERFACE

#endif
