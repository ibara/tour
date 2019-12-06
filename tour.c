/*
 * Copyright (c) 2019 Brian Callahan <bcallah@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <curses.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void
printpage(const char *fn)
{
	FILE *fp;
	int ch;

	clear();

	if ((fp = fopen(fn, "r")) == NULL) {
		endwin();
		err(1, "fopen");
	}

	while ((ch = fgetc(fp)) != EOF)
		addch(ch);

	(void) fclose(fp);

	refresh();
}

int
main(int argc, char *argv[])
{
	char page[33];
	int ch, done = 0, p = 1;

	(void) initscr();
	keypad(stdscr, TRUE);
	(void) nonl();
	(void) cbreak();
	(void) noecho();

	while (!done) {
		snprintf(page, sizeof page,
			 "/usr/local/share/tour/page%02d.txt", p);
		printpage(page);

again:
		ch = getch();
		switch (ch) {
		case 'n':
			if (++p > 20) {
				p = 20;
				goto again;
			}
			break;
		case 'p':
			if (--p < 1) {
				p = 1;
				goto again;
			}
			break;
		case 'q':
			endwin();
			done = 1;
		}
	}

	return 0;
}
