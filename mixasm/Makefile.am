bin_PROGRAMS = mixasm

noinst_HEADERS = mixasm.h locsym.h errstr.h parser.h

CFLAGS = $(MYCFLAGS)

INCLUDES = -I$(top_srcdir)/lib

YFLAGS = -d

mixasm_SOURCES = mixasm.c errstr.c scanner.c parser.c

mixasm_LDADD = $(top_builddir)/lib/libmisc.a

scanner.c: scanner.l
	if [ -f scanner.l ]; then \
		$(LEX) $(LFLAGS) $(AM_LFLAGS) \
			-oscanner.c scanner.l ; \
	fi

parser.c: parser.y
	if [ -f parser.y ]; then \
		$(YACC) $(YFLAGS) $(AM_YFLAGS) \
			-oparser.c parser.y ; \
	fi

scanner.l:
	test 1

parser.y:
	test 1
