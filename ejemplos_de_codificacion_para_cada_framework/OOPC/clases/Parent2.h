#ifndef Parent2_H
#define Parent2_H

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
/*   Parent2 interface   */
/*      base class      */ 
/*----------------------*/

#undef  OBJECT
#define OBJECT Parent2

/* Object interface */
BASEOBJECT_INTERFACE

  char const* private(name);

BASEOBJECT_METHODS

  void constMethod(print);

ENDOF_INTERFACE

/* Class interface */
CLASS_INTERFACE

  t_Parent2*const classMethod_(new) char const name[] __;
  void method_(init) char const name[] __;
  void method_(copy) t_Parent2 const*const per __;

ENDOF_INTERFACE

#endif
