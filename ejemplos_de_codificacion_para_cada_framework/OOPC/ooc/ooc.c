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

#include <setjmp.h>

#define IMPLEMENTATION

#include <ooc.h>

/*
  ----------------------------------------------------
  delete (polymorphic) objects
  ----------------------------------------------------
*/

void
ooc_delete(void *const obj)
{
  (obj ?
   (typeid((t_object*)obj)->class->_object(base_cast((t_object*)obj)),
    free(base_cast((t_object*)obj))) :
   (void)0);
}

/*
  ----------------------------------------------------
  link subobjects to their virtual table and type info
  ----------------------------------------------------
*/

void
_ooc_updateRef_(t_object *const obj, struct _ooc_type_info const*const info)
{
  t_object const*const refObj = info->obj;
  /* static int lvl = 0; */
  int i;

  /* printf("SUBOBJECT %s\n", info->name); ++lvl; */

  /* recurse on first superclass */
  if (info->super) {
    /* indentPrintf(stdout, lvl, "SUPER "); */
    _ooc_updateRef_(obj, info->super);
  }

  /* for each extra superclass */
  for(i=0; i<info->extraSuper; i++) {
    size_t const superObjOffset = info->extraOffset[i];

    t_object const*const superRefObj = (void*)((char*)refObj + superObjOffset);

    size_t const superVtabOffset = (size_t)superRefObj->__vptr -
                                   (size_t)refObj->__vptr;

    t_object *const superObj = (void*)((char*)obj + superObjOffset);

    superObj->__iptr = (void*)((char*)obj->__vptr + superVtabOffset);

    offsetOf(superObj) = offsetOf(obj) + superObjOffset;

    /* indentPrintf(stdout, lvl, "EXTRA "); */
    _ooc_updateRef_(superObj, superObj->__iptr->info);
  }

  /* --lvl; */
}

/*
  -----------------------------------------------
  dynamic casting of one (super)object to another
  -----------------------------------------------
  return NULL if
    the destination superobject isn't in subobject
  OR
    the destination superobject appears more than once in subobject
*/

static struct _ooc_type_info const* searchedType = NULL;
static t_object const *found=NULL;
static jmp_buf there;

static void
searchType(t_object const*const obj, struct _ooc_type_info const*const info)
{
  /* found destination object */
  if (info == searchedType) {
    /* found more than once, break search */
    if (found) { found = NULL; longjmp(there,1); }
    found = obj;
  }

  /* recurse on first superclass */
  if (info->super) searchType(obj, info->super);
  
  /* for each extra superclass */
  {
    int i;
    t_object const* super;

    for(i=0; i<info->extraSuper; i++) {
      super = (void*)((char*)obj + info->extraOffset[i]);
      searchType(super, super->__iptr->info);
    }
  }
}

void*const
_ooc_castDynamic_(t_object const*const obj, struct _ooc_class_object const*const class)
{
  found = NULL;

  if (class && class->__vptr) {
    searchedType = ((struct _ooc_vtbl_object*)class->__vptr)->info;
    if (obj && obj->__iptr && searchedType) {
      if (!setjmp(there)) searchType(base_cast(obj), typeid(obj));
    }
  }

  return (void*const)found;
}

/*
  ----------------------------------------------------
  strdup (Not ISO C89)
  ----------------------------------------------------
*/

#ifdef ALLOW_STRDUP
char*
strdup(char const* str)
{
  char *s = malloc(strlen(str)+1);
  if ( s != NULL ) strcpy(s, str);
  return s;
}
#endif
