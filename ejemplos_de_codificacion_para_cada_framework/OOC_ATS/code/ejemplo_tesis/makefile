chapter	=

1	= Child.c

c	= Object.c $1
d	= Object $(1:.c=)
h	= $(c:.c=.h)
l	= lib.a
m	= main.c
r	= $(c:.c=.r)
t	= $(m:.c=)

#rename	= sed 's/Object/Objct/g'
#post	= | $(rename)

all:		$t
clean:			; rm -f $c $h $l $r $t *.o

test::		main	;  main

hello:	 main.o	; $(CC) $(CFLAGS) -o $@ main.o $l

$t:	$l
$l:			; $(MAKE) l=$l o='$?' mklib

Object.h: Object.d  ; $(OOC) -R $(OOCFLAGS) Object -h $(post) > $@
Object.r: Object.d  ; $(OOC) -R $(OOCFLAGS) Object -r $(post) > $@
Object.c: Object.d
Object.c: Object.dc ; $(OOC) -R $(OOCFLAGS) Object Object.dc $(post) > $@

depend:		makefile.etc

include makefile.etc
include ../make/Makefile.$(OSTYPE)
