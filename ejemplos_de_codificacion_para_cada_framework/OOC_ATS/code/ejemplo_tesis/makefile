chapter	=

1	= 

c	= Object.c $1
d	= Object $(1:.c=)
h	= $(c:.c=.h)
l	= lib.a
m	= 
r	= $(c:.c=.r)
t	= $(m:.c=)

#rename	= sed 's/Object/Objct/g'
#post	= | $(rename)

all:		$t
clean:			; rm -f $c $h $l $r $t *.o

test::		hello	;  hello
test::		button	;  echo "a" | button
test::		run	;  echo "20 + 30 * 40 = Q" | run
#test::		cbutton	;  echo a | cbutton
#test::		crun	;  echo "20 + 30 * 40 = Q" | crun
#test::		xhello	;- xhello $(host)
#test::		xbutton	;- XENVIRONMENT=Xapp xbutton $(host)
test::		xrun	;  XENVIRONMENT=Xapp xrun $(host)

hello:	 hello.o	; $(CC) $(CFLAGS) -o $@ hello.o $l
button:	 button.o	; $(CC) $(CFLAGS) -o $@ button.o $l
run:	 run.o		; $(CC) $(CFLAGS) -o $@ run.o $l
cbutton: cbutton.o	; $(CC) $(CFLAGS) -o $@ cbutton.o $l $(curses)
crun:	 crun.o		; $(CC) $(CFLAGS) -o $@ crun.o $l $(curses)
xhello:	 xhello.o	; $(CC) $(CFLAGS) -o $@ xhello.o $l $(x11)
xbutton: xbutton.o	; $(CC) $(CFLAGS) -o $@ xbutton.o $l $(x11)
xrun:	 xrun.c		; $(CC) $(CFLAGS) -o $@ xrun.c $l $(x11)

$t:	$l
$l:			; $(MAKE) l=$l o='$?' mklib

Object.h: Object.d  ; $(OOC) -R $(OOCFLAGS) Object -h $(post) > $@
Object.r: Object.d  ; $(OOC) -R $(OOCFLAGS) Object -r $(post) > $@
Object.c: Object.d
Object.c: Object.dc ; $(OOC) -R $(OOCFLAGS) Object Object.dc $(post) > $@

depend:		makefile.etc

include makefile.etc
include ../make/Makefile.$(OSTYPE)
