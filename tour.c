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

	while (!done) {
		snprintf(page, sizeof page,
			 "/usr/local/share/tour/page%02d.txt", p);
		printpage(page);

		ch = getch();
		switch (ch) {
		case 'n':
			if (++p > 11)
				p = 11;
			break;
		case 'p':
			if (--p < 1)
				p = 1;
			break;
		case 'q':
			endwin();
			done = 1;
		}
	}

	return 0;
}
