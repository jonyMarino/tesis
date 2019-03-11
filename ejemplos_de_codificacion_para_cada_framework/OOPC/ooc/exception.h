#ifndef EXCEPTION_H
#define EXCEPTION_H

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

#ifndef __STDC__
#  error "exception.h needs ISO C compiler to work properly"
#endif

#include <setjmp.h>

/* some useful macros */

#define _makeString_(a) #a
#define _string_(a) _makeString_(a)

#define _makeConcat_(a,b) a ## b
#define _concat_(a,b) _makeConcat_(a,b)

/* some hidden types used to handle exceptions */

/* type of stack of protected pointer */
struct _protectedPointer_ {
  struct _protectedPointer_ *next;
  void *ptr;
  void (*fct)(void*);
};

/* type of stack of exception */
struct _exceptionContext_ {
  struct _exceptionContext_ *next;
  struct _protectedPointer_ *ptr;
  jmp_buf context;
};

/* extern declarations */

extern struct _exceptionContext_ *_currentExceptionContext_;
extern struct _protectedPointer_
  _newProtectedPointer_(struct _protectedPointer_*, void*, void (*)(void *));

/* exception keywords */
#ifdef ALLOW_PTREXCEPTION
#  define _ensure_pointers_as_exceptions_ \
      assert(sizeof(int)>=sizeof(void*) && "expected to work properly")
#else
#  define _ensure_pointers_as_exceptions_
#endif

#define try								\
  {									\
    int exception;							\
    struct _exceptionContext_ _localExceptionContext_ = {0};		\
    _localExceptionContext_.next = _currentExceptionContext_;		\
    _currentExceptionContext_ = &_localExceptionContext_;		\
    _ensure_pointers_as_exceptions_;					\
    if (!(exception=setjmp(_currentExceptionContext_->context))) {

#define catch(except)							\
    } else if ((int)(except) == exception) {				\
      _currentExceptionContext_ = _currentExceptionContext_->next;

#define catch_any						\
    } else {							\
      _currentExceptionContext_ = _currentExceptionContext_->next;

#define endtry								\
    }									\
    if (_currentExceptionContext_ == &_localExceptionContext_)		\
      _currentExceptionContext_ = _currentExceptionContext_->next;	\
  }

#ifdef DEBUG_THROW

#ifndef __func__
#if (defined __GNUC__ && __GNUC__ >= 2 && \
     __GNUC_MINOR__ >= (defined __cplusplus ? 6 : 4))
#  define __func__ __PRETTY_FUNCTION__
#else
#  define __func__ "?func?"
#endif
#endif

extern void _exceptionThrowDebug_(char const*, int, char const*,
                                  char const*, int);
#define throw(exception) \
          _exceptionThrowDebug_(__FILE__, __LINE__, __func__, \
                                _string_(exception), (int)(exception))
#else

extern void _exceptionThrow_(int);
#define throw(exception) _exceptionThrow_((int)(exception))

#endif /* DEBUG_THROW */

/* pointer protection */

#define protectPtr(ptr, fct)					\
  struct _protectedPointer_ _concat_(_protected_, ptr) =	\
    _newProtectedPointer_(&_concat_(_protected_, ptr),		\
			  (void*)ptr,				\
			  (void (*)(void *))fct);

#define unprotectPtr(pointer)						      \
  do {									      \
    if (_currentExceptionContext_ && _currentExceptionContext_->ptr &&	      \
        _currentExceptionContext_->ptr->ptr == (void*)pointer)		      \
        _currentExceptionContext_->ptr = _currentExceptionContext_->ptr->next;\
  } while(0)

#endif
