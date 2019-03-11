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

#include <stdio.h>

/*-----------------------------*/
/*   Child implementation    */
/*   inherit from Parent     */
/*-----------------------------*/

#define IMPLEMENTATION

#include "Child.h"

/*
  ---------------------
  Object implementation
  ---------------------
*/

void
methodDecl(child_method)
{
  /**/
}

void
constMethodOvldDecl(print, Parent)
{
  /**/
	sendCMsg(this,Parent,print);
	printf("from child\r\n");
}

OBJECT_IMPLEMENTATION

  SUPERCLASS (Parent),
  SUPERCLASS (Parent2),
  methodName(child_method)

ENDOF_IMPLEMENTATION

/*
  --------------------
  Class implementation
  --------------------
*/

initClassDecl() /* required */
{
  /* initialize super class */
  initSuper(Parent);
  initSuper(Parent2);

  /* overload super class methods */
  overload(Parent.print) = methodOvldName(print, Parent);


}

dtorDecl() /* required */
{
	Parent._Parent(super(this,Parent));
	Parent2._Parent2(super(this,Parent2));
}

t_Child
classMethodDecl_(*const new)
     char const name[] __
{
  t_Child *const this = Child.alloc();
  if (this) Child.init(this, name);
  return this;
}

void
methodDecl_(init)
     char const name[]__
{
  Parent.init(super(this,Parent), name);
  Parent2.init(super(this,Parent2), name);
  /*más código de inicialización*/
}

void
methodDecl_(copy) t_Child const*const mng __
{
  Child._Child(this);
  Child.init(this,
	       mng->m.Parent.m.name);
}

CLASS_IMPLEMENTATION

  methodName(new),
  methodName(init),
  methodName(copy)

ENDOF_IMPLEMENTATION
