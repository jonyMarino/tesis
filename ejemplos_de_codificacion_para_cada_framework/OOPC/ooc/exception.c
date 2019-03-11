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
#include <stdlib.h>
#include <assert.h>
#include "exception.h"

/* global stack of exception context */
struct _exceptionContext_ *_currentExceptionContext_ = NULL;

void
_exceptionThrow_(int exception)
{
  /* no exception context saved, exit program */
  if (!_currentExceptionContext_) exit(exception); 

  /* free pointers stored on the current exception context pointers stack */
  while(_currentExceptionContext_->ptr) { 
    _currentExceptionContext_->ptr->fct(_currentExceptionContext_->ptr->ptr); 
    _currentExceptionContext_->ptr = _currentExceptionContext_->ptr->next; 
  } 

  /* jump to previous exception context */
  longjmp(_currentExceptionContext_->context, exception); 
} 

struct _protectedPointer_ 
_newProtectedPointer_(struct _protectedPointer_ *ptr, 
                      void* ptr2protect, 
                      void (*ptr_free)(void *)) 
{ 
  if (_currentExceptionContext_) { 
    ptr->next = _currentExceptionContext_->ptr; 
    ptr->ptr  = ptr2protect; 
    ptr->fct  = ptr_free; 
    _currentExceptionContext_->ptr = ptr; 
  } 
  return *ptr; 
} 

#ifdef DEBUG_THROW

void
_exceptionThrowDebug_(char const* _file_, int _line_, char const* _func_,
		      char const* _exception_, int exception)
{
  fprintf(stderr, "%s(%d):%s: exception '%s' (id %d) thrown\n",
	  _file_, _line_, _func_, _exception_, exception);
  _exceptionThrow_(exception);
}

#endif
