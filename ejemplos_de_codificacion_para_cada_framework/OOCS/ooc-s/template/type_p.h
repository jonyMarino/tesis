/* Template for a TYPE private definition
   - replace xxxxx by the type name
   - replace yyyyy by the inherited type name
   - add more xxxxx attributes in the xxxxx_attribute definition
   - remove this comment

   Special cases:
   - public attributes:
     . put this content in the xxxxx.h file
   - final type:
     . put this content in the xxxxx.c file
   - root type:
     . remove everything related to yyyyy
     . the first attribute should be struct interface *_;
 */
#ifndef XXXXX_PH
#define XXXXX_PH

#include "xxxxx.h"
#include "yyyyy_p.h"

struct xxxxx_attribute {
  struct yyyyy_attribute yyyyy;
  /* more xxxxx attributes here  */
  /* unsigned attribute_example; */
};

#endif /* XXXXX_PH */
