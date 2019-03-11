/* Template for a TYPE definition
   - replace xxxxx by the type name
   - replace yyyyy by the inherited type name
   - replace zzzzz by the inherited interface name
   - add more xxxxx methods in the xxxxx_interface definition
   - add more xxxxx_new??? constructors
   - remove this comment

   Special cases:
   - no *new* interface:
     . remove everything related to zzzzz
   - abstract type:
     . remove xxxxx_new constructor
   - final type
     . replace XXXXX_INTERFACE by its content in INTERFACE definition
     . remove  XXXXX_INTERFACE
   - root type
     . remove everything related to yyyyy
     . the first INTERFACE field should be struct super_interface *super;
 */
#ifndef XXXXX_H
#define XXXXX_H

#include "yyyyy.h"
#include "zzzzz.h"

#define TYPE      struct xxxxx
#define INTERFACE struct xxxxx_interface

#define XXXXX_INTERFACE                         \
        YYYYY_INTERFACE                         \
        ZZZZZ_INTERFACE                         \
  /* more xxxxx methods here         */         \
  /* TYPE* (*method_example)(TYPE*); */

TYPE {
  INTERFACE *i;
};

INTERFACE {
  struct yyyyy_interface *super;
  XXXXX_INTERFACE
};

TYPE      *xxxxx_new      (void);
INTERFACE *xxxxx_interface(void);

#undef TYPE
#undef INTERFACE

#endif /* XXXXX_H */
