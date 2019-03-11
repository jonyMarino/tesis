/* Template for a TYPE definition
   - replace xxxxx by the type name
   - replace yyyyy by the inherited type name
   - replace zzzzz by the inherited interface name
   - add more xxxxx methods implementation
   - add more xxxxx methods initialization
   - add more xxxxx_new??? constructors implementation
   - remove this comment

   Special cases:
   - no *new* interface:
     . remove xxxxx_interfaces
   - abstract type:
     . remove xxxxx_new constructor
   - final type
     . replace xxxxx_p.h by xxxxx.h
   - root type
     . remove everything related to yyyyy
     . remove SUPER and AS_SUPER
     . define default xxxxx_interfaces
     . define default xxxxx_cast
   - no thread:
     . use object as root class or
     . remove/define _USE_TLS -/to an empty definition
   - with threads:
     . replace/define _USE_TLS by/to __thread (Thread Local Storage)
 */
#include <string.h>
#include <assert.h>
#include "xxxxx_p.h"

#define TYPE          struct xxxxx
#define INTERFACE     struct xxxxx_interface
#define SELF        ((struct xxxxx_attribute*)self)
#define AS_SELF(a)  ((struct xxxxx_attribute*)(a) )
#define SUPER       ((struct yyyyy          *)self)
#define AS_SUPER(a) ((struct yyyyy          *)(a) )

static INTERFACE interface;

static void*
xxxxx_interfaces(TYPE* self, void *ref_i)
{
  if (ref_i == &zzzzz_interface)
    return &self->i->zzzzz_1st_method;
  
  /* put extra *new* interface here */

  return interface.super->interface(SUPER,ref_i);
}

static TYPE*
xxxxx_init(TYPE *self)
{
  interface.super->init(SUPER);
  /* put default xxxxx attributes initialization here
     SELF->attribute_example = 0;
  */
  return self;
}

/* put xxxxx method implementation here */

/* instance methods should be defined as:

   static ret_type xxxxx_method_name(TYPE* [, ..]) { .. }

   where most of the time ret_type is TYPE* or void
*/

/* type methods should be defined as:

   static ret_type xxxxx_method_name([..]) { .. }

   where most of the time ret_type is TYPE*
*/

static void
xxxxx_initialize(void)
{
  struct yyyyy_interface *super_interface = yyyyy_interface();

  memcpy(&interface, super_interface, sizeof *super_interface);
  memcpy(&interface.zzzzz_1st_method, &zzzzz_interface,sizeof zzzzz_interface);
  
  interface.super        = super_interface;
  interface.interface    = xxxxx_interfaces;
  interface.init         = xxxxx_init;
  interface.zzzzz_method = xxxxx_method;
  /* put xxxxx methods initialization here */
}

/*
 * Public constructors
 */

INTERFACE*
xxxxx_interface(void)
{
  if (!interface.interface)
    xxxxx_initialize();
  
  return &interface;
}

TYPE*
xxxxx_new(void)
{
  TYPE *self = xxxxx_interface()->alloc(sizeof *SELF);
  assert(self);
  
  self->i = &interface;
  
  return xxxxx_init(self);
}
