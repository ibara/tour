all:
	${CC} ${CFLAGS} ${LDFLAGS} -static -o tour tour.c -lcurses

install:
	install -d -m 755 ${PREFIX}/share/tour
	install -c -S -s -m 555 tour ${PREFIX}/bin
	install -c -m 444 page* ${PREFIX}/share/tour

test:
	@echo No tests.

clean:
	rm -f tour tour.core
