/* Template for a TYPE definition
   - replace parent by the type name
   - replace object by the inherited type name
   - replace interface_example by the inherited interface name
   - add more parent methods implementation
   - add more parent methods initialization
   - add more parent_new??? constructors implementation
   - remove this comment

   Special cases:
   - no *new* interface:
     . remove parent_interfaces
   - abstract type:
     . remove parent_new constructor
   - final type
     . replace parent_p.h by parent.h
   - root type
     . remove everything related to object
     . remove SUPER and AS_SUPER
     . define default parent_interfaces
     . define default parent_cast
   - no thread:
     . use object as root class or
     . remove/define _USE_TLS -/to an empty definition
   - with threads:
     . replace/define _USE_TLS by/to __thread (Thread Local Storage)
 */
#include <string.h>
#include <assert.h>
#include "parent_p.h"

#define TYPE          struct parent
#define INTERFACE     struct parent_interface
#define SELF        ((struct parent_attribute*)self)
#define AS_SELF(a)  ((struct parent_attribute*)(a) )
#define SUPER       ((struct object          *)self)
#define AS_SUPER(a) ((struct object          *)(a) )

static INTERFACE interface;

static void*
parent_interfaces(TYPE* self, void *ref_i)
{
  if (ref_i == &interface_example_interface)
    return &self->i->method2;
  
  /* más interfaces aquí */

  return interface.super->interface(SUPER,ref_i);
}

static TYPE*
parent_init(TYPE *self)
{
  /* inicialización de atributos  */
  return self;
}

static void
method1(TYPE *self)
{

}

static void
method2(TYPE *self)
{

}



static void
parent_initialize(void)
{
  struct object_interface *super_interface = object_interface();

  memcpy(&interface, super_interface, sizeof *super_interface);
  memcpy(&interface.method2, &interface_example_interface,sizeof interface_example_interface);
  
  interface.super        = super_interface;
  interface.interface    = parent_interfaces;
  interface.init         = parent_init;
  interface.method1 = method1;
  interface.method2 = method2;
  /* put parent methods initialization here */
}

/*
 * Public constructors
 */

INTERFACE*
parent_interface(void)
{
  if (!interface.interface)
    parent_initialize();
  
  return &interface;
}

TYPE*
parent_new(void)
{
  TYPE *self = parent_interface()->alloc(sizeof *SELF);
  assert(self);
  
  self->i = &interface;
  
  return parent_init(self);
}
