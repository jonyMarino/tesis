/* Template for an INTERFACE definition
   - replace xxxxx by the interface name
   - replace xxx by the interface first method
   - add more xxxxx methods in the xxxxx_interface definition and
     use a method name very close the interface name for the 1st method
     e.g. clonable -> clone, copiable -> copy then swap, comparable -> compare
   - remove this comment
 */
#ifndef XXXXX_H
#define XXXXX_H

#define TYPE      struct xxxxx
#define INTERFACE struct xxxxx_interface

#define XXXXX_INTERFACE                         \
  TYPE* (*xxx)(TYPE*);                          \
  /* more xxxxx methods here         */         \
  /* TYPE* (*method_example)(TYPE*); */

TYPE {
  struct interface *i;
};

INTERFACE {
  XXXXX_INTERFACE
};

extern INTERFACE *xxxxx_interface;

#undef TYPE
#undef INTERFACE

#endif /* XXXXX_H */
