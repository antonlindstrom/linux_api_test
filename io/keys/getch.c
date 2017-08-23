#include<stdio.h>
#include<curses.h>

int main(int argc, char *argv[]) {
	initscr();
	keypad(stdscr, true);
	printw("Enter any key: ");
	char c = getch();
	endwin();

	printf("%d\n", c);

	return 0;
}
