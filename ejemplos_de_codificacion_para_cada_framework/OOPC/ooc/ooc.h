#if !defined(OOC_H) || defined(IMPLEMENTATION)
#define OOC_H

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
#  error "ooc.h needs ISO C compiler to work properly"
#endif

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* ooc uses exceptions */
#include <ooexception.h>

/* some useful macros */

#define _makeString_(a) #a
#define _string_(a) _makeString_(a)

#define _makeConcat_(a,b) a ## b
#define _concat_(a,b) _makeConcat_(a,b)

/*
  -----------------
  new generic type
  -----------------
*/

#define t_OBJECT _concat_(t_,OBJECT) /* object type */

/*
  --------------------
  macros for interface
  --------------------
*/

#define OBJECT_INTERFACE                                        \
typedef union {                                                 \
  struct _concat_(_ooc_vtbl_,OBJECT) const*_CONST__ __vptr;     \
  struct _ooc_vtbl_object _CONST_*_CONST_ __iptr;               \
  struct {

#define OBJECT_METHODS                          \
  } m;                                          \
} t_OBJECT;                                     \
struct _concat_(_ooc_vtbl_,OBJECT) {

#define BASEOBJECT_INTERFACE                    \
  OBJECT_INTERFACE                              \
  t_object _CONST__ private(_);

#define BASEOBJECT_METHODS                      \
  OBJECT_METHODS                                \
  struct _ooc_vtbl_object _CONST_ private(_);

#define INHERIT_MEMBERS_OF(obj) \
  _concat_(t_,obj) obj

#define INHERIT_METHODS_OF(obj) \
  struct _concat_(_ooc_vtbl_,obj) obj

#define CLASS_INTERFACE                         \
  ABSTRACTCLASS_INTERFACE                       \
  t_OBJECT*const classMethod(alloc);

#define ABSTRACTCLASS_INTERFACE                                 \
extern struct _concat_(_ooc_class_,OBJECT) OBJECT;              \
struct _concat_(_ooc_class_,OBJECT) {                           \
  struct _concat_(_ooc_vtbl_,OBJECT) const*const __vptr;        \
  t_OBJECT classMethod(OBJECT);                                 \
  void method(_concat_(_,OBJECT));

#define ENDOF_INTERFACE };

/*
  -------------------------
  macros for implementation
  -------------------------
*/

#ifdef IMPLEMENTATION

#define OBJECT_IMPLEMENTATION                                            \
static struct _concat_(_ooc_vtbl_,OBJECT) _concat_(_ooc_vtbl_,OBJECT);   \
static t_OBJECT _concat_(_ooc_obj_,OBJECT) = { &_concat_(_ooc_vtbl_,OBJECT) };\
static struct _ooc_type_info _concat_(_ooc_info_,OBJECT) = {             \
  _string_(OBJECT),                                                      \
  (struct _ooc_class_object const*const) &OBJECT,                        \
  (t_object const*const) &_concat_(_ooc_obj_,OBJECT)                     \
};                                                                       \
static struct _concat_(_ooc_vtbl_,OBJECT) _concat_(_ooc_vtbl_,OBJECT) = {

#define BASEOBJECT_IMPLEMENTATION               \
  OBJECT_IMPLEMENTATION                         \
  { &_concat_(_ooc_info_,OBJECT), 0 },

#define SUPERCLASS(obj) { 0 }

#define ABSTRACTCLASS_IMPLEMENTATION                            \
initClassDecl();                                                \
dtorDecl();                                                     \
t_OBJECT classMethodDecl(OBJECT)                                \
{                                                               \
  return _concat_(_ooc_obj_,OBJECT);                            \
}                                                               \
t_OBJECT classMethodDecl(_concat_(OBJECT,_once))                \
{                                                               \
  methodName(initClass)();                                      \
  /*fputs(_string_(OBJECT)".initClass() done\n", stderr);*/     \
  OBJECT.OBJECT = methodName(OBJECT);                           \
  return _concat_(_ooc_obj_,OBJECT);                            \
}                                                               \
struct _concat_(_ooc_class_,OBJECT) OBJECT = {                  \
  &_concat_(_ooc_vtbl_,OBJECT),                                 \
  methodName(_concat_(OBJECT,_once)),                           \
  methodName(_concat_(_,OBJECT)),

#define CLASS_IMPLEMENTATION                                            \
t_OBJECT classMethodDecl(*const alloc)                                  \
{                                                                       \
  t_OBJECT *const this = malloc(sizeof(t_OBJECT));                      \
  if (!this) throw(ooc_bad_alloc);                                      \
  objCopy(*this, _concat_(_ooc_obj_,OBJECT));                           \
  return this;                                                          \
}                                                                       \
t_OBJECT classMethodDecl(*const alloc_once)                             \
{                                                                       \
  t_OBJECT const _this = OBJECT.OBJECT();                               \
  t_OBJECT *const this = malloc(sizeof(t_OBJECT));                      \
  if (!this) throw(ooc_bad_alloc);                                      \
  objCopy(*this, _this);                                                \
  OBJECT.alloc = methodName(alloc);                                     \
  return this;                                                          \
}                                                                       \
ABSTRACTCLASS_IMPLEMENTATION                                            \
  methodName(alloc_once),

#define ENDOF_IMPLEMENTATION };

#endif

/*
  -------------------------
  macros for initialization
  -------------------------
*/

#ifdef IMPLEMENTATION

#define initSuper(SUPER)                                                      \
do {                                                                          \
  /* initialize super class */                                                \
  _concat_(t_,SUPER) const super = SUPER.SUPER();                             \
                                                                              \
  /*fputs(_string_(OBJECT)".initSuper("_string_(SUPER)") done\n", stderr);*/  \
                                                                              \
  /* copy superclass obj */                                                   \
  objCopy(_concat_(_ooc_obj_,OBJECT).m.SUPER, super);                         \
                                                                              \
  /* copy superclass vtbl */                                                  \
  objCopy( _concat_(_ooc_vtbl_,OBJECT).SUPER,                                 \
          *_concat_(_ooc_obj_,OBJECT).m.SUPER.__vptr);                        \
                                                                              \
  /* first superclass ? */                                                    \
  if (0 == offsetof(t_OBJECT, m.SUPER)) {                                     \
    /* assign direct superclass (cast away lvalue const) */                   \
    (*(struct _ooc_type_info **)&_concat_(_ooc_info_,OBJECT).super) =         \
                      (void*)_concat_(_ooc_obj_,OBJECT).m.SUPER.__iptr->info; \
                                                                              \
    /* restore __vptr */                                                      \
    _concat_(_ooc_obj_,OBJECT).__iptr = (void*)&_concat_(_ooc_vtbl_,OBJECT);  \
                                                                              \
    /* restore __iptr.info (cast away lvalue const) */                        \
    (*(struct _ooc_type_info**)&_concat_(_ooc_obj_,OBJECT).__iptr->info) =    \
                                              &_concat_(_ooc_info_,OBJECT);   \
                                                                              \
   /* update reference of obj and vtbl */                                     \
    _ooc_updateRef_((t_object *const)&_concat_(_ooc_obj_,OBJECT).m.SUPER,     \
                    _concat_(_ooc_obj_,OBJECT).m.SUPER.__iptr->info->super);  \
  } else {                                                                    \
    /* check number of class's extrasuperclass */                             \
    assert( _concat_(_ooc_info_,OBJECT).extraSuper<_OBJECT_MAXEXTRASUPER_-1 &&\
                                               "too many extra superclasses");\
                                                                              \
    /* store extra superclass offset (cast away lvalue const) */              \
    ((size_t*)_concat_(_ooc_info_,OBJECT).extraOffset)                        \
     [_concat_(_ooc_info_,OBJECT).extraSuper] = offsetof(t_OBJECT, m.SUPER);  \
                                                                              \
    /* increment number of extra superclass (cast away lvalue const) */       \
    ++*(size_t*)&_concat_(_ooc_info_,OBJECT).extraSuper;                      \
                                                                              \
    /* update obj's pointer to vtbl */                                        \
    _concat_(_ooc_obj_,OBJECT).m.SUPER.__iptr =                               \
                                   (void*)&_concat_(_ooc_vtbl_,OBJECT).SUPER; \
                                                                              \
    /* update superclass offset */                                            \
     _concat_(_ooc_obj_,OBJECT).m.SUPER.__iptr->offset =                      \
                                                 offsetof(t_OBJECT, m.SUPER); \
                                                                              \
   /* update reference of obj and vtbl */                                     \
    _ooc_updateRef_((t_object *const)&_concat_(_ooc_obj_,OBJECT).m.SUPER,     \
                    _concat_(_ooc_obj_,OBJECT).m.SUPER.__iptr->info);         \
  }                                                                           \
                                                                              \
} while(0)

#define objDefault(member) \
        _concat_(_ooc_obj_,OBJECT).m.member

#define overload(super_fct) \
        _concat_(_ooc_vtbl_,OBJECT).super_fct

#define sub_cast(obj, objclass) \
        static_cast(obj, objclass, OBJECT)

#endif

/*
  ----------------------------
  macros for scope declaration
  ----------------------------
*/

#define public(decl) decl

#ifdef IMPLEMENTATION

#undef  private
#define private(decl) decl
#else
#define private(decl) _concat_(decl,                            \
                      _concat_(__ooc_private_,                  \
                      _concat_(__LINE__,__STDC_VERSION__)))
#endif

/*
  -----------------------------------------------
  macros for object identification, cast & delete
  -----------------------------------------------
*/

#define super(obj, super) \
        (&((obj)->m.super))

#define className(obj) \
        (typeid(obj)->name)

#define isA(obj, class) \
        ((obj)->__vptr == (void*)(class).__vptr)

#define offsetOf(obj) \
        ((obj)->__iptr->offset)

#define methodAddr(obj, msg) \
        ((obj)->__vptr->msg)

#define typeid(obj) \
        (((t_object*)base_cast(obj))->__iptr->info)

#define base_cast(obj) \
        ((void*const)((char*)(obj) - offsetOf(obj)))

#define super_cast(obj, super) \
        super(obj, super)

#define static_cast(obj, objclass, subclass) \
        ((_concat_(t_,subclass)*const)((char*)(obj) - \
         offsetof(_concat_(t_,subclass),m.objclass)))

#define dynamic_cast(obj, class) \
        ((_concat_(t_,class)*)_ooc_castDynamic_((void*)(obj), (void*)&(class)))

#define delete(obj)							\
        ((obj) ?							\
         (typeid(obj)->class->_object(base_cast(obj)),	                \
          free(base_cast(obj))):					\
         (void)0)

/*
  -----------------------------
  macros for method declaration
  -----------------------------
*/

#ifdef IMPLEMENTATION
#  undef  classMethod
#  undef  classMethod_
#  undef  method
#  undef  method_
#  undef  constMethod
#  undef  constMethod_

#  define classMethod(fct) \
          (*fct)(void)
#  define classMethod_(fct) \
          (*fct)(

#  define method(fct) \
          (*fct) (t_OBJECT *const)
#  define method_(fct) \
          (*fct) (t_OBJECT *const,
#  define constMethod(fct) \
          (*fct) (t_OBJECT const*const)
#  define constMethod_(fct) \
          (*fct) (t_OBJECT const*const,

#  define initClassDecl() \
          void classMethodDecl(initClass)

#  define dtorDecl() \
          void methodDecl(_concat_(_,OBJECT))

#  define classMethodDecl(fct) \
          static methodName(fct)(void)
#  define classMethodDecl_(fct) \
          static methodName(fct)(

#  define methodDecl(fct) \
          static methodName(fct)(t_OBJECT *const this)
#  define methodDecl_(fct) \
          static methodName(fct)(t_OBJECT *const this,
#  define constMethodDecl(fct) \
          static methodName(fct)(t_OBJECT const*const this)
#  define constMethodDecl_(fct) \
          static methodName(fct)(t_OBJECT const*const this,

#  define methodOvldDecl(fct, obj) \
          static methodOvldName(fct,obj)(_concat_(t_,obj) *const this)
#  define methodOvldDecl_(fct, obj) \
          static methodOvldName(fct,obj)(_concat_(t_,obj) *const this,
#  define constMethodOvldDecl(fct, obj) \
          static methodOvldName(fct,obj)(_concat_(t_,obj) const*const this)
#  define constMethodOvldDecl_(fct, obj) \
          static methodOvldName(fct,obj)(_concat_(t_,obj) const*const this,

#  define methodName(fct) \
          _concat_(_concat_(fct,_m_),OBJECT)
#  define methodOvldName(fct, obj) \
          _concat_(_concat_(fct,_m_),_concat_(_concat_(obj,_),OBJECT))

#else
#  define classMethod(fct) \
          (*const fct)(void)
#  define classMethod_(fct) \
          (*const fct)(

#  define method(fct) \
          (*const fct) (t_OBJECT *const)
#  define method_(fct) \
          (*const fct) (t_OBJECT *const,
#  define constMethod(fct) \
          (*const fct) (t_OBJECT const*const)
#  define constMethod_(fct) \
          (*const fct) (t_OBJECT const*const,
#endif

/*
  --------------------------
  macros for message passing
  --------------------------
*/

/* object messages */
#define sendMsg(obj, msg) \
        ((obj)->__vptr->msg)(obj)
#define sendMsg_(obj, msg) \
        ((obj)->__vptr->msg)(obj,

/* class messages */
#define sendCMsg(obj, class, msg) \
        ((class).__vptr->msg)(obj)
#define sendCMsg_(obj, class, msg) \
        ((class).__vptr->msg)(obj,

/*
  arguments closure
  #undef __ or use
  _concat_(_,_concat_(_,token))
  if you want to build token with __
*/

#define __ )

/*
  --------------------------
  macros for generic objects
  --------------------------
*/

#define GENERIC(obj) _concat_(gTypePrefix, obj)
#define GENERIC_DTOR(obj) _concat_(_,GENERIC(obj))

/*
  -----------
  base object
  -----------
*/

/* maximum number of super classes */
#define _OBJECT_MAXEXTRASUPER_ 4

/* disable _CONST__ if requested by user */
#ifdef ALLOW_OBJCOPY
#  define _CONST__
#  define objCopy(a,b) ((a) = (b))
#else
#  define _CONST__ const
#  define objCopy(a,b) memcpy(&(a), &(b), sizeof(a))
#endif

/* disable _CONST_ in implementation */
#ifdef IMPLEMENTATION
#  undef  _CONST_
#  define _CONST_
#else
#  undef  _CONST_
#  define _CONST_ _CONST__
#endif

#ifndef _OOC_INCLUDE_ONCE_
#define _OOC_INCLUDE_ONCE_

/* object type (public) */
typedef union {
  struct _ooc_vtbl_object  const *_CONST__ __vptr;
  struct _ooc_vtbl_object _CONST_*_CONST_  __iptr;
} t_object;

/* object virtual table type (private) */
struct _ooc_vtbl_object {
  struct _ooc_type_info const*_CONST_ info;
  size_t offset;
};

/* object class type (private) */
struct _ooc_class_object {
  struct _ooc_vtbl_object const*const __vptr;
  t_object (*const object) (void);
  void (*const _object)  (t_object *const);
};

/* object RTTI (private) */
struct _ooc_type_info {
  char const*const name;
  struct _ooc_class_object const*_CONST_ class;
  t_object const*_CONST_ obj;
  struct _ooc_type_info const*_CONST_ super;
  size_t _CONST_ extraSuper;
  size_t _CONST_ extraOffset[_OBJECT_MAXEXTRASUPER_];
};

#endif

/*
  ------------
  debug info
  ------------
*/

#if defined(DEBUG_CALL) || defined(DEBUG_MEM) || defined(DEBUG_OBJ)
#  include <oodebug.h>
#endif

#ifndef DEBUG_MEM
/* for compatibility with oodebug.h */
extern char *strdup(const char*); /* not ISO C, but in libc or ooc.c */
#endif

/*
  ------------
  declarations
  ------------
*/

/*
  Extern declarations
*/

extern void       _ooc_updateRef_   (t_object *const,
				     struct _ooc_type_info const*const);
extern void*const _ooc_castDynamic_ (t_object const*const,
				     struct _ooc_class_object const*const);
extern void        ooc_delete       (void *const);

#endif
