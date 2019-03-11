#ifndef OOEXCEPTIONS_H
#define OOEXCEPTIONS_H

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

#include <exception.h>

typedef enum {

  ooc_invalid_exception=0,

  ooc_bad_alloc,     /* thrown by alloc          */
  ooc_bad_cast,      /* not used by dynamic_cast */
  ooc_bad_typeid,    /* not used by typeid       */
  ooc_bad_exception, /* not used                 */

  /* last ooc exception id */
  ooc_last_exception

} ooc_exception;

#endif
