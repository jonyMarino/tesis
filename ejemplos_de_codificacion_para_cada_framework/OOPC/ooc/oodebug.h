#ifndef OODEBUG_H
#define OODEBUG_H

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
#  error "oodebug.h needs ISO C compiler to work properly"
#endif

#include <stdio.h>

/*
  --------------------------
  provide alternate __func__
  --------------------------
*/

#ifndef __func__

#if (defined __GNUC__ && __GNUC__ >= 2 && \
     __GNUC_MINOR__ >= (defined __cplusplus ? 6 : 4))
#  define __func__ __PRETTY_FUNCTION__
#else
#  define __func__ "?func?"
#endif
#endif

/*
  ----------------------
  Debug of function call
  ----------------------
*/

#ifdef DEBUG_CALL

#  define DEBUG_VOID_PROTO char const* _file_, int _line_, char const* _func_
#  define DEBUG_VOID_ARGS  __FILE__, __LINE__, __func__
#  define DEBUG_PROTO      DEBUG_VOID_PROTO,
#  define DEBUG_ARGS       DEBUG_VOID_ARGS,
#  define DEBUG_DISPCALL(fp, msg) \
          fprintf(fp, "%s(%d):%s - %s: %s\n", \
		  _file_, _line_, _func_, __func__, (msg))

#else

#  define DEBUG_VOID_PROTO void
#  define DEBUG_VOID_ARGS
#  define DEBUG_PROTO
#  define DEBUG_ARGS 
#  define DEBUG_DISPCALL(fp, msg)

#endif /* DEBUG_CALL */

/*
  -----------------------
  Debug memory allocation
  -----------------------
*/

#ifdef DEBUG_MEM

#define DEBUG_DISPMEM(fp) (ooc_usedMem()>0 ? ooc_displayMem(fp) : (void)0)

#define malloc(a)    ooc_malloc  (__FILE__,__LINE__,__func__,(a))
#define calloc(a,b)  ooc_calloc  (__FILE__,__LINE__,__func__,(a),(b))
#define realloc(a,b) ooc_realloc (__FILE__,__LINE__,__func__,(a),(b))
#define free(a)      ooc_free    (__FILE__,__LINE__,__func__,(a))
#define strdup(a)    ooc_strdup  (__FILE__,__LINE__,__func__,(a))
#define memchk(a,b)  ooc_checkMem(__FILE__,__LINE__,__func__,(a),(b))

extern void*  ooc_malloc     (char const* file, int line, char const* func,
			      size_t size);
extern void*  ooc_calloc     (char const* file, int line, char const* func,
			      size_t nmemb, size_t size);
extern void*  ooc_realloc    (char const* file, int line, char const* func,
			      void *ptr,size_t size);
extern void   ooc_free       (char const* file, int line, char const* func,
			      void *ptr);
extern char*  ooc_strdup     (char const* file, int line, char const* func,
			      char const* str);
extern int    ooc_checkMem   (char const* fil, int lin, char const* fun,
			      void *ptr, FILE *fp);
extern size_t ooc_usedMem    (void);
extern void   ooc_displayMem (FILE *const fp);

#else

#define DEBUG_DISPMEM(fp)
#define ooc_usedMem() (0)
#define ooc_displayMem(a)
#define memchk(a,b)

#endif /* DEBUG_MEM */

/*
  ----------------------------
  Debug of object construction
  ----------------------------
*/

#ifdef DEBUG_OBJ

  extern void ooc_printObjInfo(FILE*, void const*const);
  extern void ooc_printClassInfo(FILE*, void const*const);

#else

#  define ooc_printObjInfo(a,b)
#  define ooc_printClassInfo(a,b)

#endif /* DEBUG_OBJ */

#endif
