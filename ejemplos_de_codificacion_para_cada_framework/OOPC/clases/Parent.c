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

/*---------------------------*/
/*   Parent implementation   */
/*---------------------------*/

#define IMPLEMENTATION

#include <Parent.h>

/*
  ---------------------
  Object implementation
  ---------------------
*/

void
constMethodDecl(print)
{
  printf("name:\t%s\n", this->m.name);
}

BASEOBJECT_IMPLEMENTATION

  methodName(print)

ENDOF_IMPLEMENTATION

/*
  --------------------
  Class implementation
  --------------------
*/

initClassDecl() {

	  /* defaults */
	  objDefault(attribute) = 1;
} /* required */

dtorDecl() /* required */
{
  free((void*)this->m.name);
  this->m.name = NULL;
}

t_Parent
classMethodDecl_(*const new) char const name[] __
{
  t_Parent *const this = Parent.alloc();
  if (this) Parent.init(this, name);
  return this;
}

void
methodDecl_(init) char const name[] __
{
  this->m.name = strdup(name);
}

void
methodDecl_(copy) t_Parent const*const per __
{
  Parent._Parent(this);
  Parent.init(this, per->m.name);
}

CLASS_IMPLEMENTATION

  methodName(new),
  methodName(init),
  methodName(copy)

ENDOF_IMPLEMENTATION
