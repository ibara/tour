# tour Makefile

CC ?=		cc
CFLAGS ?=	-O2 -pipe

PREFIX ?=	/usr/local

OBJS =	tour.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o tour ${OBJS} -lcurses

install:
	install -d -m 755 ${PREFIX}/share/tour
	install -c -S -s -m 555 tour ${PREFIX}/bin
	install -c -m 444 page* ${PREFIX}/share/tour

test:
	@echo No tests.

clean:
	rm -f ${OBJS} tour tour.core
