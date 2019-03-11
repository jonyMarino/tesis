/* Template for a TYPE definition
   - replace parent by the type name
   - replace object by the inherited type name
   - replace interface_example by the inherited interface name
   - add more parent methods in the parent_interface definition
   - add more parent_new??? constructors
   - remove this comment

   Special cases:
   - no *new* interface:
     . remove everything related to interface_example
   - abstract type:
     . remove parent_new constructor
   - final type
     . replace PARENT_INTERFACE by its content in INTERFACE definition
     . remove  PARENT_INTERFACE
   - root type
     . remove everything related to object
     . the first INTERFACE field should be struct super_interface *super;
 */
#ifndef PARENT_H
#define PARENT_H

#include "object.h"
#include "interface_example.h"

#define TYPE      struct parent
#define INTERFACE struct parent_interface

#define PARENT_INTERFACE                         \
        OBJECT_INTERFACE                         \
        INTERFACE_EXAMPLE_INTERFACE                         \
		void (*method1)(TYPE*);

TYPE {
  INTERFACE *i;
};

INTERFACE {
  struct object_interface *super;
  PARENT_INTERFACE
};

TYPE      *parent_new      (void);
INTERFACE *parent_interface(void);

#undef TYPE
#undef INTERFACE

#endif /* PARENT_H */
