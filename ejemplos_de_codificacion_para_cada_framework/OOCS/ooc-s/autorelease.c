#undef  NDEBUG
#define NDEBUG 1

/*
 o---------------------------------------------------------------------o
 |
 | OOC-S autorelease pool
 |
 o---------------------------------------------------------------------o
 |
 | Object Oriented C - Simplified release
 |
 | Copyright (c) 2007+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/oopc.html#OOC-S
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the Simplified Object Oriented C package.
 |
 | OOC-S is free software; you can redistribute it and/or modify it
 | under the terms of the GNU Lesser General Public License as
 | published by the Free Software Foundation; either version 2.1 of
 | the License, or (at your option) any later version.
 |
 | OOC-S is distributed in the hope that it will be useful, but
 | WITHOUT ANY WARRANTY; without even the implied warranty of
 | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 | Lesser General Public License for more details.
 |
 | You should have received a copy of the GNU Lesser General Public
 | License along with this library; if not, write to the Free
 | Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 | Boston, MA 02110-1301 USA
 |
 o---------------------------------------------------------------------o
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "autorelease.h"
#include "object_p.h"

#define TYPE          struct autorelease
#define INTERFACE     struct autorelease_interface
#define SELF        ((struct autorelease_attribute*)self)
#define AS_SELF(a)  ((struct autorelease_attribute*)(a) )
#define SUPER       ((struct object               *)self)
#define AS_SUPER(a) ((struct object               *)(a) )

#define AUTORELEASE_INIT 512
#define AUTORELEASE_RATE 2.0
#define AUTORELEASE_WARN 1000000

#define ARR_LEN(a) (sizeof((a))/sizeof(*(a)))

/* final type */
struct autorelease_attribute {
  struct object_attribute object;
  struct autorelease *prv;
  struct object **stk;
  struct object **top;
  struct object **end;
  struct object  *tmp;
  struct object *_stk[16];
};

static INTERFACE interface;

static void
enlarge(struct autorelease_attribute *pool)
{
  size_t size = pool->top - pool->stk;
  size_t new_size;
  struct object **stk;

  if (pool->stk == pool->_stk) {
    new_size = AUTORELEASE_INIT;
    stk = malloc(sizeof *stk * new_size);
    if (stk) memcpy(stk, pool->stk, sizeof *stk * size);
  } else {
    new_size = size * AUTORELEASE_RATE;    
    stk = realloc(pool->stk, sizeof *stk * new_size);
  }

  assert(stk);
  
  pool->stk = stk;
  pool->top = stk + size;
  pool->end = stk + new_size;

  if (size >= AUTORELEASE_WARN)
    fprintf(stderr,"autorelease pool at %p hold %lu autoreleased objects",
            (void*)pool, (unsigned long)size);
}

static TYPE*
autorelease_init(TYPE *self)
{
  assert(!interface.super->init);

  SELF->stk = SELF->_stk;
  SELF->top = SELF->_stk;
  SELF->end = SELF->_stk + ARR_LEN(SELF->_stk);
  SELF->tmp = 0;
  SELF->prv = autorelease_pool;

  return autorelease_pool = self;
}

static TYPE*
autorelease_deinit(TYPE *self)
{
  struct object *obj;

  assert(autorelease_pool == self);

  if (SELF->tmp)
    obj = SELF->tmp, obj->i->release(obj);

  while(SELF->top-- > SELF->stk)
    obj = *SELF->top, obj->i->release(obj);

  if (SELF->stk != SELF->_stk)
    free(SELF->stk);

  autorelease_pool = SELF->prv;

  return self;
}

static TYPE*
autorelease_retain(TYPE *self)
{
  assert(!"autorelease pool retain is forbidden");
  return self; /* never reached */
}

static TYPE*
autorelease_autorelease(TYPE *self)
{
  assert(!"autorelease pool autorelease is forbidden");
  return self; /* never reached */
}

static void
autorelease_addObject(TYPE *self, struct object *obj)
{
  if (SELF->top == SELF->end) {
    SELF->tmp = obj;
    enlarge(SELF);
    SELF->tmp = 0;
  }

  *SELF->top++ = obj;
}

static void
autorelease_initialize(void)
{
  struct object_interface *super_interface = object_interface();

  memcpy(&interface, super_interface, sizeof *super_interface);
  
  interface.super       = super_interface;
  interface.init        = autorelease_init;
  interface.deinit      = autorelease_deinit;
  interface.retain      = autorelease_retain;
  interface.autorelease = autorelease_autorelease;
  interface.addObject   = autorelease_addObject;
}

/*
 * Public constructors and global state
 */

_USE_TLS TYPE *autorelease_pool = 0;

INTERFACE*
autorelease_interface(void)
{
  if (!interface.interface)
    autorelease_initialize();

  return &interface;
}

TYPE*
autorelease_new(void)
{
  TYPE *self = autorelease_interface()->alloc(sizeof *SELF);
  assert(self);

  self->i = &interface;

  return autorelease_init(self);
}
