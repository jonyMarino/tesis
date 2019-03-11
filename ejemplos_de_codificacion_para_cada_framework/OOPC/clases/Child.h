#ifndef Child_H
#define Child_H

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

#include <Parent.h>
#include <Parent2.h>

/*---------------------------*/
/*     Child interface     */
/*    derive from Parent   */
/*   derive from Parent2   */
/*---------------------------*/

#undef  OBJECT
#define OBJECT Child

/* Object interface */
OBJECT_INTERFACE

  INHERIT_MEMBERS_OF (Parent);
  INHERIT_MEMBERS_OF (Parent2);
  int private(child_attribute);

OBJECT_METHODS

  INHERIT_METHODS_OF (Parent);
  INHERIT_METHODS_OF (Parent2);
  void method(child_method);

ENDOF_INTERFACE

/* Class interface */
CLASS_INTERFACE

  t_Child*const classMethod_(new)
     char const name[]__;
  void method_(init)
     char const name[]__;
  void method_(copy) t_Child const*const child __;

ENDOF_INTERFACE

#endif
