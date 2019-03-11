/* Template for an INTERFACE definition
   - replace interface_example by the interface name
   - replace method1 by the interface first method
   - add more interface_example methods in the interface_example_interface definition and
     use a method name very close the interface name for the 1st method
     e.g. clonable -> clone, copiable -> copy then swap, comparable -> compare
   - remove this comment
 */
#ifndef INTERFACE_EXAMPLE_H
#define INTERFACE_EXAMPLE_H

#define TYPE      struct interface_example
#define INTERFACE struct interface_example_interface

#define INTERFACE_EXAMPLE_INTERFACE                         \
  void (*method2)(TYPE*);                          \
  /* more interface_example methods here         */         \
  /* TYPE* (*method_example)(TYPE*); */

TYPE {
  INTERFACE *i;
};

INTERFACE {
  INTERFACE_EXAMPLE_INTERFACE
};

extern INTERFACE interface_example_interface;

#undef TYPE
#undef INTERFACE

#endif /* INTERFACE_EXAMPLE_H */
