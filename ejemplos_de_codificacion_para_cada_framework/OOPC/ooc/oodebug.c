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
#include <stdarg.h>
#include <ctype.h>

/*
  ------------------------------------------
  check & display dynamic memory information
  ------------------------------------------
*/

#ifdef DEBUG_MEM

#undef malloc
#undef calloc
#undef realloc
#undef free
#undef strdup

typedef struct hdr_ {
  struct hdr_ *next;
  struct hdr_ *prev;
  size_t       size;
  char const  *file;
  char const  *func;
  int          line;
} hdr_t;

static unsigned const mem_tag  =  0xa5a5a5a5;
static unsigned const mem_gat  = ~0xa5a5a5a5;
static size_t         mem_size = 0;
static hdr_t         *mem_list = NULL;

#define ALG_SIZE sizeof(double)
#define HDR_SIZE sizeof(hdr_t)
#define TAG_SIZE sizeof(mem_tag)

#define RESERVED_SIZE (((HDR_SIZE+TAG_SIZE+ALG_SIZE-1)/ALG_SIZE)*ALG_SIZE)

#define USR_2_HDR(a) (((char*)(a))-RESERVED_SIZE)
#define HDR_2_USR(a) (((char*)(a))+RESERVED_SIZE)

#define BEG_TAG(a) ((char*)(a)+RESERVED_SIZE-TAG_SIZE)
#define END_TAG(a) ((char*)(a)+RESERVED_SIZE+(a)->size)

#define SET_TAGS(a) (memcpy(BEG_TAG(a), &mem_tag, TAG_SIZE), \
                     memcpy(END_TAG(a), &mem_tag, TAG_SIZE))

#define CLR_TAGS(a) (memcpy(BEG_TAG(a), &mem_gat, TAG_SIZE), \
                     memcpy(END_TAG(a), &mem_gat, TAG_SIZE))

#define CHK_TAGS(a) (memcmp(BEG_TAG(a), &mem_tag, TAG_SIZE) || \
                     memcmp(END_TAG(a), &mem_tag, TAG_SIZE))

static void mem_err(void *p, char const* fil, int lin, char const* fun);
static void mem_add(hdr_t *p);
static void mem_del(hdr_t *p);

size_t
ooc_usedMem(void)
{
  return mem_size;
}

int
ooc_checkMem(char const* fil, int lin, char const* fun, void *ptr, FILE *fp)
{
  hdr_t *p;
  int ret = 0;

  if (!ptr) {
    fprintf(fp, "(nil) pointer - %s(%d):%s\n", fil, lin, fun);
    return -1;
  }
  
  p = (hdr_t*)USR_2_HDR(ptr);

  if (memcmp(BEG_TAG(p), &mem_tag, TAG_SIZE)) {
    fprintf(fp, "Heap corrupted @ beginning of %-10p - %s(%d):%s\n",
	    ptr, fil, lin, fun);
    ret = -1;
  }

  if (memcmp(END_TAG((hdr_t*)p), &mem_tag, TAG_SIZE)) {
    fprintf(fp, "Heap corrupted @ %send of %-10p - %s(%d):%s\n",
	    ret ? "      " : "", ptr, fil, lin, fun);
    ret = -1;
  }

  return ret;
}

void
ooc_displayMem(FILE *fp)
{
  int i;
  hdr_t *p;
  char  *q;

  fprintf(fp,
	 "Index  Address    Size     Begin End   File(Line):Func - Total size %d\n",
          mem_size);

  for(i=0, p=mem_list; p; p=p->next, i++) {
    fprintf(fp, "%-5d  %-10p %-7u", i, HDR_2_USR(p), p->size);

    q = BEG_TAG(p)+TAG_SIZE;
    fprintf(fp, "  %c%c%c%c",
            isprint(q[0]) ? q[0] : '.',
            isprint(q[1]) ? q[1] : '.',
            isprint(q[2]) ? q[2] : '.',
            isprint(q[3]) ? q[3] : '.');
    
    q = END_TAG(p)-4;
    fprintf(fp, "  %c%c%c%c",
            isprint(q[0]) ? q[0] : '.',
            isprint(q[1]) ? q[1] : '.',
            isprint(q[2]) ? q[2] : '.',
            isprint(q[3]) ? q[3] : '.');

    fprintf(fp, "  %s(%d):%s", p->file, p->line, p->func);
    if (CHK_TAGS(p)) fprintf(fp, " **INVALID**");
    putc('\n', fp);
  }
}

void*
ooc_malloc(char const* fil, int lin, char const* fun, size_t size)
{
  hdr_t *p = malloc(RESERVED_SIZE+size+TAG_SIZE);
  if ( p == NULL ) return NULL;
  p->size = size;
  p->file = fil;
  p->func = fun;
  p->line = lin;
  SET_TAGS(p);
  mem_size += size;
  mem_add(p);

  return HDR_2_USR(p);
}

void*
ooc_realloc(char const* fil, int lin, char const* fun, void *ptr, size_t size)
{
  hdr_t *p = ptr;

  if (p) {
    p = (hdr_t*)USR_2_HDR(ptr);
    if (CHK_TAGS(p)) { mem_err(p,fil,lin,fun); return NULL; }
    CLR_TAGS(p);
    mem_size -= p->size;
    mem_del(p);
  }

  p = realloc(p, RESERVED_SIZE+size+TAG_SIZE);
  if ( p == NULL ) return NULL;
  p->size = size;
  p->file = fil;
  p->func = fun;
  p->line = lin;
  SET_TAGS(p);
  mem_size += size;
  mem_add(p);
  return HDR_2_USR(p);
}        

void*
ooc_calloc(char const* fil, int lin, char const* fun, size_t nmemb,size_t size)
{
  void *p = ooc_malloc(fil, lin, fun, nmemb*size);
  if ( p != NULL ) memset(p, 0, nmemb*size);
  return p;
}

char*
ooc_strdup(char const* fil, int lin, char const* fun, char const* str)
{
  char *s = ooc_malloc(fil, lin, fun, strlen(str)+1);
  if ( s != NULL ) strcpy(s, str);
  return s;
}

void
ooc_free(char const* fil, int lin, char const* fun, void *ptr)
{       
  hdr_t *p = (hdr_t*)USR_2_HDR(ptr);
  if (CHK_TAGS(p)) { mem_err(p,fil,lin,fun); return; }
  CLR_TAGS(p);
  mem_size -= p->size;
  mem_del(p);
  free(p);
}

static void
mem_add(hdr_t *p)
{
  p->next = mem_list;
  p->prev = NULL;
  if ( mem_list != NULL ) mem_list->prev = p;
  mem_list = p;
}

static void 
mem_del(hdr_t *p)
{
  if ( p->next != NULL ) 
    p->next->prev = p->prev;
  if ( p->prev != NULL ) 
    p->prev->next = p->next;
  else 
    mem_list = p->next;
}

static void
mem_err(void *p, char const* fil, int lin, char const* fun)
{
  ooc_checkMem(fil, lin, fun, HDR_2_USR(p), stderr);
  if (mem_size>0) ooc_displayMem(stderr);
  exit(EXIT_FAILURE);
}

#endif /* DEBUG_MEM */

/*
  ----------------------------------
  display object & class information
  ----------------------------------
*/

#ifdef DEBUG_OBJ

#define IMPLEMENTATION

#include <ooc.h>

static void
indentPrintf(FILE *fp, int lvl, char const *fmt, ...)
{
  int i;
  va_list ap;

  va_start(ap, fmt);
  for(i=0; i<lvl*2; i++) putc(' ', fp);
  vfprintf(fp, fmt, ap);
  va_end(ap);
}

static void
obj_printInfo(FILE* fp,
	     t_object const*const obj,
	     struct _ooc_type_info const*const info)
{
  static int lvl = 0;

  if (obj->__iptr->info == info && !offsetOf(obj)) {
    indentPrintf(fp, lvl++, "OBJECT %s @ %p\n", info->name, obj);
    indentPrintf(fp, lvl, "ctor  @ %p\n", info->obj);
    indentPrintf(fp, lvl, "info  @ %p\n", info);
    indentPrintf(fp, lvl, "vtbl  @ %p\n", obj->__vptr);
    indentPrintf(fp, lvl, "class @ %p\n", info->class);
  } else {
    indentPrintf(fp, lvl++, "SUPEROBJECT %s @ %p\n", info->name, obj);
    indentPrintf(fp, lvl, "base @ %p (offset = %+d)\n",
		 base_cast(obj), offsetOf(obj));
    indentPrintf(fp, lvl, "info @ %p\n", info);
  }

  if (info->super) obj_printInfo(fp, obj, info->super);

  {
    int i;
    t_object const* super;

    for(i=0; i<info->extraSuper; i++) {
      super = (void*)((char*)obj + info->extraOffset[i]);
      obj_printInfo(fp, super, super->__iptr->info);
    }
  }
  
  --lvl;
}

static void
class_printInfo(FILE* fp, struct _ooc_type_info const*const info)
{
  static int lvl = 0;

  indentPrintf(fp, lvl, "%sCLASS %s @ %p\n",
	       lvl ? "SUPER" : "", info->name, info->class);
  indentPrintf(fp, ++lvl, "ctor  @ %p\n", info->obj);
  indentPrintf(fp, lvl, "info  @ %p\n", info);
  indentPrintf(fp, lvl, "vtbl  @ %p\n", info->obj->__vptr);
    
  if (info->super) class_printInfo(fp, info->super);

  {
    int i;
    t_object const* super;

    for(i=0; i<info->extraSuper; i++) {
      super = (void*)((char*)info->obj + info->extraOffset[i]);
      class_printInfo(fp, super->__iptr->info);
    }
  }
  
  --lvl;
}

void
ooc_printObjInfo(FILE* fp, void const*const obj_)
{
  t_object const*const obj = obj_;

  if (!(obj && obj->__vptr && obj->__vptr->info)) {
    fprintf(fp, "OBJECT? @ %p\n", obj);
    return;
  }

  obj_printInfo(fp, obj, obj->__vptr->info);
}

void
ooc_printClassInfo(FILE* fp, void const*const class_)
{
  struct _ooc_class_object const*const class = class_;

  if (!(class && class->__vptr && class->__vptr->info)) {
    fprintf(fp, "CLASS? @ %p\n", class);
    return;
  }

  class_printInfo(fp, class->__vptr->info);
}

#endif /* DEBUG_OBJ */
