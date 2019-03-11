#undef  NDEBUG
#define NDEBUG 1

/*
 o---------------------------------------------------------------------o
 |
 | OOC-S root class
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

#include <stdlib.h>
#include <assert.h>
#include "object_p.h"
#include "clonable.h"
#include "autorelease.h"

#define TYPE      struct object
#define INTERFACE struct object_interface
#define SELF    ((struct object_attribute*)self)

static INTERFACE interface;

static void*
object_interfaces(TYPE *self, void *ref_i)
{
  return 0; (void)self; (void)ref_i;
}

static void*
object_cast(TYPE *self, void *ref_i)
{
  INTERFACE *self_i = self->i;

  while(self_i && self_i != ref_i)
    self_i = (INTERFACE*)self_i->super;

  return self_i ? self : 0;
}

static int
object_equal(TYPE *self, TYPE *other)
{
  return self == other;
}

static size_t
object_hash(TYPE *self)
{
  return ((size_t)self >> 2) * 2621124293u + 1;
}

static TYPE*
object_alloc(size_t size)
{
  TYPE *self = malloc(size);

  assert(self && size >= sizeof(struct object));
  SELF->refcnt = REFCNT_UNIT();
  return self;
}

static void
object_free(TYPE *self)
{
  assert(SELF->refcnt == REFCNT_UNIT());
  free(self);
}

static TYPE*
object_retain(TYPE *self)
{
  switch(SELF->refcnt) {
  case REFCNT_STATIC():
    break;

  case REFCNT_AUTO(): {
    struct clonable_interface *clonable_i = INTERFACE_CAST(self,clonable);
    assert(clonable_i);
    self = (TYPE*)clonable_i->clone((struct clonable*)self);
    } break;

  case REFCNT_LAST():
    assert(!"Too many retain counts");

  default:
    ++SELF->refcnt;
  }

  return self;
}

static void
object_release(TYPE *self)
{
  switch(SELF->refcnt) {
  case REFCNT_STATIC():
    break;

  case REFCNT_AUTO():
    self->i->deinit(self);
    break;
    
  case REFCNT_UNIT(): {
    struct object_interface *self_i = self->i;
    self_i->free(self_i->deinit(self));
  } break;
  
  default:
    --SELF->refcnt;
  }
}

static TYPE*
object_autorelease(TYPE *self)
{
  switch(SELF->refcnt) {
  case REFCNT_STATIC():
    break;

  case REFCNT_AUTO(): {
    struct clonable_interface *clonable_i = INTERFACE_CAST(self,clonable);
    assert(clonable_i);
    self = (TYPE*)clonable_i->clone((struct clonable*)self);
  }

  default:
    assert(autorelease_pool);
    autorelease_pool->i->addObject(autorelease_pool,self);
  }

  return self;
}

static TYPE*
object_deinit(TYPE *self)
{
  return self;
}

static void
object_initialize(void)
{
  interface.interface   = object_interfaces;
  interface.cast        = object_cast;
  interface.equal       = object_equal;
  interface.hash        = object_hash;
  interface.alloc       = object_alloc;
  interface.free        = object_free;
  interface.retain      = object_retain;
  interface.release     = object_release;
  interface.autorelease = object_autorelease;
  interface.deinit      = object_deinit;
}

/*
 * Public constructors
 */

INTERFACE*
object_interface(void)
{
  if (!interface.interface)
    object_initialize();
  
  return &interface;
}
